#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <xgpio_l.h>
#include <xil_types.h>
#include <xintc_l.h>

#include "xllfifo.h"
#include "platform.h"
#include "sleep.h"
#include "xaxi_stream_adder.h"
#include "xgpio.h"
#include "xil_exception.h"
#include "xil_io.h"
#include "xil_printf.h"
#include "xintc.h"
#include "xparameters.h"
#include "xuartlite.h"

#ifdef SDT
#define BA_OR_DI(v) v##_BASEADDR
typedef UINTPTR ba_or_di_t;
#define BA_OR_DI_VAR_NAME(prefix) prefix##_base_address
#else
#define BA_OR_DI(v)               v##_DEVICE_ID
typedef u16 ba_or_di_t;
#define BA_OR_DI_VAR_NAME(prefix) prefix##_device_id
#endif

#ifdef SDT
#define INTC_DEVICE_INT_ID 0x0U
#else
/*
 *  This is the Interrupt Number of the Device whose Interrupt Output is
 *  connected to the Input of the Interrupt Controller
 */
#define INTC_DEVICE_INT_ID 0x0U
#endif

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                             \
	((byte)&0x80 ? '1' : '0'), ((byte)&0x40 ? '1' : '0'), ((byte)&0x20 ? '1' : '0'),     \
		((byte)&0x10 ? '1' : '0'), ((byte)&0x08 ? '1' : '0'), ((byte)&0x04 ? '1' : '0'), \
		((byte)&0x02 ? '1' : '0'), ((byte)&0x01 ? '1' : '0')

#define CHK_STATUS__PRINT_SUCCESS(expr, message) \
	do {                                         \
		if (((expr)) == XST_SUCCESS) {           \
			print("Succeded ");                  \
		} else {                                 \
			print("Failed in ");                 \
		}                                        \
		print(((message)));                      \
		print(".\n");                            \
	} while (0)

#define CHK_STATUS__PRINT_SUCCESS__CUSTOM_MESSAGE(expr, message_block) \
	do {                                                               \
		if (((expr)) == XST_SUCCESS) {                                 \
			print("Succeded ");                                        \
		} else {                                                       \
			print("Failed in ");                                       \
		}                                                              \
		do message_block while (0);                                    \
		print(".\n");                                                  \
	} while (0)

XGpio_Config *led_cfg, *sw_cfg, *seg_14_bit_io_cfg;
XGpio         led_gpio, sw_gpio, seg_14_bit_io;

XUartLite_Config *usb_uart_cfg;
XUartLite         usb_uart;

XLlFifo_Config *adder_fifo_config;
XLlFifo         adder_fifo;

XAxi_stream_adder_Config *stream_adder_cfg;
XAxi_stream_adder         stream_adder;

XIntc intc;

void print_char_array(u8 data[], size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (data[i] == '\0') break;
		if (data[i] == '\r') {
			xil_printf("\\r");
			// if (data_rec[count + 1] != '\n') {
			// 	printf("\\n");
			// }
		} else if (data[i] == '\n') {
			xil_printf("\\n");
		} else {
			xil_printf("%c", data[i]);
		}
	}
}

void uartlite_flush(XUartLite *ptr) {
	while (XUartLite_IsSending(ptr)) {
		usleep(1);
	}
	XUartLite_ResetFifos(ptr);
}

int init_gpio_with_addr_one_channel(XGpio         *gpio,
									XGpio_Config **gpio_cfg,
									ba_or_di_t     device_info,
									u32            ch_1_direction_mask,
									const char    *name) {
	int status;
	*gpio_cfg = XGpio_LookupConfig(device_info);
	CHK_STATUS__PRINT_SUCCESS__CUSTOM_MESSAGE(
		status = XGpio_CfgInitialize(gpio, *gpio_cfg, (*gpio_cfg)->BaseAddress), {
			print("Initializing ");
			print(name);
		});
	// usleep(1000);
	XGpio_SetDataDirection(gpio, 1, ch_1_direction_mask);
	CHK_STATUS__PRINT_SUCCESS__CUSTOM_MESSAGE(status = XGpio_SelfTest(gpio), {
		print("Self-testing of ");
		print(name);
	});
	return status;
}

void gpio_init() {
	int status;
	status = init_gpio_with_addr_one_channel(
		&led_gpio, &led_cfg, BA_OR_DI(XPAR_LEDS_GPIO), 0x0000, "LEDs GPIO");

	status = init_gpio_with_addr_one_channel(
		&sw_gpio, &sw_cfg, BA_OR_DI(XPAR_SWITCHES_GPIO), 0xffff, "Switch GPIO");

	status = init_gpio_with_addr_one_channel(&seg_14_bit_io,
											 &seg_14_bit_io_cfg,
											 BA_OR_DI(XPAR_SEG_14_BIT_IO),
											 0xffff,
											 "14-bit Integer 7 Segment Display IO");
}

void uart_init() {
	int status;
	usb_uart_cfg = XUartLite_LookupConfig(BA_OR_DI(XPAR_USB_UART));
	CHK_STATUS__PRINT_SUCCESS(
		status = XUartLite_CfgInitialize(&usb_uart, usb_uart_cfg, usb_uart_cfg->RegBaseAddr),
		"Initializing USB UART");
	uartlite_flush(&usb_uart);
	CHK_STATUS__PRINT_SUCCESS(status = XUartLite_SelfTest(&usb_uart), "Self-testing of USB UART");
	uartlite_flush(&usb_uart);
}

void fifo_init() {
	int status;
	adder_fifo_config = XLlFfio_LookupConfig(BA_OR_DI(XPAR_AXI_FIFO_TO_ADDER));
	CHK_STATUS__PRINT_SUCCESS(status = XLlFifo_CfgInitialize(
								  &adder_fifo, adder_fifo_config, adder_fifo_config->BaseAddress),
							  "Initializing FIFO to AXI Adder");
	uartlite_flush(&usb_uart);
	XLlFifo_IntDisable(&adder_fifo, XLLF_INT_ALL_MASK);
}

void stream_adder_init() {
	int status;
	stream_adder_cfg = XAxi_stream_adder_LookupConfig(BA_OR_DI(XPAR_AXIS_ADDER));
	CHK_STATUS__PRINT_SUCCESS(
		status = XAxi_stream_adder_CfgInitialize(&stream_adder, stream_adder_cfg),
		"Initializing AXI Adder");
	uartlite_flush(&usb_uart);
}

void interrupt_handler(void *_unused) {
	XIntc_Acknowledge(&intc, INTC_DEVICE_INT_ID);
	XIntc_Disable(&intc, INTC_DEVICE_INT_ID);

	const u32 SIGN_BIT = 1 << 15;
	const u32 SIGN_BIT_M1 = SIGN_BIT - 1;

	u32 data_orig = XGpio_DiscreteRead(&sw_gpio, 1);
	u16 data_trunc = (u16) data_orig;
	s32 data = (data_trunc & SIGN_BIT) == 0 ? data_trunc : -((s32)(((u32)(data_trunc)) & SIGN_BIT_M1));

	xil_printf("data_orig = %u, data_trunc = %u, SIGN_BIT = %u, SIGN_BIT = %u\n", data_orig, data_trunc, SIGN_BIT, SIGN_BIT_M1);
	xil_printf("Interrupted by button: Adding data = %d\n", data);

	while (!XLlFifo_IsTxDone(&adder_fifo)) {
		// Empty
	}

	XLlFifo_TxPutWord(&adder_fifo, data);
	XLlFifo_iTxSetLen(&adder_fifo, sizeof(data));

	uartlite_flush(&usb_uart);

	XIntc_Enable(&intc, INTC_DEVICE_INT_ID);
}

void interrupt_controller_init() {
	int status;

	CHK_STATUS__PRINT_SUCCESS(status = XIntc_Initialize(&intc, BA_OR_DI(XPAR_INTERRUPT_CONTROLLER)),
							  "Initialization of Interrupt Controller");
	CHK_STATUS__PRINT_SUCCESS(
		status = XIntc_SelfTest(&intc), "Self-testing of Interrupt Controller");

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(
		XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &intc);
	Xil_ExceptionEnable();

	CHK_STATUS__PRINT_SUCCESS(
		status =
			XIntc_Connect(&intc, INTC_DEVICE_INT_ID, (XInterruptHandler)interrupt_handler, NULL),
		"Connecting Interrupt Controller to handler function");
	XIntc_Enable(&intc, INTC_DEVICE_INT_ID);
	CHK_STATUS__PRINT_SUCCESS(
		status = XIntc_Start(&intc, XIN_REAL_MODE), "Starting of Interrupt Controller");
}

int main() {
	init_platform();
	uart_init();
	gpio_init();
	fifo_init();
	stream_adder_init();
	interrupt_controller_init();

	uartlite_flush(&usb_uart);

	{
		u32 data = 0;
		XLlFifo_TxPutWord(&adder_fifo, data);
		XLlFifo_iTxSetLen(&adder_fifo, sizeof(data));
	}

	s64 sum  = 0;

	while(0 == 0){
		s64 new_sum = (s64)XAxi_stream_adder_Get_sum(&stream_adder);
		{
			u64 abs_sum;
			u32 neg_led;
			if(new_sum < 0){
				abs_sum = -new_sum;
				neg_led = 1;
			}else{
				abs_sum = new_sum;
				neg_led = 0;
			}
			u32 truncated_sum = abs_sum % 10000;
			XGpio_DiscreteWrite(&seg_14_bit_io, 1, truncated_sum);
			XGpio_DiscreteWrite(&led_gpio, 1, neg_led);
		}
		if(new_sum != sum){
			xil_printf("sum = %lld\n", new_sum);
			uartlite_flush(&usb_uart);
		}
		sum = new_sum;
	}

	cleanup_platform();
	return 0;
}

/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

// This include is relative to $CARAVEL_PATH (see Makefile)
#include <defs.h>
// #include <stub.c>
#include <user_uart.h>
#ifdef USER_PROJ_IRQ0_EN
#include <irq_vex.h>
#endif

// extern int adder();
extern int* matmul();
extern int* qsort();
extern int* fir();


extern void uart_write();
extern void uart_write_char();
extern void uart_write_string();
extern void uart_reset_write_fifo();
extern int uart_isr();
extern int uart_read();

// --------------------------------------------------------

/*
	MPRJ Logic Analyzer Test:
		- Observes counter value through LA probes [31:0] 
		- Sets counter initial value through LA probes [63:32]
		- Flags when counter value exceeds 500 through the management SoC gpio
		- Outputs message to the UART when the test concludes successfuly
*/

void main()
{
#ifdef USER_PROJ_IRQ0_EN
    int mask;
#endif

  reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;

	reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_9  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_8  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_7  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_4  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_3  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_2  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_1  = GPIO_MODE_MGMT_STD_OUTPUT;
	reg_mprj_io_0  = GPIO_MODE_MGMT_STD_OUTPUT;

	reg_mprj_io_6  = GPIO_MODE_USER_STD_OUTPUT;
	reg_mprj_io_5  = GPIO_MODE_USER_STD_INPUT_NOPULL;

	
	
	reg_wb_enable = 1;
	
	reg_uart_enable = 1;
	// reg_uart_clkdiv = 625;
	
	reg_mprj_xfer = 1;
	while (reg_mprj_xfer == 1);

	// Configure LA probes [31:0], [127:64] as inputs to the cpu 
	// Configure LA probes [63:32] as outputs from the cpu
	reg_la0_oenb = reg_la0_iena = 0x00000000;    // [31:0]
	reg_la1_oenb = reg_la1_iena = 0xFFFFFFFF;    // [63:32]
	reg_la2_oenb = reg_la2_iena = 0x00000000;    // [95:64]
	reg_la3_oenb = reg_la3_iena = 0x00000000;    // [127:96]

	// Set Counter value to zero through LA probes [63:32]
	reg_la1_data = 0x00000000;

	// Configure LA probes from [63:32] as inputs to disable counter write
	reg_la1_oenb = reg_la1_iena = 0x00000000;


#ifdef USER_PROJ_IRQ0_EN	
	// unmask USER_IRQ_0_INTERRUPT
	mask = irq_getmask();
	mask |= 1 << USER_IRQ_0_INTERRUPT; // USER_IRQ_0_INTERRUPT = 2
	irq_setmask(mask);
	// enable user_irq_0_ev_enable
	user_irq_0_ev_enable_write(1);	
#endif

	// Set UART clock to 64 kbaud (enable before I/O configuration)

	reg_mprj_datal = 0xAB400000;
	int* task_mm = matmul();
	reg_mprj_datal = *(task_mm+0) << 16;
	reg_mprj_datal = *(task_mm+1) << 16;
	reg_mprj_datal = *(task_mm+2) << 16;
	reg_mprj_datal = *(task_mm+3) << 16;
	// reg_mprj_datal = *(task_mm+4) << 16;
	// reg_mprj_datal = *(task_mm+5) << 16;
	// reg_mprj_datal = *(task_mm+6) << 16;
	// reg_mprj_datal = *(task_mm+7) << 16;
	// reg_mprj_datal = *(task_mm+8) << 16;
	// reg_mprj_datal = *(task_mm+9) << 16;
	// reg_mprj_datal = *(task_mm+10) << 16;
	// reg_mprj_datal = *(task_mm+11) << 16;
	// reg_mprj_datal = *(task_mm+12) << 16;
	// reg_mprj_datal = *(task_mm+13) << 16;
	// reg_mprj_datal = *(task_mm+14) << 16;
	// reg_mprj_datal = *(task_mm+15) << 16;
	reg_mprj_datal = 0xAB500000;

	
	reg_mprj_datal = 0xAB410000;
	int* task_qs = qsort();
	reg_mprj_datal = *(task_qs+0) << 16;
	reg_mprj_datal = *(task_qs+1) << 16;
	reg_mprj_datal = *(task_qs+2) << 16;
	reg_mprj_datal = *(task_qs+3) << 16;
	reg_mprj_datal = *(task_qs+4) << 16;
	reg_mprj_datal = *(task_qs+5) << 16;
	reg_mprj_datal = *(task_qs+6) << 16;
	reg_mprj_datal = *(task_qs+7) << 16;
	reg_mprj_datal = *(task_qs+8) << 16;
	reg_mprj_datal = *(task_qs+9) << 16;
	reg_mprj_datal = 0xAB510000;

	reg_mprj_datal = 0xAB420000;
	int* task_fir = fir();
	for(int i=0; i<64; i++)
	{
		reg_mprj_datal = *(task_fir+i) << 16;
	}
	reg_mprj_datal = 0xAB520000;
	
}


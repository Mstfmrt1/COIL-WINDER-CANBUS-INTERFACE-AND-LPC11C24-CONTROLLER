#ifndef COIL_WINDER_H
#define COIL_WINDER_H


#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cr_section_macros.h>
#endif
#endif

#define CAN_BAUD_RATE 250000
#define GPIO_PININT_PORT 		0
#define GPIO_PININT 			6
#define IOCON_PIN_ID		    IOCON_PIO0_6
#define PININT_IRQ_HANDLER	PIOINT0_IRQHandler /* GPIO interrupt IRQ function name */
#define PININT_NVIC_NAME		EINT0_IRQn /* GPIO interrupt NVIC interrupt name */

CCAN_MSG_OBJ_T Send_Data;
CCAN_MSG_OBJ_T Rx_Command;
CCAN_MSG_OBJ_T send_msg;

typedef enum _BUTTON_STATUS
{
  RELEASED=0,
  PRESSED,
}button_status;


void Chip_GPIO_AllInit()
{
	Chip_GPIO_Init(LPC_GPIO);

    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 3, 2);
    Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO3_2 , IOCON_MODE_INACT, FUNC0);

    /*Chip_IOCON_PinMux(LPC_IOCON, IOCON_PIO0_8 , IOCON_MODE_INACT, FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 8);Set BOARD LED OUTPUT*/

    Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPIO_PININT_PORT, GPIO_PININT);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIN_ID,//PIO06 SET AS INPUT
    (IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));

   // Configure channel interrupt as edge sensitive and falling edge interrupt

  /*Chip_GPIO_SetPinModeEdge(LPC_GPIO, GPIO_PININT_PORT, (1 << GPIO_PININT));
    Chip_GPIO_SetEdgeModeSingle(LPC_GPIO, GPIO_PININT_PORT, (1 << GPIO_PININT));
	Chip_GPIO_SetModeHigh(LPC_GPIO, GPIO_PININT_PORT, (1 << GPIO_PININT));*/

    Chip_GPIO_SetupPinInt(LPC_GPIO, GPIO_PININT_PORT, GPIO_PININT, GPIO_INT_RISING_EDGE);
    Chip_GPIO_EnableInt(LPC_GPIO, GPIO_PININT_PORT, (1 << GPIO_PININT));


    Chip_SYSCTL_EnableStartPin(0X08); /* Hardcoded to PIO0_3 right for this board */
    Chip_SYSCTL_ResetStartPin(0X08); /* Hardcoded to PIO0_3 right for this board */

   /* Enable all clocks, even those turned off at wake power up */
   Chip_SYSCTL_SetWakeup(~(SYSCTL_SLPWAKE_IRCOUT_PD | SYSCTL_SLPWAKE_IRC_PD |
   SYSCTL_SLPWAKE_FLASH_PD | SYSCTL_SLPWAKE_SYSOSC_PD | SYSCTL_SLPWAKE_SYSOSC_PD | SYSCTL_SLPWAKE_SYSPLL_PD));

   /* Enable interrupt in the NVIC */
   NVIC_EnableIRQ(PININT_NVIC_NAME);
}


void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg)
{
	uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
	pClk = Chip_Clock_GetMainClockRate();

	clk_per_bit = pClk / baud_rate;

	for (div = 0; div <= 15; div++) {
		for (quanta = 1; quanta <= 32; quanta++) {
			for (segs = 3; segs <= 17; segs++) {
				if (clk_per_bit == (segs * quanta * (div + 1))) {
					segs -= 3;
					seg1 = segs / 2;
					seg2 = segs - seg1;
					can_sjw = seg1 > 3 ? 3 : seg1;
					can_api_timing_cfg[0] = div;
					can_api_timing_cfg[1] =
						((quanta - 1) & 0x3F) | (can_sjw & 0x03) << 6 | (seg1 & 0x0F) << 8 | (seg2 & 0x07) << 12;
					return;
				}
			}
		}
	}
}




void set_up_msg()
{
Send_Data.mode_id=0x500;           //SEND COUNT DATA
Send_Data.mask=0x1FFFFFFF;
Send_Data.dlc=4;
Send_Data.msgobj=2;

//received messsage
Rx_Command.mode_id=0x600;        //RECEIVE PC COMMAND
Rx_Command.mask=0x1FFFFFFF;
Rx_Command.dlc=8;

LPC_CCAN_API->config_rxmsgobj(&Rx_Command);

}

void Send_Msg(uint32_t _mode_id,uint8_t b0,uint8_t b1,uint8_t b2,uint8_t b3,uint8_t b4,uint8_t b5,uint8_t b6,uint8_t b7)
{
	send_msg.mode_id=_mode_id;
	//send_msg.mask=_mask;
	send_msg.dlc=8;
	send_msg.data[0]=b0;
	send_msg.data[1]=b1;
	send_msg.data[2]=b2;
	send_msg.data[3]=b3;
	send_msg.data[4]=b4;
	send_msg.data[5]=b5;
	send_msg.data[6]=b6;
	send_msg.data[7]=b7;
	send_msg.msgobj=6;

	LPC_CCAN_API->can_transmit(&send_msg);
}

void Send_INPData(uint16_t count)
{
	if(count<256)
	{
		Send_Data.data[0]=count;
		Send_Data.data[1]=0;
		Send_Data.data[2]=0;
		Send_Data.data[3]=0;
		 LPC_CCAN_API->can_transmit(&Send_Data);

	}

	else if ((count>256) && (count<512))
	{
		Send_Data.data[0]=255;
	    Send_Data.data[1]=count-255;
	    Send_Data.data[2]=0;
	    Send_Data.data[3]=0;
		 LPC_CCAN_API->can_transmit(&Send_Data);

	}
    else if((count>512) && (count<768))
    {
    	Send_Data.data[0]=255;
        Send_Data.data[1]=255;
        Send_Data.data[2]=count-510;
        Send_Data.data[3]=0;
        LPC_CCAN_API->can_transmit(&Send_Data);

    }
    else if((count>768) && (count<1024) )
    {
    	Send_Data.data[0]=255;
        Send_Data.data[1]=255;
        Send_Data.data[2]=255;
        Send_Data.data[3]=count-765;
        LPC_CCAN_API->can_transmit(&Send_Data);

    }
}

#endif /* COIL_WINDER_H */


#if defined (__USE_LPCOPEN)
#include "chip.h"
#endif

#include <cr_section_macros.h>
#include "motordriver.h"
#include "Ind_Wrapper.h"


uint32_t CanApiClkInitTable[2];
uint32_t count=0;
#define TEST_CCAN_BAUD_RATE 250000
uint8_t pwm=2;
uint16_t turn_value;

void PININT_IRQ_HANDLER(void)
{
	/* Clear interrupt */
	Chip_GPIO_ClearInts(LPC_GPIO, GPIO_PININT_PORT, (1 << GPIO_PININT));
	Chip_GPIO_SetPinToggle(LPC_GPIO, 3, 2);
	count++;
	if(count==turn_value)
	{
		//NVIC_DisableIRQ(EINT0_IRQn);
		DC_MOTOR_Set_Speed(DC_MOTOR1,100 );
		Send_Msg(0x545, 70, 73, 78, 73, 83, 72, 69, 68);
	}


	Send_INPData(count);



}

/*	CAN receive callback */
/*	Function is executed by the Callback handler after
    a CAN message has been received */
void CAN_rx(uint8_t msg_obj_num) {
	    Rx_Command.msgobj = msg_obj_num;
	    LPC_CCAN_API->can_receive(&Rx_Command);

        pwm=Rx_Command.data[1];

	    if(Rx_Command.mode_id==0x600 && Rx_Command.data[0]==1)
	    {
	    	Send_Msg(0x545, 87, 79, 82, 75, 73, 78, 71, 0);
	    	count=0;
	    	//NVIC_EnableIRQ(PIO0_6_IRQn);
	    	DC_MOTOR_Set_Speed(DC_MOTOR1,pwm );
	    	turn_value=Rx_Command.data[2]+Rx_Command.data[3]+Rx_Command.data[4]+Rx_Command.data[5];
	    }
	    else if(Rx_Command.mode_id==0x600 && Rx_Command.data[0]==0)
	    {
	    	DC_MOTOR_Set_Speed(DC_MOTOR1,100 );
	    }



}
/*	CAN transmit callback */
/*	Function is executed by the Callback handler after
    a CAN message has been transmitted */
void CAN_tx(uint8_t msg_obj_num) {


}

/*	CAN error callback */
/*	Function is executed by the Callback handler after
    an error has occured on the CAN bus */
void CAN_error(uint32_t error_info) {}

/**
 * @brief	CCAN Interrupt Handler
 * @return	Nothing
 * @note	The CCAN interrupt handler must be provided by the user application.
 *	It's function is to call the isr() API located in the ROM
 */
void CAN_IRQHandler(void) {


	LPC_CCAN_API->isr();
}

void Can_CallbackInit()
{
	CCAN_CALLBACKS_T callbacks = {
			    CAN_rx,
			 	CAN_tx,
			 	CAN_error,
			 	NULL,
			 	NULL,
			 	NULL,
			 	NULL,
			 	NULL,
			   };


			  baudrateCalculate(TEST_CCAN_BAUD_RATE, CanApiClkInitTable);
			  LPC_CCAN_API->init_can(&CanApiClkInitTable[0], TRUE);
			/* Configure the CAN callback functions */
			  LPC_CCAN_API->config_calb(&callbacks);
			  	/* Enable the CAN Interrupt */
			  NVIC_EnableIRQ(CAN_IRQn);

}


int main(void)
{
	uint8_t pwm=0;
	SystemCoreClockUpdate();
	Can_CallbackInit();
	Chip_GPIO_AllInit();
	set_up_msg();
	pwmInit(IOCON_PIO0_8, DC_MOTOR1, 24-1);
	DC_MOTOR_Init(DC_MOTOR1);

	DC_MOTOR_Start(DC_MOTOR1, DIR_ClockWıse,100);


while(1)	 {
    			__WFI();

    		}
return 0 ;
}

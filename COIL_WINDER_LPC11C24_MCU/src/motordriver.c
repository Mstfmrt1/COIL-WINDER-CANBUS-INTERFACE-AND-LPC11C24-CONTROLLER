#include "motordriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSTEM_FREQUENCY	     (48000000)
#define TMR16_PWM_PRESCALER     (24)//Divider to system clock to get PWM prescale value
#define TMR16_PWM_PERIOD_HZ      (20000)

// SET DC_MOTOR_INIT() MOTOR PIN SETTINGS ENABLE
// SET PWM_INIT ()  PWM SETTINGS ENABLE

const DC_MOTOR_CfgType DC_MOTOR_CfgParam[DC_MOTOR_UNITS] =
{
	// DC MOTOR 1 Configurations
    {
    	PORT2,
		PORT2,
		IOCON_PIO2_7,
		IOCON_PIO2_8,
		NUM0,
		LPC_TIMER16_0,
		48,
		DC_MOTOR_F_PWM,
		DC_MOTOR_PWM_RES
	}
};


	// DC MOTOR 2 Configurations
/**/


void DC_MOTOR_Init(uint8_t MOTOR_Instance)
{

	//--------[ Configure The 2 Direction Control GPIO Pins ]-------


    //PINMUX PWM FUNC
    Chip_IOCON_PinMux(LPC_IOCON, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN , IOCON_MODE_INACT, FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT,  DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN);

    Chip_IOCON_PinMux(LPC_IOCON, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN , IOCON_MODE_INACT, FUNC0);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN);



    //SET START OUTPUT DISABLE
    Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT , DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN, false);

    Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN, false);
}

void pwmInit(CHIP_IOCON_PIO_T IOCON,uint8_t MOTOR_Instance,uint16_t Prescaler)
{
	    Chip_IOCON_PinMux(LPC_IOCON, IOCON , IOCON_MODE_PULLDOWN, IOCON_FUNC2 | (0x1 << 6)| (0x1 << 7));//IOCON_PIO0_8

		//LPC_TIMER16_0->EMR = (1<<0)|(1<<5);

		/* Setup Timer for PWM */
		Chip_TIMER_Init( DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance );
		// MR0 reset
	    Chip_TIMER_ResetOnMatchEnable(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN);
		//set the resolution of the ticks to the PWM timer (match register resolution)
	    // Set the frequency prescaler for the timer
	    Chip_TIMER_PrescaleSet(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance, Prescaler);//24
	    // Set MR3 value for resetting the timer
	    Chip_TIMER_SetMatch(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, 2);

	    // Set PWM Control Register
	    Chip_TIMER_PWMWrite(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance,(1<< DC_MOTOR_CfgParam[MOTOR_Instance].MatchN));
	    // Enable Timer16_0
	    Chip_TIMER_Enable(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance);
	    Chip_TIMER_Init(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance);

}

void DC_MOTOR_Start(uint8_t MOTOR_Instance, uint8_t DIR, uint16_t SPEED)
{
	/* Write To The 2 Direction Control Pins */
	if(DIR == DIR_ClockWıse)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT , DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN, true);

	    Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN, false);
	}
	else if(DIR == DIR_CClockWıse)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT , DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN, false);

		Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN, true);
	}

	if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER16_0)
		{
			Chip_TIMER_SetMatch(LPC_TIMER16_0,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
		}
		else if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER16_1)
		{
			Chip_TIMER_SetMatch(LPC_TIMER16_1,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
		}
		else if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER32_0)
		{
				Chip_TIMER_SetMatch(LPC_TIMER32_0,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
		}
		else if (DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER32_1)
		{
			    Chip_TIMER_SetMatch(LPC_TIMER32_1,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
		}



}

void DC_MOTOR_Set_Dir(uint8_t MOTOR_Instance, uint8_t DIR)
{
	/* Write To The 2 Direction Control Pins */
	if(DIR == DIR_ClockWıse)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT , DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN, true);

	    Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN, false);
	}
	else if(DIR == DIR_CClockWıse)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT , DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN, false);

		Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN, true);
	}
}
void DC_Motor_Stop(uint8_t MOTOR_Instance)
{

	Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PORT , DC_MOTOR_CfgParam[MOTOR_Instance].DIR1_PIN, false);

    Chip_GPIO_SetPinState(LPC_GPIO, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PORT, DC_MOTOR_CfgParam[MOTOR_Instance].DIR2_PIN, false);

	if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER16_0)
	{
		Chip_TIMER_SetMatch(LPC_TIMER16_0,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, 0);
	}
	else if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER16_1)
	{
		Chip_TIMER_SetMatch(LPC_TIMER16_1,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, 0);
	}
	else if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER32_0)
	{
			Chip_TIMER_SetMatch(LPC_TIMER32_0,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, 0);
	}
	else if (DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER32_1)
	{
		    Chip_TIMER_SetMatch(LPC_TIMER32_1,  DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, 0);
	}


}



void DC_MOTOR_Set_Speed(uint8_t MOTOR_Instance, uint16_t SPEED)
{
	if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER16_0)
	{
		Chip_TIMER_SetMatch(LPC_TIMER16_0, DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
	}
	else if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER16_1)
	{
		Chip_TIMER_SetMatch(LPC_TIMER16_1, DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
	}
	else if(DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER32_0)
	{
			Chip_TIMER_SetMatch(LPC_TIMER32_0, DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
	}
	else if (DC_MOTOR_CfgParam[MOTOR_Instance].TIM_Instance==LPC_TIMER32_1)
	{
			Chip_TIMER_SetMatch(LPC_TIMER32_1, DC_MOTOR_CfgParam[MOTOR_Instance].MatchN, SPEED);
	}


}

void Chip_TIMER_PWMWrite(LPC_TIMER_T *pTMR, uint32_t pwmval)
{
    pTMR->PWMC = pwmval;
}

uint32_t Chip_TIMER_PWMRead(LPC_TIMER_T *pTMR)
{
    return pTMR->PWMC;
}



/*void setFreq(uint16_t requested_freq,uint16_t duty_cycle){
	uint32_t period;
	uint32_t dCycle;
	if(requested_freq>0){
		period=(65535/requested_freq); //+ ( ( (65535%requested_freq)*2) / requested_freq) ;
		dCycle=period*duty_cycle/1000;
	}else{
		period=65000;
		dCycle=65000;
	}
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 3, period);
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 1,dCycle );
}*/



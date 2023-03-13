
#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_
#include "chip.h"

// DC Motor Rotation Directions
#define DIR_ClockWıse        0
#define DIR_CClockWıse       1
// MOTOR INSTANCE
#define DC_MOTOR1    0
#define DC_MOTOR2    1
// DC Motor PWM Properties
#define DC_MOTOR_PWM_RES  10
#define DC_MOTOR_F_PWM    19000

// The Number OF DC MOTORs To Be Used
#define DC_MOTOR_UNITS  1

typedef enum _PORTS
{
	PORT0=0,
	PORT1,
	PORT2,
	PORT3
}PORT;
typedef enum _MATCH_NUMBER
{
	NUM0=0,
	NUM1,
	NUM2,
	NUM3
}Match_Num;

typedef struct
{
	PORT         DIR1_PORT;
	PORT         DIR2_PORT;
	uint8_t       DIR1_PIN;
	uint8_t       DIR2_PIN;
	Match_Num     MatchN;
	LPC_TIMER_T*   TIM_Instance;
	uint16_t       TIM_CLK_MHz;
	uint32_t       PWM_FREQ_Hz;
	uint8_t        PWM_RES_BITS;
}DC_MOTOR_CfgType;

extern const DC_MOTOR_CfgType DC_MOTOR_CfgParam[DC_MOTOR_UNITS];

void DC_MOTOR_Init(uint8_t MOTOR_Instance);
void pwmInit(CHIP_IOCON_PIO_T IOCON,uint8_t MOTOR_Instance,uint16_t Prescaler);
void DC_MOTOR_Start(uint8_t MOTOR_Instance, uint8_t DIR, uint16_t SPEED);
void DC_MOTOR_Set_Dir(uint8_t MOTOR_Instance, uint8_t DIR);
void DC_Motor_Stop(uint8_t MOTOR_Instance);
void DC_MOTOR_Set_Speed(uint8_t MOTOR_Instance, uint16_t SPEED);


void Chip_TIMER_PWMWrite(LPC_TIMER_T *pTMR, uint32_t pwmval);
uint32_t Chip_TIMER_PWMRead(LPC_TIMER_T *pTMR);



#endif /* MOTORDRIVER_H_ */

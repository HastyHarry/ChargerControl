/*
******************************************************************************
* @file           : ControlFunc.h
* @brief          : Control and Init functions for Buck Converter
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUCK_CTRL_H
#define __BUCK_CTRL_H

//#include "stdint.h"
//#include "stdio.h"
#include "stm32g4xx_hal.h"
#include "Application_Conf.h"

/* Exported types ------------------------------------------------------------*/
typedef struct {
float Kp;
float Ki;
float Kd;
float SW_Freq;
float Omega;
float Err_pr;
float Up_pr;
float Ui_pr;
float Ud_pr;
float Ui_previous;
float Ud_previous;
float Sat_Up;
float Sat_Down;
float Hist;
float Base_Value;
float Antiwindup_Val;
float Antiwindup_Gain;
uint16_t MA_Step;
FlagStatus Init_Complete;
FlagStatus Antiwindup_Switch;
FlagStatus resetPI;
FlagStatus resetComplete;
}PID_Control_Struct;

typedef struct{
  uint32_t Vdc[ADC1_MA_PERIOD_VDC];
  uint32_t Vac[ADC1_MA_PERIOD_VDC];
  uint32_t Idc[ADC1_MA_PERIOD_VDC];
  uint32_t MA_Counter;
  float Vdc_MA;
  float Vac_MA;
  float Idc_MA;
  float Vdc_MA_prev;
  float Vac_MA_prev;
  float Idc_MA_prev;

  FlagStatus Ready;
}RAW_ADC_Struct;


typedef struct{
  float Vdc;
  float Vac;
  float Idc;
}Cooked_ADC_Struct;

typedef struct {
float G_Vac;
float invG_Vac;
float B_Vac;
float G_Iac;
float invG_Iac;
float B_Iac;
float G_Vdc;
float invG_Vdc;
float B_Vdc;
float G_Idc;
float invG_Idc;
float B_Idc;
FlagStatus ADC_Conf_Complete;
}ADC_Conf_TypeDef;

typedef struct{
	uint32_t PWM_A;
	uint32_t PWM_B;
}BUCK_PWM_Source_Struct;

typedef struct{
	uint32_t OC1;
}BUCK_OC_Source_Struct;

void PID_Init(PID_Control_Struct* PID_CONFIG, float Kp, float Ki, float Kd, float Freq, float Omega, float Sat_Up, float Sat_Down,
				float Hist, float Antiwindup, float Base_Value);
float PID(float Ref, float Feed, PID_Control_Struct* Conf_struct);

#endif //__BUCK_CTRL_H

/**
******************************************************************************
* @file           : Buck_Control.c
* @brief          : Control and init functions for Buck Converter
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include <ControlFunc.h>

#include "tim.h"
#include "Application_Conf.h"

/* Private variables ---------------------------------------------------------*/

RAW_ADC_Struct Raw_ADC;
RAW_ADC_Struct Raw_DMA;



/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  PID_Init
  * @param
  * @param
  * @retval None
  */
void PID_Init(PID_Control_Struct* PID_CONFIG, float Kp, float Ki, float Kd, float Freq, float Omega, float Sat_Up, float Sat_Down,
				float Hist, float Antiwindup, float Base_Value ){

	PID_CONFIG->SW_Freq = Freq;
	PID_CONFIG->Omega = Omega;
	PID_CONFIG->Kp = Kp;
	PID_CONFIG->Ki = Ki;
	PID_CONFIG->Kd = Kd;
	PID_CONFIG->Sat_Up = Sat_Up;
	PID_CONFIG->Sat_Down = Sat_Down;
	PID_CONFIG->Hist = Hist;
	PID_CONFIG->Antiwindup_Gain = Antiwindup;
	PID_CONFIG->Base_Value = Base_Value;
	PID_CONFIG->Init_Complete = SET;

}


/**
  * @brief  PID
  * @param  Ref
  * @param  Feed
  * @param  Co nf_struct
  * @retval Result
  */
float PID(float Ref, float Feed, PID_Control_Struct* Conf_struct){

	float Err;
	float Result;
	float Up;
	float Ui;
	float Ud;


	if (Conf_struct->resetPI == SET){
		Conf_struct->Ui_previous = 0;
		Conf_struct->Ud_previous = 0;
		Conf_struct->Err_pr = 0;
		Conf_struct->resetPI = RESET;
	}

	Err = Ref - Feed;

	Up = Conf_struct->Kp * Err;

	if (Err < (Ref*Conf_struct->Hist)/100 && Err>0){
		Ui = (Conf_struct->Ui_previous + Err*Conf_struct->Ki*Conf_struct->Antiwindup_Gain);
	}
	else if (Err > (Ref*Conf_struct->Hist)/100 && Err<0){
		Ui = (Conf_struct->Ui_previous + Err*Conf_struct->Ki*Conf_struct->Antiwindup_Gain);
	}
	else {
		Ui = Conf_struct->Ui_previous + Err*Conf_struct->Ki;
	}

	Ud =(Err - Conf_struct->Err_pr)*Conf_struct->Kd;
	Result = Up+Ui+Ud;

	Result = Conf_struct->Base_Value + Result;

	if (Result>=Conf_struct->Sat_Up){
		Result = Conf_struct->Sat_Up;
	}
	else if (Result<=Conf_struct->Sat_Down){
		Result = Conf_struct->Sat_Down;
	}

	if (Conf_struct->Antiwindup_Switch==SET){
		Conf_struct->Antiwindup_Val = (Conf_struct->Sat_Up - Result)*Conf_struct->Antiwindup_Gain;
	}
	else{
		Conf_struct->Antiwindup_Val=0;
	}

	Conf_struct->Err_pr = Err;
	Conf_struct->Up_pr = Up;
	Conf_struct->Ui_previous = Ui;
	Conf_struct->Ud_previous = Result;

	return Result;
}

/**
  * @brief  ADC_Gain_Init
  * @param  ADC_Conf_TypeDef
  * @retval None
  */

void ADC_Gain_Init(ADC_Conf_TypeDef *BUCK_ADC_Conf,float G_Vac,float B_Vac,float G_Iac,float B_Iac,float G_Vdc,float B_Vdc,float G_Idc,float B_Idc){

	BUCK_ADC_Conf->B_Vac=B_Vac;
	BUCK_ADC_Conf->G_Vac=G_Vac;
	BUCK_ADC_Conf->invG_Vac=(float)(1.0/G_Vac);

	BUCK_ADC_Conf->B_Vdc=B_Vdc;
	BUCK_ADC_Conf->G_Vdc=G_Vdc;
	BUCK_ADC_Conf->invG_Vdc=(float)(1.0/G_Vdc);

	BUCK_ADC_Conf->B_Iac=B_Iac;
	BUCK_ADC_Conf->G_Iac=G_Iac;
	BUCK_ADC_Conf->invG_Iac=(float)(1.0/G_Iac);

	BUCK_ADC_Conf->B_Idc=B_Idc;
	BUCK_ADC_Conf->G_Idc=G_Idc;
	BUCK_ADC_Conf->invG_Idc=(float)(1.0/G_Idc);

	BUCK_ADC_Conf->ADC_Conf_Complete=SET;
}




/**
******************************************************************************
* @file           : PWM_Functions.c
* @brief          : Functions for PWM control using G334
******************************************************************************


/* Includes ------------------------------------------------------------------*/
#include "PWM_Functions.h"
#include "hrtim.h"

HRTIM_HandleTypeDef hhrtim1;

//void HRTIM_PWM_Init(uint32_t  BURST_PWM_Freq_Desidered,uint32_t  PWM_Freq_Desidered, DPC_PWM_StatusTypeDef DPC_PWM_SET,
//		DPC_PWM_TypeDef *tDPC_PWM_loc, DMA_PWMDUTY_STRUCT *DUTY_SRC){
//
//}

void HRTIM_PWM_Init(/*uint32_t  BURST_PWM_Freq_Desidered, uint32_t  PWM_Freq_Desidered,*/  DMA_PWMDUTY_STRUCT *DUTY_SRC)
{
	  /* USER CODE BEGIN HRTIM1_Init 0 */

	  /* USER CODE END HRTIM1_Init 0 */

	  HRTIM_FaultCfgTypeDef pFaultCfg = {0};
	  HRTIM_FaultBlankingCfgTypeDef pFaultBlkCfg = {0};
	  HRTIM_ADCTriggerCfgTypeDef pADCTriggerCfg = {0};
	  HRTIM_TimeBaseCfgTypeDef pTimeBaseCfg = {0};
	  HRTIM_TimerCtlTypeDef pTimerCtl = {0};
	  HRTIM_TimerCfgTypeDef pTimerCfg = {0};
	  HRTIM_CompareCfgTypeDef pCompareCfg = {0};
	  HRTIM_DeadTimeCfgTypeDef pDeadTimeCfg = {0};
	  HRTIM_OutputCfgTypeDef pOutputCfg = {0};

	  /* USER CODE BEGIN HRTIM1_Init 1 */

	  /* USER CODE END HRTIM1_Init 1 */
	  hhrtim1.Instance = HRTIM1;
	  hhrtim1.Init.HRTIMInterruptResquests = HRTIM_IT_FLT1|HRTIM_IT_FLT3
	                              |HRTIM_IT_FLT4;
	  hhrtim1.Init.SyncOptions = HRTIM_SYNCOPTION_NONE;
	  if (HAL_HRTIM_Init(&hhrtim1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_DLLCalibrationStart(&hhrtim1, HRTIM_CALIBRATIONRATE_3) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_PollForDLLCalibration(&hhrtim1, 10) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_FaultPrescalerConfig(&hhrtim1, HRTIM_FAULTPRESCALER_DIV1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pFaultCfg.Source = HRTIM_FAULTSOURCE_DIGITALINPUT;
	  pFaultCfg.Polarity = HRTIM_FAULTPOLARITY_HIGH;
	  pFaultCfg.Filter = HRTIM_FAULTFILTER_NONE;
	  pFaultCfg.Lock = HRTIM_FAULTLOCK_READWRITE;
	  if (HAL_HRTIM_FaultConfig(&hhrtim1, HRTIM_FAULT_1, &pFaultCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pFaultBlkCfg.Threshold = 0;
	  pFaultBlkCfg.ResetMode = HRTIM_FAULTCOUNTERRST_UNCONDITIONAL;
	  pFaultBlkCfg.BlankingSource = HRTIM_FAULTBLANKINGMODE_RSTALIGNED;
	  if (HAL_HRTIM_FaultCounterConfig(&hhrtim1, HRTIM_FAULT_1, &pFaultBlkCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_FaultBlankingConfigAndEnable(&hhrtim1, HRTIM_FAULT_1, &pFaultBlkCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_HRTIM_FaultModeCtl(&hhrtim1, HRTIM_FAULT_1, HRTIM_FAULTMODECTL_ENABLED);
	  if (HAL_HRTIM_FaultCounterConfig(&hhrtim1, HRTIM_FAULT_3, &pFaultBlkCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_FaultBlankingConfigAndEnable(&hhrtim1, HRTIM_FAULT_3, &pFaultBlkCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_FaultConfig(&hhrtim1, HRTIM_FAULT_3, &pFaultCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_HRTIM_FaultModeCtl(&hhrtim1, HRTIM_FAULT_3, HRTIM_FAULTMODECTL_ENABLED);
	  if (HAL_HRTIM_FaultCounterConfig(&hhrtim1, HRTIM_FAULT_4, &pFaultBlkCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_FaultBlankingConfigAndEnable(&hhrtim1, HRTIM_FAULT_4, &pFaultBlkCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_FaultConfig(&hhrtim1, HRTIM_FAULT_4, &pFaultCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  HAL_HRTIM_FaultModeCtl(&hhrtim1, HRTIM_FAULT_4, HRTIM_FAULTMODECTL_ENABLED);
	  pADCTriggerCfg.UpdateSource = HRTIM_ADCTRIGGERUPDATE_TIMER_A;
	  pADCTriggerCfg.Trigger = HRTIM_ADCTRIGGEREVENT13_NONE;
	  if (HAL_HRTIM_ADCTriggerConfig(&hhrtim1, HRTIM_ADCTRIGGER_1, &pADCTriggerCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_ADCPostScalerConfig(&hhrtim1, HRTIM_ADCTRIGGER_1, 0x0) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimeBaseCfg.Period = 28936;
	  pTimeBaseCfg.RepetitionCounter = 0x00;
	  pTimeBaseCfg.PrescalerRatio = HRTIM_PRESCALERRATIO_MUL32;
	  pTimeBaseCfg.Mode = HRTIM_MODE_CONTINUOUS;
	  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pTimeBaseCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimerCtl.UpDownMode = HRTIM_TIMERUPDOWNMODE_UP;
	  pTimerCtl.TrigHalf = HRTIM_TIMERTRIGHALF_DISABLED;
	  pTimerCtl.GreaterCMP3 = HRTIM_TIMERGTCMP3_EQUAL;
	  pTimerCtl.GreaterCMP1 = HRTIM_TIMERGTCMP1_EQUAL;
	  pTimerCtl.DualChannelDacEnable = HRTIM_TIMER_DCDE_DISABLED;
	  if (HAL_HRTIM_WaveformTimerControl(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pTimerCtl) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimerCfg.InterruptRequests = HRTIM_TIM_IT_NONE;
	  pTimerCfg.DMARequests = HRTIM_TIM_DMA_RST;
	  pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chA1;
	  pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[0].CMP3xR);
	  pTimerCfg.DMASize = 0x1;
	  pTimerCfg.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
	  pTimerCfg.InterleavedMode = HRTIM_INTERLEAVED_MODE_DISABLED;
	  pTimerCfg.StartOnSync = HRTIM_SYNCSTART_DISABLED;
	  pTimerCfg.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
	  pTimerCfg.DACSynchro = HRTIM_DACSYNC_NONE;
	  pTimerCfg.PreloadEnable = HRTIM_PRELOAD_ENABLED;
	  pTimerCfg.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
	  pTimerCfg.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
	  pTimerCfg.RepetitionUpdate = HRTIM_UPDATEONREPETITION_DISABLED;
	  pTimerCfg.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
	  pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;//HRTIM_TIMFAULTENABLE_FAULT1|HRTIM_TIMFAULTENABLE_FAULT3
	                             // |HRTIM_TIMFAULTENABLE_FAULT4;
	  pTimerCfg.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
	  pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_ENABLED;
	  pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED;
	  pTimerCfg.UpdateTrigger = HRTIM_TIMUPDATETRIGGER_NONE;
	  pTimerCfg.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
	  pTimerCfg.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
	  pTimerCfg.ReSyncUpdate = HRTIM_TIMERESYNC_UPDATE_UNCONDITIONAL;

	  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pTimerCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chB1;
	  pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[1].CMP3xR);
	  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, &pTimerCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chC1;
	  pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[2].CMP3xR);
	  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, &pTimerCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimerCfg.DMASrcAddress = (uint32_t)&DUTY_SRC->chD1;
	  pTimerCfg.DMADstAddress = (uint32_t)&(hhrtim1.Instance->sTimerxRegs[3].CMP3xR);
	  pTimerCfg.DelayedProtectionMode = HRTIM_TIMER_D_E_DELAYEDPROTECTION_DISABLED;
	  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, &pTimerCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimerCfg.InterruptRequests = HRTIM_MASTER_IT_NONE;
	  pTimerCfg.DMARequests = HRTIM_TIM_DMA_NONE;
	  pTimerCfg.PreloadEnable = HRTIM_PRELOAD_DISABLED;
	  pTimerCfg.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
	  pTimerCfg.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
	  if (HAL_HRTIM_WaveformTimerConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, &pTimerCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 0;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_1, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.AutoDelayedMode = HRTIM_AUTODELAYEDMODE_REGULAR;
	  pCompareCfg.AutoDelayedTimeout = 0x0000;

	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_2, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 20000;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_COMPAREUNIT_3, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pDeadTimeCfg.Prescaler = HRTIM_TIMDEADTIME_PRESCALERRATIO_MUL8;
	  pDeadTimeCfg.RisingValue = 0x000;
	  pDeadTimeCfg.RisingSign = HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE;
	  pDeadTimeCfg.RisingLock = HRTIM_TIMDEADTIME_RISINGLOCK_WRITE;
	  pDeadTimeCfg.RisingSignLock = HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE;
	  pDeadTimeCfg.FallingValue = 0x000;
	  pDeadTimeCfg.FallingSign = HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE;
	  pDeadTimeCfg.FallingLock = HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE;
	  pDeadTimeCfg.FallingSignLock = HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE;
	  if (HAL_HRTIM_DeadTimeConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, &pDeadTimeCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_DeadTimeConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, &pDeadTimeCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_DeadTimeConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, &pDeadTimeCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_DeadTimeConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, &pDeadTimeCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pOutputCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
	  pOutputCfg.SetSource = HRTIM_OUTPUTSET_TIMCMP1;
	  pOutputCfg.ResetSource = HRTIM_OUTPUTRESET_TIMCMP3;
	  pOutputCfg.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
	  pOutputCfg.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
	  pOutputCfg.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_INACTIVE;
	  pOutputCfg.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
	  pOutputCfg.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC1, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD1, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pOutputCfg.SetSource = HRTIM_OUTPUTSET_NONE;
	  pOutputCfg.ResetSource = HRTIM_OUTPUTRESET_NONE;
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, HRTIM_OUTPUT_TE1, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pOutputCfg.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_INACTIVE;
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA2, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB2, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_OUTPUT_TC2, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformOutputConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_OUTPUT_TD2, &pOutputCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, &pTimeBaseCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformTimerControl(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, &pTimerCtl) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 0;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_1, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_2, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 20000;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_B, HRTIM_COMPAREUNIT_3, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, &pTimeBaseCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformTimerControl(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, &pTimerCtl) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 0;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_1, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_2, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 20000;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_3, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, &pTimeBaseCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformTimerControl(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, &pTimerCtl) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 0;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_2, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pCompareCfg.CompareValue = 20000;
	  if (HAL_HRTIM_WaveformCompareConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_3, &pCompareCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  pTimeBaseCfg.Period = 38857;
	  pTimeBaseCfg.PrescalerRatio = HRTIM_PRESCALERRATIO_MUL16;
	  if (HAL_HRTIM_TimeBaseConfig(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, &pTimeBaseCfg) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  if (HAL_HRTIM_WaveformTimerControl(&hhrtim1, HRTIM_TIMERINDEX_TIMER_E, &pTimerCtl) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN HRTIM1_Init 2 */

	  /* USER CODE END HRTIM1_Init 2 */
	  HAL_HRTIM_MspPostInit(&hhrtim1);


}

void PWM_DUTY_Processing (DMA_PWMDUTY_STRUCT *DUTY_SRC, uint32_t Timers, uint32_t Duty){

	switch (Timers){
		case HRTIM_TIMERID_TIMER_A:
			DUTY_SRC->chA1 = Duty;

		case HRTIM_TIMERID_TIMER_B:
			DUTY_SRC->chB1 = Duty;

		case HRTIM_TIMERID_TIMER_C:
			DUTY_SRC->chC1 = Duty;

		case HRTIM_TIMERID_TIMER_D:
			DUTY_SRC->chD1 = Duty;

		case HRTIM_TIMERID_TIMER_E:
			DUTY_SRC->chE1 = Duty;
	}

}

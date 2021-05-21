/*******************************************************************************
* File Name: GameTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_GameTimer_H)
#define CY_Timer_v2_60_GameTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 GameTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define GameTimer_Resolution                 32u
#define GameTimer_UsingFixedFunction         0u
#define GameTimer_UsingHWCaptureCounter      0u
#define GameTimer_SoftwareCaptureMode        0u
#define GameTimer_SoftwareTriggerMode        0u
#define GameTimer_UsingHWEnable              0u
#define GameTimer_EnableTriggerMode          0u
#define GameTimer_InterruptOnCaptureCount    0u
#define GameTimer_RunModeUsed                0u
#define GameTimer_ControlRegRemoved          0u

#if defined(GameTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define GameTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (GameTimer_UsingFixedFunction)
    #define GameTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define GameTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End GameTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!GameTimer_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (GameTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!GameTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}GameTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    GameTimer_Start(void) ;
void    GameTimer_Stop(void) ;

void    GameTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   GameTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define GameTimer_GetInterruptSource() GameTimer_ReadStatusRegister()

#if(!GameTimer_UDB_CONTROL_REG_REMOVED)
    uint8   GameTimer_ReadControlRegister(void) ;
    void    GameTimer_WriteControlRegister(uint8 control) ;
#endif /* (!GameTimer_UDB_CONTROL_REG_REMOVED) */

uint32  GameTimer_ReadPeriod(void) ;
void    GameTimer_WritePeriod(uint32 period) ;
uint32  GameTimer_ReadCounter(void) ;
void    GameTimer_WriteCounter(uint32 counter) ;
uint32  GameTimer_ReadCapture(void) ;
void    GameTimer_SoftwareCapture(void) ;

#if(!GameTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (GameTimer_SoftwareCaptureMode)
        void    GameTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!GameTimer_UsingFixedFunction) */

    #if (GameTimer_SoftwareTriggerMode)
        void    GameTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (GameTimer_SoftwareTriggerMode) */

    #if (GameTimer_EnableTriggerMode)
        void    GameTimer_EnableTrigger(void) ;
        void    GameTimer_DisableTrigger(void) ;
    #endif /* (GameTimer_EnableTriggerMode) */


    #if(GameTimer_InterruptOnCaptureCount)
        void    GameTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (GameTimer_InterruptOnCaptureCount) */

    #if (GameTimer_UsingHWCaptureCounter)
        void    GameTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   GameTimer_ReadCaptureCount(void) ;
    #endif /* (GameTimer_UsingHWCaptureCounter) */

    void GameTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void GameTimer_Init(void)          ;
void GameTimer_Enable(void)        ;
void GameTimer_SaveConfig(void)    ;
void GameTimer_RestoreConfig(void) ;
void GameTimer_Sleep(void)         ;
void GameTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define GameTimer__B_TIMER__CM_NONE 0
#define GameTimer__B_TIMER__CM_RISINGEDGE 1
#define GameTimer__B_TIMER__CM_FALLINGEDGE 2
#define GameTimer__B_TIMER__CM_EITHEREDGE 3
#define GameTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define GameTimer__B_TIMER__TM_NONE 0x00u
#define GameTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define GameTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define GameTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define GameTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define GameTimer_INIT_PERIOD             4294967295u
#define GameTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << GameTimer_CTRL_CAP_MODE_SHIFT))
#define GameTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << GameTimer_CTRL_TRIG_MODE_SHIFT))
#if (GameTimer_UsingFixedFunction)
    #define GameTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << GameTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << GameTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define GameTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << GameTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << GameTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << GameTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (GameTimer_UsingFixedFunction) */
#define GameTimer_INIT_CAPTURE_COUNT      (2u)
#define GameTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << GameTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (GameTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define GameTimer_STATUS         (*(reg8 *) GameTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define GameTimer_STATUS_MASK    (*(reg8 *) GameTimer_TimerHW__SR0 )
    #define GameTimer_CONTROL        (*(reg8 *) GameTimer_TimerHW__CFG0)
    #define GameTimer_CONTROL2       (*(reg8 *) GameTimer_TimerHW__CFG1)
    #define GameTimer_CONTROL2_PTR   ( (reg8 *) GameTimer_TimerHW__CFG1)
    #define GameTimer_RT1            (*(reg8 *) GameTimer_TimerHW__RT1)
    #define GameTimer_RT1_PTR        ( (reg8 *) GameTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define GameTimer_CONTROL3       (*(reg8 *) GameTimer_TimerHW__CFG2)
        #define GameTimer_CONTROL3_PTR   ( (reg8 *) GameTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define GameTimer_GLOBAL_ENABLE  (*(reg8 *) GameTimer_TimerHW__PM_ACT_CFG)
    #define GameTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) GameTimer_TimerHW__PM_STBY_CFG)

    #define GameTimer_CAPTURE_LSB         (* (reg16 *) GameTimer_TimerHW__CAP0 )
    #define GameTimer_CAPTURE_LSB_PTR       ((reg16 *) GameTimer_TimerHW__CAP0 )
    #define GameTimer_PERIOD_LSB          (* (reg16 *) GameTimer_TimerHW__PER0 )
    #define GameTimer_PERIOD_LSB_PTR        ((reg16 *) GameTimer_TimerHW__PER0 )
    #define GameTimer_COUNTER_LSB         (* (reg16 *) GameTimer_TimerHW__CNT_CMP0 )
    #define GameTimer_COUNTER_LSB_PTR       ((reg16 *) GameTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define GameTimer_BLOCK_EN_MASK                     GameTimer_TimerHW__PM_ACT_MSK
    #define GameTimer_BLOCK_STBY_EN_MASK                GameTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define GameTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define GameTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define GameTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define GameTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define GameTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define GameTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << GameTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define GameTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define GameTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << GameTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define GameTimer_CTRL_MODE_SHIFT                 0x01u
        #define GameTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << GameTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define GameTimer_CTRL_RCOD_SHIFT        0x02u
        #define GameTimer_CTRL_ENBL_SHIFT        0x00u
        #define GameTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define GameTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << GameTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define GameTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << GameTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define GameTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << GameTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define GameTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << GameTimer_CTRL_RCOD_SHIFT))
        #define GameTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << GameTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define GameTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define GameTimer_RT1_MASK                        ((uint8)((uint8)0x03u << GameTimer_RT1_SHIFT))
    #define GameTimer_SYNC                            ((uint8)((uint8)0x03u << GameTimer_RT1_SHIFT))
    #define GameTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define GameTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << GameTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define GameTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << GameTimer_SYNCDSI_SHIFT))

    #define GameTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << GameTimer_CTRL_MODE_SHIFT))
    #define GameTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << GameTimer_CTRL_MODE_SHIFT))
    #define GameTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << GameTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define GameTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define GameTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define GameTimer_STATUS_TC_INT_MASK_SHIFT        (GameTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define GameTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (GameTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define GameTimer_STATUS_TC                       ((uint8)((uint8)0x01u << GameTimer_STATUS_TC_SHIFT))
    #define GameTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << GameTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define GameTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << GameTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define GameTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << GameTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define GameTimer_STATUS              (* (reg8 *) GameTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define GameTimer_STATUS_MASK         (* (reg8 *) GameTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define GameTimer_STATUS_AUX_CTRL     (* (reg8 *) GameTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define GameTimer_CONTROL             (* (reg8 *) GameTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(GameTimer_Resolution <= 8u) /* 8-bit Timer */
        #define GameTimer_CAPTURE_LSB         (* (reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define GameTimer_CAPTURE_LSB_PTR       ((reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define GameTimer_PERIOD_LSB          (* (reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define GameTimer_PERIOD_LSB_PTR        ((reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define GameTimer_COUNTER_LSB         (* (reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define GameTimer_COUNTER_LSB_PTR       ((reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(GameTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define GameTimer_CAPTURE_LSB         (* (reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define GameTimer_CAPTURE_LSB_PTR       ((reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define GameTimer_PERIOD_LSB          (* (reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define GameTimer_PERIOD_LSB_PTR        ((reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define GameTimer_COUNTER_LSB         (* (reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define GameTimer_COUNTER_LSB_PTR       ((reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define GameTimer_CAPTURE_LSB         (* (reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define GameTimer_CAPTURE_LSB_PTR       ((reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define GameTimer_PERIOD_LSB          (* (reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define GameTimer_PERIOD_LSB_PTR        ((reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define GameTimer_COUNTER_LSB         (* (reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define GameTimer_COUNTER_LSB_PTR       ((reg16 *) GameTimer_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(GameTimer_Resolution <= 24u)/* 24-bit Timer */
        #define GameTimer_CAPTURE_LSB         (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define GameTimer_CAPTURE_LSB_PTR       ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define GameTimer_PERIOD_LSB          (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define GameTimer_PERIOD_LSB_PTR        ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define GameTimer_COUNTER_LSB         (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define GameTimer_COUNTER_LSB_PTR       ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define GameTimer_CAPTURE_LSB         (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define GameTimer_CAPTURE_LSB_PTR       ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define GameTimer_PERIOD_LSB          (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define GameTimer_PERIOD_LSB_PTR        ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define GameTimer_COUNTER_LSB         (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define GameTimer_COUNTER_LSB_PTR       ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define GameTimer_CAPTURE_LSB         (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define GameTimer_CAPTURE_LSB_PTR       ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define GameTimer_PERIOD_LSB          (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define GameTimer_PERIOD_LSB_PTR        ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define GameTimer_COUNTER_LSB         (* (reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define GameTimer_COUNTER_LSB_PTR       ((reg32 *) GameTimer_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define GameTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) GameTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (GameTimer_UsingHWCaptureCounter)
        #define GameTimer_CAP_COUNT              (*(reg8 *) GameTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define GameTimer_CAP_COUNT_PTR          ( (reg8 *) GameTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define GameTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) GameTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define GameTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) GameTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (GameTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define GameTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define GameTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define GameTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define GameTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define GameTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define GameTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << GameTimer_CTRL_INTCNT_SHIFT))
    #define GameTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << GameTimer_CTRL_TRIG_MODE_SHIFT))
    #define GameTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << GameTimer_CTRL_TRIG_EN_SHIFT))
    #define GameTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << GameTimer_CTRL_CAP_MODE_SHIFT))
    #define GameTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << GameTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define GameTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define GameTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define GameTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define GameTimer_STATUS_TC_INT_MASK_SHIFT       GameTimer_STATUS_TC_SHIFT
    #define GameTimer_STATUS_CAPTURE_INT_MASK_SHIFT  GameTimer_STATUS_CAPTURE_SHIFT
    #define GameTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define GameTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define GameTimer_STATUS_FIFOFULL_INT_MASK_SHIFT GameTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define GameTimer_STATUS_TC                      ((uint8)((uint8)0x01u << GameTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define GameTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << GameTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define GameTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << GameTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define GameTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << GameTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define GameTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << GameTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define GameTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << GameTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define GameTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << GameTimer_STATUS_FIFOFULL_SHIFT))

    #define GameTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define GameTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define GameTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define GameTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define GameTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define GameTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_GameTimer_H */


/* [] END OF FILE */

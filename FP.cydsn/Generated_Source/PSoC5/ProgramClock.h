/*******************************************************************************
* File Name: ProgramClock.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_ProgramClock_H)
#define CY_COUNTER_ProgramClock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ProgramClock_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed ProgramClock_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef ProgramClock_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* ProgramClock_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define ProgramClock_Resolution            32u
#define ProgramClock_UsingFixedFunction    0u
#define ProgramClock_ControlRegRemoved     0u
#define ProgramClock_COMPARE_MODE_SOFTWARE 0u
#define ProgramClock_CAPTURE_MODE_SOFTWARE 0u
#define ProgramClock_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint32 CounterUdb;         /* Current Counter Value */

    #if (!ProgramClock_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!ProgramClock_ControlRegRemoved) */

}ProgramClock_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    ProgramClock_Start(void) ;
void    ProgramClock_Stop(void) ;
void    ProgramClock_SetInterruptMode(uint8 interruptsMask) ;
uint8   ProgramClock_ReadStatusRegister(void) ;
#define ProgramClock_GetInterruptSource() ProgramClock_ReadStatusRegister()
#if(!ProgramClock_ControlRegRemoved)
    uint8   ProgramClock_ReadControlRegister(void) ;
    void    ProgramClock_WriteControlRegister(uint8 control) \
        ;
#endif /* (!ProgramClock_ControlRegRemoved) */
#if (!(ProgramClock_UsingFixedFunction && (CY_PSOC5A)))
    void    ProgramClock_WriteCounter(uint32 counter) \
            ; 
#endif /* (!(ProgramClock_UsingFixedFunction && (CY_PSOC5A))) */
uint32  ProgramClock_ReadCounter(void) ;
uint32  ProgramClock_ReadCapture(void) ;
void    ProgramClock_WritePeriod(uint32 period) \
    ;
uint32  ProgramClock_ReadPeriod( void ) ;
#if (!ProgramClock_UsingFixedFunction)
    void    ProgramClock_WriteCompare(uint32 compare) \
        ;
    uint32  ProgramClock_ReadCompare( void ) \
        ;
#endif /* (!ProgramClock_UsingFixedFunction) */

#if (ProgramClock_COMPARE_MODE_SOFTWARE)
    void    ProgramClock_SetCompareMode(uint8 compareMode) ;
#endif /* (ProgramClock_COMPARE_MODE_SOFTWARE) */
#if (ProgramClock_CAPTURE_MODE_SOFTWARE)
    void    ProgramClock_SetCaptureMode(uint8 captureMode) ;
#endif /* (ProgramClock_CAPTURE_MODE_SOFTWARE) */
void ProgramClock_ClearFIFO(void)     ;
void ProgramClock_Init(void)          ;
void ProgramClock_Enable(void)        ;
void ProgramClock_SaveConfig(void)    ;
void ProgramClock_RestoreConfig(void) ;
void ProgramClock_Sleep(void)         ;
void ProgramClock_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define ProgramClock__B_COUNTER__LESS_THAN 1
#define ProgramClock__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define ProgramClock__B_COUNTER__EQUAL 0
#define ProgramClock__B_COUNTER__GREATER_THAN 3
#define ProgramClock__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define ProgramClock__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define ProgramClock_CMP_MODE_LT 1u
#define ProgramClock_CMP_MODE_LTE 2u
#define ProgramClock_CMP_MODE_EQ 0u
#define ProgramClock_CMP_MODE_GT 3u
#define ProgramClock_CMP_MODE_GTE 4u
#define ProgramClock_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define ProgramClock__B_COUNTER__NONE 0
#define ProgramClock__B_COUNTER__RISING_EDGE 1
#define ProgramClock__B_COUNTER__FALLING_EDGE 2
#define ProgramClock__B_COUNTER__EITHER_EDGE 3
#define ProgramClock__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define ProgramClock_CAP_MODE_NONE 0u
#define ProgramClock_CAP_MODE_RISE 1u
#define ProgramClock_CAP_MODE_FALL 2u
#define ProgramClock_CAP_MODE_BOTH 3u
#define ProgramClock_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define ProgramClock_CAPTURE_MODE_CONF       0u
#define ProgramClock_INIT_PERIOD_VALUE       4294967295u
#define ProgramClock_INIT_COUNTER_VALUE      0u
#if (ProgramClock_UsingFixedFunction)
#define ProgramClock_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << ProgramClock_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define ProgramClock_INIT_COMPARE_VALUE      4294967295u
#define ProgramClock_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << ProgramClock_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << ProgramClock_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << ProgramClock_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << ProgramClock_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << ProgramClock_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define ProgramClock_DEFAULT_COMPARE_MODE    3u

#if( 0 != ProgramClock_CAPTURE_MODE_CONF)
    #define ProgramClock_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << ProgramClock_CTRL_CAPMODE0_SHIFT))
#else    
    #define ProgramClock_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != ProgramClock_CAPTURE_MODE_CONF) */

#endif /* (ProgramClock_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (ProgramClock_UsingFixedFunction)
    #define ProgramClock_STATICCOUNT_LSB     (*(reg16 *) ProgramClock_CounterHW__CAP0 )
    #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg16 *) ProgramClock_CounterHW__CAP0 )
    #define ProgramClock_PERIOD_LSB          (*(reg16 *) ProgramClock_CounterHW__PER0 )
    #define ProgramClock_PERIOD_LSB_PTR      ( (reg16 *) ProgramClock_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define ProgramClock_COMPARE_LSB         (*(reg16 *) ProgramClock_CounterHW__CNT_CMP0 )
    #define ProgramClock_COMPARE_LSB_PTR     ( (reg16 *) ProgramClock_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define ProgramClock_COUNTER_LSB         (*(reg16 *) ProgramClock_CounterHW__CNT_CMP0 )
    #define ProgramClock_COUNTER_LSB_PTR     ( (reg16 *) ProgramClock_CounterHW__CNT_CMP0 )
    #define ProgramClock_RT1                 (*(reg8 *) ProgramClock_CounterHW__RT1)
    #define ProgramClock_RT1_PTR             ( (reg8 *) ProgramClock_CounterHW__RT1)
#else
    
    #if (ProgramClock_Resolution <= 8u) /* 8-bit Counter */
    
        #define ProgramClock_STATICCOUNT_LSB     (*(reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define ProgramClock_PERIOD_LSB          (*(reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define ProgramClock_PERIOD_LSB_PTR      ( (reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define ProgramClock_COMPARE_LSB         (*(reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define ProgramClock_COMPARE_LSB_PTR     ( (reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define ProgramClock_COUNTER_LSB         (*(reg8 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )  
        #define ProgramClock_COUNTER_LSB_PTR     ( (reg8 *)\
            ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )
    
    #elif(ProgramClock_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define ProgramClock_STATICCOUNT_LSB     (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define ProgramClock_PERIOD_LSB          (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define ProgramClock_PERIOD_LSB_PTR      ( (reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define ProgramClock_COMPARE_LSB         (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define ProgramClock_COMPARE_LSB_PTR     ( (reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define ProgramClock_COUNTER_LSB         (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )  
            #define ProgramClock_COUNTER_LSB_PTR     ( (reg16 *)\
                ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define ProgramClock_STATICCOUNT_LSB     (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_F0_REG )
            #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_F0_REG )
            #define ProgramClock_PERIOD_LSB          (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_D0_REG )
            #define ProgramClock_PERIOD_LSB_PTR      ( (reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_D0_REG )
            #define ProgramClock_COMPARE_LSB         (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_D1_REG )
            #define ProgramClock_COMPARE_LSB_PTR     ( (reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_D1_REG )
            #define ProgramClock_COUNTER_LSB         (*(reg16 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_A0_REG )  
            #define ProgramClock_COUNTER_LSB_PTR     ( (reg16 *)\
                ProgramClock_CounterUDB_sC32_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(ProgramClock_Resolution <= 24u) /* 24-bit Counter */
        
        #define ProgramClock_STATICCOUNT_LSB     (*(reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
        #define ProgramClock_PERIOD_LSB          (*(reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define ProgramClock_PERIOD_LSB_PTR      ( (reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
        #define ProgramClock_COMPARE_LSB         (*(reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define ProgramClock_COMPARE_LSB_PTR     ( (reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
        #define ProgramClock_COUNTER_LSB         (*(reg32 *) \
            ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )  
        #define ProgramClock_COUNTER_LSB_PTR     ( (reg32 *)\
            ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define ProgramClock_STATICCOUNT_LSB     (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__F0_REG )
            #define ProgramClock_PERIOD_LSB          (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define ProgramClock_PERIOD_LSB_PTR      ( (reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D0_REG )
            #define ProgramClock_COMPARE_LSB         (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define ProgramClock_COMPARE_LSB_PTR     ( (reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__D1_REG )
            #define ProgramClock_COUNTER_LSB         (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )  
            #define ProgramClock_COUNTER_LSB_PTR     ( (reg32 *)\
                ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define ProgramClock_STATICCOUNT_LSB     (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_F0_REG )
            #define ProgramClock_STATICCOUNT_LSB_PTR ( (reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_F0_REG )
            #define ProgramClock_PERIOD_LSB          (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_D0_REG )
            #define ProgramClock_PERIOD_LSB_PTR      ( (reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_D0_REG )
            #define ProgramClock_COMPARE_LSB         (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_D1_REG )
            #define ProgramClock_COMPARE_LSB_PTR     ( (reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_D1_REG )
            #define ProgramClock_COUNTER_LSB         (*(reg32 *) \
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_A0_REG )  
            #define ProgramClock_COUNTER_LSB_PTR     ( (reg32 *)\
                ProgramClock_CounterUDB_sC32_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define ProgramClock_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                ProgramClock_CounterUDB_sC32_counterdp_u0__A0_REG )
				
    #define ProgramClock_AUX_CONTROLDP0 \
        (*(reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u0__DP_AUX_CTL_REG)
    
    #define ProgramClock_AUX_CONTROLDP0_PTR \
        ( (reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (ProgramClock_Resolution == 16 || ProgramClock_Resolution == 24 || ProgramClock_Resolution == 32)
       #define ProgramClock_AUX_CONTROLDP1 \
           (*(reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u1__DP_AUX_CTL_REG)
       #define ProgramClock_AUX_CONTROLDP1_PTR \
           ( (reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (ProgramClock_Resolution == 16 || ProgramClock_Resolution == 24 || ProgramClock_Resolution == 32) */
    
    #if (ProgramClock_Resolution == 24 || ProgramClock_Resolution == 32)
       #define ProgramClock_AUX_CONTROLDP2 \
           (*(reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u2__DP_AUX_CTL_REG)
       #define ProgramClock_AUX_CONTROLDP2_PTR \
           ( (reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (ProgramClock_Resolution == 24 || ProgramClock_Resolution == 32) */
    
    #if (ProgramClock_Resolution == 32)
       #define ProgramClock_AUX_CONTROLDP3 \
           (*(reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u3__DP_AUX_CTL_REG)
       #define ProgramClock_AUX_CONTROLDP3_PTR \
           ( (reg8 *) ProgramClock_CounterUDB_sC32_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (ProgramClock_Resolution == 32) */

#endif  /* (ProgramClock_UsingFixedFunction) */

#if (ProgramClock_UsingFixedFunction)
    #define ProgramClock_STATUS         (*(reg8 *) ProgramClock_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define ProgramClock_STATUS_MASK             (*(reg8 *) ProgramClock_CounterHW__SR0 )
    #define ProgramClock_STATUS_MASK_PTR         ( (reg8 *) ProgramClock_CounterHW__SR0 )
    #define ProgramClock_CONTROL                 (*(reg8 *) ProgramClock_CounterHW__CFG0)
    #define ProgramClock_CONTROL_PTR             ( (reg8 *) ProgramClock_CounterHW__CFG0)
    #define ProgramClock_CONTROL2                (*(reg8 *) ProgramClock_CounterHW__CFG1)
    #define ProgramClock_CONTROL2_PTR            ( (reg8 *) ProgramClock_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define ProgramClock_CONTROL3       (*(reg8 *) ProgramClock_CounterHW__CFG2)
        #define ProgramClock_CONTROL3_PTR   ( (reg8 *) ProgramClock_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ProgramClock_GLOBAL_ENABLE           (*(reg8 *) ProgramClock_CounterHW__PM_ACT_CFG)
    #define ProgramClock_GLOBAL_ENABLE_PTR       ( (reg8 *) ProgramClock_CounterHW__PM_ACT_CFG)
    #define ProgramClock_GLOBAL_STBY_ENABLE      (*(reg8 *) ProgramClock_CounterHW__PM_STBY_CFG)
    #define ProgramClock_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) ProgramClock_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define ProgramClock_BLOCK_EN_MASK          ProgramClock_CounterHW__PM_ACT_MSK
    #define ProgramClock_BLOCK_STBY_EN_MASK     ProgramClock_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define ProgramClock_CTRL_ENABLE_SHIFT      0x00u
    #define ProgramClock_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define ProgramClock_CTRL_ENABLE            ((uint8)((uint8)0x01u << ProgramClock_CTRL_ENABLE_SHIFT))         
    #define ProgramClock_ONESHOT                ((uint8)((uint8)0x01u << ProgramClock_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define ProgramClock_CTRL_MODE_SHIFT        0x01u    
        #define ProgramClock_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << ProgramClock_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define ProgramClock_CTRL_MODE_SHIFT        0x00u    
        #define ProgramClock_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << ProgramClock_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define ProgramClock_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define ProgramClock_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << ProgramClock_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define ProgramClock_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define ProgramClock_STATUS_ZERO_INT_EN_MASK_SHIFT      (ProgramClock_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define ProgramClock_STATUS_ZERO            ((uint8)((uint8)0x01u << ProgramClock_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define ProgramClock_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)ProgramClock_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define ProgramClock_RT1_SHIFT            0x04u
    #define ProgramClock_RT1_MASK             ((uint8)((uint8)0x03u << ProgramClock_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define ProgramClock_SYNC                 ((uint8)((uint8)0x03u << ProgramClock_RT1_SHIFT))
    #define ProgramClock_SYNCDSI_SHIFT        0x00u
    #define ProgramClock_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << ProgramClock_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define ProgramClock_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << ProgramClock_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !ProgramClock_UsingFixedFunction */
    #define ProgramClock_STATUS               (* (reg8 *) ProgramClock_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define ProgramClock_STATUS_PTR           (  (reg8 *) ProgramClock_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define ProgramClock_STATUS_MASK          (* (reg8 *) ProgramClock_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define ProgramClock_STATUS_MASK_PTR      (  (reg8 *) ProgramClock_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define ProgramClock_STATUS_AUX_CTRL      (*(reg8 *) ProgramClock_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define ProgramClock_STATUS_AUX_CTRL_PTR  ( (reg8 *) ProgramClock_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define ProgramClock_CONTROL              (* (reg8 *) ProgramClock_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define ProgramClock_CONTROL_PTR          (  (reg8 *) ProgramClock_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define ProgramClock_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define ProgramClock_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define ProgramClock_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define ProgramClock_CTRL_CMPMODE_MASK      0x07u 
    #define ProgramClock_CTRL_CAPMODE_MASK      0x03u  
    #define ProgramClock_CTRL_RESET             ((uint8)((uint8)0x01u << ProgramClock_CTRL_RESET_SHIFT))  
    #define ProgramClock_CTRL_ENABLE            ((uint8)((uint8)0x01u << ProgramClock_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define ProgramClock_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define ProgramClock_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define ProgramClock_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define ProgramClock_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define ProgramClock_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define ProgramClock_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define ProgramClock_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ProgramClock_STATUS_CMP_INT_EN_MASK_SHIFT       ProgramClock_STATUS_CMP_SHIFT       
    #define ProgramClock_STATUS_ZERO_INT_EN_MASK_SHIFT      ProgramClock_STATUS_ZERO_SHIFT      
    #define ProgramClock_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  ProgramClock_STATUS_OVERFLOW_SHIFT  
    #define ProgramClock_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT ProgramClock_STATUS_UNDERFLOW_SHIFT 
    #define ProgramClock_STATUS_CAPTURE_INT_EN_MASK_SHIFT   ProgramClock_STATUS_CAPTURE_SHIFT   
    #define ProgramClock_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  ProgramClock_STATUS_FIFOFULL_SHIFT  
    #define ProgramClock_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  ProgramClock_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define ProgramClock_STATUS_CMP             ((uint8)((uint8)0x01u << ProgramClock_STATUS_CMP_SHIFT))  
    #define ProgramClock_STATUS_ZERO            ((uint8)((uint8)0x01u << ProgramClock_STATUS_ZERO_SHIFT)) 
    #define ProgramClock_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << ProgramClock_STATUS_OVERFLOW_SHIFT)) 
    #define ProgramClock_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << ProgramClock_STATUS_UNDERFLOW_SHIFT)) 
    #define ProgramClock_STATUS_CAPTURE         ((uint8)((uint8)0x01u << ProgramClock_STATUS_CAPTURE_SHIFT)) 
    #define ProgramClock_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << ProgramClock_STATUS_FIFOFULL_SHIFT))
    #define ProgramClock_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << ProgramClock_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ProgramClock_STATUS_CMP_INT_EN_MASK            ProgramClock_STATUS_CMP                    
    #define ProgramClock_STATUS_ZERO_INT_EN_MASK           ProgramClock_STATUS_ZERO            
    #define ProgramClock_STATUS_OVERFLOW_INT_EN_MASK       ProgramClock_STATUS_OVERFLOW        
    #define ProgramClock_STATUS_UNDERFLOW_INT_EN_MASK      ProgramClock_STATUS_UNDERFLOW       
    #define ProgramClock_STATUS_CAPTURE_INT_EN_MASK        ProgramClock_STATUS_CAPTURE         
    #define ProgramClock_STATUS_FIFOFULL_INT_EN_MASK       ProgramClock_STATUS_FIFOFULL        
    #define ProgramClock_STATUS_FIFONEMP_INT_EN_MASK       ProgramClock_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define ProgramClock_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define ProgramClock_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define ProgramClock_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define ProgramClock_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define ProgramClock_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define ProgramClock_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* ProgramClock_UsingFixedFunction */

#endif  /* CY_COUNTER_ProgramClock_H */


/* [] END OF FILE */


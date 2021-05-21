/*******************************************************************************
* File Name: C_Square.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_C_Square_H)
#define CY_CLOCK_C_Square_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void C_Square_Start(void) ;
void C_Square_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void C_Square_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void C_Square_StandbyPower(uint8 state) ;
void C_Square_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 C_Square_GetDividerRegister(void) ;
void C_Square_SetModeRegister(uint8 modeBitMask) ;
void C_Square_ClearModeRegister(uint8 modeBitMask) ;
uint8 C_Square_GetModeRegister(void) ;
void C_Square_SetSourceRegister(uint8 clkSource) ;
uint8 C_Square_GetSourceRegister(void) ;
#if defined(C_Square__CFG3)
void C_Square_SetPhaseRegister(uint8 clkPhase) ;
uint8 C_Square_GetPhaseRegister(void) ;
#endif /* defined(C_Square__CFG3) */

#define C_Square_Enable()                       C_Square_Start()
#define C_Square_Disable()                      C_Square_Stop()
#define C_Square_SetDivider(clkDivider)         C_Square_SetDividerRegister(clkDivider, 1u)
#define C_Square_SetDividerValue(clkDivider)    C_Square_SetDividerRegister((clkDivider) - 1u, 1u)
#define C_Square_SetMode(clkMode)               C_Square_SetModeRegister(clkMode)
#define C_Square_SetSource(clkSource)           C_Square_SetSourceRegister(clkSource)
#if defined(C_Square__CFG3)
#define C_Square_SetPhase(clkPhase)             C_Square_SetPhaseRegister(clkPhase)
#define C_Square_SetPhaseValue(clkPhase)        C_Square_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(C_Square__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define C_Square_CLKEN              (* (reg8 *) C_Square__PM_ACT_CFG)
#define C_Square_CLKEN_PTR          ((reg8 *) C_Square__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define C_Square_CLKSTBY            (* (reg8 *) C_Square__PM_STBY_CFG)
#define C_Square_CLKSTBY_PTR        ((reg8 *) C_Square__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define C_Square_DIV_LSB            (* (reg8 *) C_Square__CFG0)
#define C_Square_DIV_LSB_PTR        ((reg8 *) C_Square__CFG0)
#define C_Square_DIV_PTR            ((reg16 *) C_Square__CFG0)

/* Clock MSB divider configuration register. */
#define C_Square_DIV_MSB            (* (reg8 *) C_Square__CFG1)
#define C_Square_DIV_MSB_PTR        ((reg8 *) C_Square__CFG1)

/* Mode and source configuration register */
#define C_Square_MOD_SRC            (* (reg8 *) C_Square__CFG2)
#define C_Square_MOD_SRC_PTR        ((reg8 *) C_Square__CFG2)

#if defined(C_Square__CFG3)
/* Analog clock phase configuration register */
#define C_Square_PHASE              (* (reg8 *) C_Square__CFG3)
#define C_Square_PHASE_PTR          ((reg8 *) C_Square__CFG3)
#endif /* defined(C_Square__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define C_Square_CLKEN_MASK         C_Square__PM_ACT_MSK
#define C_Square_CLKSTBY_MASK       C_Square__PM_STBY_MSK

/* CFG2 field masks */
#define C_Square_SRC_SEL_MSK        C_Square__CFG2_SRC_SEL_MASK
#define C_Square_MODE_MASK          (~(C_Square_SRC_SEL_MSK))

#if defined(C_Square__CFG3)
/* CFG3 phase mask */
#define C_Square_PHASE_MASK         C_Square__CFG3_PHASE_DLY_MASK
#endif /* defined(C_Square__CFG3) */

#endif /* CY_CLOCK_C_Square_H */


/* [] END OF FILE */

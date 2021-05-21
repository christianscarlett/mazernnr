/*******************************************************************************
* File Name: D_Square.h
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

#if !defined(CY_CLOCK_D_Square_H)
#define CY_CLOCK_D_Square_H

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

void D_Square_Start(void) ;
void D_Square_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void D_Square_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void D_Square_StandbyPower(uint8 state) ;
void D_Square_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 D_Square_GetDividerRegister(void) ;
void D_Square_SetModeRegister(uint8 modeBitMask) ;
void D_Square_ClearModeRegister(uint8 modeBitMask) ;
uint8 D_Square_GetModeRegister(void) ;
void D_Square_SetSourceRegister(uint8 clkSource) ;
uint8 D_Square_GetSourceRegister(void) ;
#if defined(D_Square__CFG3)
void D_Square_SetPhaseRegister(uint8 clkPhase) ;
uint8 D_Square_GetPhaseRegister(void) ;
#endif /* defined(D_Square__CFG3) */

#define D_Square_Enable()                       D_Square_Start()
#define D_Square_Disable()                      D_Square_Stop()
#define D_Square_SetDivider(clkDivider)         D_Square_SetDividerRegister(clkDivider, 1u)
#define D_Square_SetDividerValue(clkDivider)    D_Square_SetDividerRegister((clkDivider) - 1u, 1u)
#define D_Square_SetMode(clkMode)               D_Square_SetModeRegister(clkMode)
#define D_Square_SetSource(clkSource)           D_Square_SetSourceRegister(clkSource)
#if defined(D_Square__CFG3)
#define D_Square_SetPhase(clkPhase)             D_Square_SetPhaseRegister(clkPhase)
#define D_Square_SetPhaseValue(clkPhase)        D_Square_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(D_Square__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define D_Square_CLKEN              (* (reg8 *) D_Square__PM_ACT_CFG)
#define D_Square_CLKEN_PTR          ((reg8 *) D_Square__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define D_Square_CLKSTBY            (* (reg8 *) D_Square__PM_STBY_CFG)
#define D_Square_CLKSTBY_PTR        ((reg8 *) D_Square__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define D_Square_DIV_LSB            (* (reg8 *) D_Square__CFG0)
#define D_Square_DIV_LSB_PTR        ((reg8 *) D_Square__CFG0)
#define D_Square_DIV_PTR            ((reg16 *) D_Square__CFG0)

/* Clock MSB divider configuration register. */
#define D_Square_DIV_MSB            (* (reg8 *) D_Square__CFG1)
#define D_Square_DIV_MSB_PTR        ((reg8 *) D_Square__CFG1)

/* Mode and source configuration register */
#define D_Square_MOD_SRC            (* (reg8 *) D_Square__CFG2)
#define D_Square_MOD_SRC_PTR        ((reg8 *) D_Square__CFG2)

#if defined(D_Square__CFG3)
/* Analog clock phase configuration register */
#define D_Square_PHASE              (* (reg8 *) D_Square__CFG3)
#define D_Square_PHASE_PTR          ((reg8 *) D_Square__CFG3)
#endif /* defined(D_Square__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define D_Square_CLKEN_MASK         D_Square__PM_ACT_MSK
#define D_Square_CLKSTBY_MASK       D_Square__PM_STBY_MSK

/* CFG2 field masks */
#define D_Square_SRC_SEL_MSK        D_Square__CFG2_SRC_SEL_MASK
#define D_Square_MODE_MASK          (~(D_Square_SRC_SEL_MSK))

#if defined(D_Square__CFG3)
/* CFG3 phase mask */
#define D_Square_PHASE_MASK         D_Square__CFG3_PHASE_DLY_MASK
#endif /* defined(D_Square__CFG3) */

#endif /* CY_CLOCK_D_Square_H */


/* [] END OF FILE */

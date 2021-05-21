/*******************************************************************************
* File Name: P.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P_H) /* Pins P_H */
#define CY_PINS_P_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P__PORT == 15 && ((P__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P_Write(uint8 value);
void    P_SetDriveMode(uint8 mode);
uint8   P_ReadDataReg(void);
uint8   P_Read(void);
void    P_SetInterruptMode(uint16 position, uint16 mode);
uint8   P_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P_SetDriveMode() function.
     *  @{
     */
        #define P_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P_DM_RES_UP          PIN_DM_RES_UP
        #define P_DM_RES_DWN         PIN_DM_RES_DWN
        #define P_DM_OD_LO           PIN_DM_OD_LO
        #define P_DM_OD_HI           PIN_DM_OD_HI
        #define P_DM_STRONG          PIN_DM_STRONG
        #define P_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P_MASK               P__MASK
#define P_SHIFT              P__SHIFT
#define P_WIDTH              1u

/* Interrupt constants */
#if defined(P__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P_SetInterruptMode() function.
     *  @{
     */
        #define P_INTR_NONE      (uint16)(0x0000u)
        #define P_INTR_RISING    (uint16)(0x0001u)
        #define P_INTR_FALLING   (uint16)(0x0002u)
        #define P_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P_INTR_MASK      (0x01u) 
#endif /* (P__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P_PS                     (* (reg8 *) P__PS)
/* Data Register */
#define P_DR                     (* (reg8 *) P__DR)
/* Port Number */
#define P_PRT_NUM                (* (reg8 *) P__PRT) 
/* Connect to Analog Globals */                                                  
#define P_AG                     (* (reg8 *) P__AG)                       
/* Analog MUX bux enable */
#define P_AMUX                   (* (reg8 *) P__AMUX) 
/* Bidirectional Enable */                                                        
#define P_BIE                    (* (reg8 *) P__BIE)
/* Bit-mask for Aliased Register Access */
#define P_BIT_MASK               (* (reg8 *) P__BIT_MASK)
/* Bypass Enable */
#define P_BYP                    (* (reg8 *) P__BYP)
/* Port wide control signals */                                                   
#define P_CTL                    (* (reg8 *) P__CTL)
/* Drive Modes */
#define P_DM0                    (* (reg8 *) P__DM0) 
#define P_DM1                    (* (reg8 *) P__DM1)
#define P_DM2                    (* (reg8 *) P__DM2) 
/* Input Buffer Disable Override */
#define P_INP_DIS                (* (reg8 *) P__INP_DIS)
/* LCD Common or Segment Drive */
#define P_LCD_COM_SEG            (* (reg8 *) P__LCD_COM_SEG)
/* Enable Segment LCD */
#define P_LCD_EN                 (* (reg8 *) P__LCD_EN)
/* Slew Rate Control */
#define P_SLW                    (* (reg8 *) P__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P_PRTDSI__CAPS_SEL       (* (reg8 *) P__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P_PRTDSI__OE_SEL0        (* (reg8 *) P__PRTDSI__OE_SEL0) 
#define P_PRTDSI__OE_SEL1        (* (reg8 *) P__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P_PRTDSI__OUT_SEL0       (* (reg8 *) P__PRTDSI__OUT_SEL0) 
#define P_PRTDSI__OUT_SEL1       (* (reg8 *) P__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P_PRTDSI__SYNC_OUT       (* (reg8 *) P__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P__SIO_CFG)
    #define P_SIO_HYST_EN        (* (reg8 *) P__SIO_HYST_EN)
    #define P_SIO_REG_HIFREQ     (* (reg8 *) P__SIO_REG_HIFREQ)
    #define P_SIO_CFG            (* (reg8 *) P__SIO_CFG)
    #define P_SIO_DIFF           (* (reg8 *) P__SIO_DIFF)
#endif /* (P__SIO_CFG) */

/* Interrupt Registers */
#if defined(P__INTSTAT)
    #define P_INTSTAT            (* (reg8 *) P__INTSTAT)
    #define P_SNAP               (* (reg8 *) P__SNAP)
    
	#define P_0_INTTYPE_REG 		(* (reg8 *) P__0__INTTYPE)
#endif /* (P__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P_H */


/* [] END OF FILE */

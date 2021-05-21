/*******************************************************************************
* File Name: L.h  
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

#if !defined(CY_PINS_L_H) /* Pins L_H */
#define CY_PINS_L_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "L_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 L__PORT == 15 && ((L__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    L_Write(uint8 value);
void    L_SetDriveMode(uint8 mode);
uint8   L_ReadDataReg(void);
uint8   L_Read(void);
void    L_SetInterruptMode(uint16 position, uint16 mode);
uint8   L_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the L_SetDriveMode() function.
     *  @{
     */
        #define L_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define L_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define L_DM_RES_UP          PIN_DM_RES_UP
        #define L_DM_RES_DWN         PIN_DM_RES_DWN
        #define L_DM_OD_LO           PIN_DM_OD_LO
        #define L_DM_OD_HI           PIN_DM_OD_HI
        #define L_DM_STRONG          PIN_DM_STRONG
        #define L_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define L_MASK               L__MASK
#define L_SHIFT              L__SHIFT
#define L_WIDTH              1u

/* Interrupt constants */
#if defined(L__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in L_SetInterruptMode() function.
     *  @{
     */
        #define L_INTR_NONE      (uint16)(0x0000u)
        #define L_INTR_RISING    (uint16)(0x0001u)
        #define L_INTR_FALLING   (uint16)(0x0002u)
        #define L_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define L_INTR_MASK      (0x01u) 
#endif /* (L__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define L_PS                     (* (reg8 *) L__PS)
/* Data Register */
#define L_DR                     (* (reg8 *) L__DR)
/* Port Number */
#define L_PRT_NUM                (* (reg8 *) L__PRT) 
/* Connect to Analog Globals */                                                  
#define L_AG                     (* (reg8 *) L__AG)                       
/* Analog MUX bux enable */
#define L_AMUX                   (* (reg8 *) L__AMUX) 
/* Bidirectional Enable */                                                        
#define L_BIE                    (* (reg8 *) L__BIE)
/* Bit-mask for Aliased Register Access */
#define L_BIT_MASK               (* (reg8 *) L__BIT_MASK)
/* Bypass Enable */
#define L_BYP                    (* (reg8 *) L__BYP)
/* Port wide control signals */                                                   
#define L_CTL                    (* (reg8 *) L__CTL)
/* Drive Modes */
#define L_DM0                    (* (reg8 *) L__DM0) 
#define L_DM1                    (* (reg8 *) L__DM1)
#define L_DM2                    (* (reg8 *) L__DM2) 
/* Input Buffer Disable Override */
#define L_INP_DIS                (* (reg8 *) L__INP_DIS)
/* LCD Common or Segment Drive */
#define L_LCD_COM_SEG            (* (reg8 *) L__LCD_COM_SEG)
/* Enable Segment LCD */
#define L_LCD_EN                 (* (reg8 *) L__LCD_EN)
/* Slew Rate Control */
#define L_SLW                    (* (reg8 *) L__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define L_PRTDSI__CAPS_SEL       (* (reg8 *) L__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define L_PRTDSI__DBL_SYNC_IN    (* (reg8 *) L__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define L_PRTDSI__OE_SEL0        (* (reg8 *) L__PRTDSI__OE_SEL0) 
#define L_PRTDSI__OE_SEL1        (* (reg8 *) L__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define L_PRTDSI__OUT_SEL0       (* (reg8 *) L__PRTDSI__OUT_SEL0) 
#define L_PRTDSI__OUT_SEL1       (* (reg8 *) L__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define L_PRTDSI__SYNC_OUT       (* (reg8 *) L__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(L__SIO_CFG)
    #define L_SIO_HYST_EN        (* (reg8 *) L__SIO_HYST_EN)
    #define L_SIO_REG_HIFREQ     (* (reg8 *) L__SIO_REG_HIFREQ)
    #define L_SIO_CFG            (* (reg8 *) L__SIO_CFG)
    #define L_SIO_DIFF           (* (reg8 *) L__SIO_DIFF)
#endif /* (L__SIO_CFG) */

/* Interrupt Registers */
#if defined(L__INTSTAT)
    #define L_INTSTAT            (* (reg8 *) L__INTSTAT)
    #define L_SNAP               (* (reg8 *) L__SNAP)
    
	#define L_0_INTTYPE_REG 		(* (reg8 *) L__0__INTTYPE)
#endif /* (L__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_L_H */


/* [] END OF FILE */

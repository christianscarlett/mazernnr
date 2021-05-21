/*******************************************************************************
* File Name: F.h  
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

#if !defined(CY_PINS_F_H) /* Pins F_H */
#define CY_PINS_F_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "F_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 F__PORT == 15 && ((F__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    F_Write(uint8 value);
void    F_SetDriveMode(uint8 mode);
uint8   F_ReadDataReg(void);
uint8   F_Read(void);
void    F_SetInterruptMode(uint16 position, uint16 mode);
uint8   F_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the F_SetDriveMode() function.
     *  @{
     */
        #define F_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define F_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define F_DM_RES_UP          PIN_DM_RES_UP
        #define F_DM_RES_DWN         PIN_DM_RES_DWN
        #define F_DM_OD_LO           PIN_DM_OD_LO
        #define F_DM_OD_HI           PIN_DM_OD_HI
        #define F_DM_STRONG          PIN_DM_STRONG
        #define F_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define F_MASK               F__MASK
#define F_SHIFT              F__SHIFT
#define F_WIDTH              1u

/* Interrupt constants */
#if defined(F__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in F_SetInterruptMode() function.
     *  @{
     */
        #define F_INTR_NONE      (uint16)(0x0000u)
        #define F_INTR_RISING    (uint16)(0x0001u)
        #define F_INTR_FALLING   (uint16)(0x0002u)
        #define F_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define F_INTR_MASK      (0x01u) 
#endif /* (F__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define F_PS                     (* (reg8 *) F__PS)
/* Data Register */
#define F_DR                     (* (reg8 *) F__DR)
/* Port Number */
#define F_PRT_NUM                (* (reg8 *) F__PRT) 
/* Connect to Analog Globals */                                                  
#define F_AG                     (* (reg8 *) F__AG)                       
/* Analog MUX bux enable */
#define F_AMUX                   (* (reg8 *) F__AMUX) 
/* Bidirectional Enable */                                                        
#define F_BIE                    (* (reg8 *) F__BIE)
/* Bit-mask for Aliased Register Access */
#define F_BIT_MASK               (* (reg8 *) F__BIT_MASK)
/* Bypass Enable */
#define F_BYP                    (* (reg8 *) F__BYP)
/* Port wide control signals */                                                   
#define F_CTL                    (* (reg8 *) F__CTL)
/* Drive Modes */
#define F_DM0                    (* (reg8 *) F__DM0) 
#define F_DM1                    (* (reg8 *) F__DM1)
#define F_DM2                    (* (reg8 *) F__DM2) 
/* Input Buffer Disable Override */
#define F_INP_DIS                (* (reg8 *) F__INP_DIS)
/* LCD Common or Segment Drive */
#define F_LCD_COM_SEG            (* (reg8 *) F__LCD_COM_SEG)
/* Enable Segment LCD */
#define F_LCD_EN                 (* (reg8 *) F__LCD_EN)
/* Slew Rate Control */
#define F_SLW                    (* (reg8 *) F__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define F_PRTDSI__CAPS_SEL       (* (reg8 *) F__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define F_PRTDSI__DBL_SYNC_IN    (* (reg8 *) F__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define F_PRTDSI__OE_SEL0        (* (reg8 *) F__PRTDSI__OE_SEL0) 
#define F_PRTDSI__OE_SEL1        (* (reg8 *) F__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define F_PRTDSI__OUT_SEL0       (* (reg8 *) F__PRTDSI__OUT_SEL0) 
#define F_PRTDSI__OUT_SEL1       (* (reg8 *) F__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define F_PRTDSI__SYNC_OUT       (* (reg8 *) F__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(F__SIO_CFG)
    #define F_SIO_HYST_EN        (* (reg8 *) F__SIO_HYST_EN)
    #define F_SIO_REG_HIFREQ     (* (reg8 *) F__SIO_REG_HIFREQ)
    #define F_SIO_CFG            (* (reg8 *) F__SIO_CFG)
    #define F_SIO_DIFF           (* (reg8 *) F__SIO_DIFF)
#endif /* (F__SIO_CFG) */

/* Interrupt Registers */
#if defined(F__INTSTAT)
    #define F_INTSTAT            (* (reg8 *) F__INTSTAT)
    #define F_SNAP               (* (reg8 *) F__SNAP)
    
	#define F_0_INTTYPE_REG 		(* (reg8 *) F__0__INTTYPE)
#endif /* (F__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_F_H */


/* [] END OF FILE */

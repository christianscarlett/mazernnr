/*******************************************************************************
* File Name: v_sync.h  
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

#if !defined(CY_PINS_v_sync_H) /* Pins v_sync_H */
#define CY_PINS_v_sync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "v_sync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 v_sync__PORT == 15 && ((v_sync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    v_sync_Write(uint8 value);
void    v_sync_SetDriveMode(uint8 mode);
uint8   v_sync_ReadDataReg(void);
uint8   v_sync_Read(void);
void    v_sync_SetInterruptMode(uint16 position, uint16 mode);
uint8   v_sync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the v_sync_SetDriveMode() function.
     *  @{
     */
        #define v_sync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define v_sync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define v_sync_DM_RES_UP          PIN_DM_RES_UP
        #define v_sync_DM_RES_DWN         PIN_DM_RES_DWN
        #define v_sync_DM_OD_LO           PIN_DM_OD_LO
        #define v_sync_DM_OD_HI           PIN_DM_OD_HI
        #define v_sync_DM_STRONG          PIN_DM_STRONG
        #define v_sync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define v_sync_MASK               v_sync__MASK
#define v_sync_SHIFT              v_sync__SHIFT
#define v_sync_WIDTH              1u

/* Interrupt constants */
#if defined(v_sync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in v_sync_SetInterruptMode() function.
     *  @{
     */
        #define v_sync_INTR_NONE      (uint16)(0x0000u)
        #define v_sync_INTR_RISING    (uint16)(0x0001u)
        #define v_sync_INTR_FALLING   (uint16)(0x0002u)
        #define v_sync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define v_sync_INTR_MASK      (0x01u) 
#endif /* (v_sync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define v_sync_PS                     (* (reg8 *) v_sync__PS)
/* Data Register */
#define v_sync_DR                     (* (reg8 *) v_sync__DR)
/* Port Number */
#define v_sync_PRT_NUM                (* (reg8 *) v_sync__PRT) 
/* Connect to Analog Globals */                                                  
#define v_sync_AG                     (* (reg8 *) v_sync__AG)                       
/* Analog MUX bux enable */
#define v_sync_AMUX                   (* (reg8 *) v_sync__AMUX) 
/* Bidirectional Enable */                                                        
#define v_sync_BIE                    (* (reg8 *) v_sync__BIE)
/* Bit-mask for Aliased Register Access */
#define v_sync_BIT_MASK               (* (reg8 *) v_sync__BIT_MASK)
/* Bypass Enable */
#define v_sync_BYP                    (* (reg8 *) v_sync__BYP)
/* Port wide control signals */                                                   
#define v_sync_CTL                    (* (reg8 *) v_sync__CTL)
/* Drive Modes */
#define v_sync_DM0                    (* (reg8 *) v_sync__DM0) 
#define v_sync_DM1                    (* (reg8 *) v_sync__DM1)
#define v_sync_DM2                    (* (reg8 *) v_sync__DM2) 
/* Input Buffer Disable Override */
#define v_sync_INP_DIS                (* (reg8 *) v_sync__INP_DIS)
/* LCD Common or Segment Drive */
#define v_sync_LCD_COM_SEG            (* (reg8 *) v_sync__LCD_COM_SEG)
/* Enable Segment LCD */
#define v_sync_LCD_EN                 (* (reg8 *) v_sync__LCD_EN)
/* Slew Rate Control */
#define v_sync_SLW                    (* (reg8 *) v_sync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define v_sync_PRTDSI__CAPS_SEL       (* (reg8 *) v_sync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define v_sync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) v_sync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define v_sync_PRTDSI__OE_SEL0        (* (reg8 *) v_sync__PRTDSI__OE_SEL0) 
#define v_sync_PRTDSI__OE_SEL1        (* (reg8 *) v_sync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define v_sync_PRTDSI__OUT_SEL0       (* (reg8 *) v_sync__PRTDSI__OUT_SEL0) 
#define v_sync_PRTDSI__OUT_SEL1       (* (reg8 *) v_sync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define v_sync_PRTDSI__SYNC_OUT       (* (reg8 *) v_sync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(v_sync__SIO_CFG)
    #define v_sync_SIO_HYST_EN        (* (reg8 *) v_sync__SIO_HYST_EN)
    #define v_sync_SIO_REG_HIFREQ     (* (reg8 *) v_sync__SIO_REG_HIFREQ)
    #define v_sync_SIO_CFG            (* (reg8 *) v_sync__SIO_CFG)
    #define v_sync_SIO_DIFF           (* (reg8 *) v_sync__SIO_DIFF)
#endif /* (v_sync__SIO_CFG) */

/* Interrupt Registers */
#if defined(v_sync__INTSTAT)
    #define v_sync_INTSTAT            (* (reg8 *) v_sync__INTSTAT)
    #define v_sync_SNAP               (* (reg8 *) v_sync__SNAP)
    
	#define v_sync_0_INTTYPE_REG 		(* (reg8 *) v_sync__0__INTTYPE)
#endif /* (v_sync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_v_sync_H */


/* [] END OF FILE */

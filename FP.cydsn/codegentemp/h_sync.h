/*******************************************************************************
* File Name: h_sync.h  
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

#if !defined(CY_PINS_h_sync_H) /* Pins h_sync_H */
#define CY_PINS_h_sync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "h_sync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 h_sync__PORT == 15 && ((h_sync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    h_sync_Write(uint8 value);
void    h_sync_SetDriveMode(uint8 mode);
uint8   h_sync_ReadDataReg(void);
uint8   h_sync_Read(void);
void    h_sync_SetInterruptMode(uint16 position, uint16 mode);
uint8   h_sync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the h_sync_SetDriveMode() function.
     *  @{
     */
        #define h_sync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define h_sync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define h_sync_DM_RES_UP          PIN_DM_RES_UP
        #define h_sync_DM_RES_DWN         PIN_DM_RES_DWN
        #define h_sync_DM_OD_LO           PIN_DM_OD_LO
        #define h_sync_DM_OD_HI           PIN_DM_OD_HI
        #define h_sync_DM_STRONG          PIN_DM_STRONG
        #define h_sync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define h_sync_MASK               h_sync__MASK
#define h_sync_SHIFT              h_sync__SHIFT
#define h_sync_WIDTH              1u

/* Interrupt constants */
#if defined(h_sync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in h_sync_SetInterruptMode() function.
     *  @{
     */
        #define h_sync_INTR_NONE      (uint16)(0x0000u)
        #define h_sync_INTR_RISING    (uint16)(0x0001u)
        #define h_sync_INTR_FALLING   (uint16)(0x0002u)
        #define h_sync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define h_sync_INTR_MASK      (0x01u) 
#endif /* (h_sync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define h_sync_PS                     (* (reg8 *) h_sync__PS)
/* Data Register */
#define h_sync_DR                     (* (reg8 *) h_sync__DR)
/* Port Number */
#define h_sync_PRT_NUM                (* (reg8 *) h_sync__PRT) 
/* Connect to Analog Globals */                                                  
#define h_sync_AG                     (* (reg8 *) h_sync__AG)                       
/* Analog MUX bux enable */
#define h_sync_AMUX                   (* (reg8 *) h_sync__AMUX) 
/* Bidirectional Enable */                                                        
#define h_sync_BIE                    (* (reg8 *) h_sync__BIE)
/* Bit-mask for Aliased Register Access */
#define h_sync_BIT_MASK               (* (reg8 *) h_sync__BIT_MASK)
/* Bypass Enable */
#define h_sync_BYP                    (* (reg8 *) h_sync__BYP)
/* Port wide control signals */                                                   
#define h_sync_CTL                    (* (reg8 *) h_sync__CTL)
/* Drive Modes */
#define h_sync_DM0                    (* (reg8 *) h_sync__DM0) 
#define h_sync_DM1                    (* (reg8 *) h_sync__DM1)
#define h_sync_DM2                    (* (reg8 *) h_sync__DM2) 
/* Input Buffer Disable Override */
#define h_sync_INP_DIS                (* (reg8 *) h_sync__INP_DIS)
/* LCD Common or Segment Drive */
#define h_sync_LCD_COM_SEG            (* (reg8 *) h_sync__LCD_COM_SEG)
/* Enable Segment LCD */
#define h_sync_LCD_EN                 (* (reg8 *) h_sync__LCD_EN)
/* Slew Rate Control */
#define h_sync_SLW                    (* (reg8 *) h_sync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define h_sync_PRTDSI__CAPS_SEL       (* (reg8 *) h_sync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define h_sync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) h_sync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define h_sync_PRTDSI__OE_SEL0        (* (reg8 *) h_sync__PRTDSI__OE_SEL0) 
#define h_sync_PRTDSI__OE_SEL1        (* (reg8 *) h_sync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define h_sync_PRTDSI__OUT_SEL0       (* (reg8 *) h_sync__PRTDSI__OUT_SEL0) 
#define h_sync_PRTDSI__OUT_SEL1       (* (reg8 *) h_sync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define h_sync_PRTDSI__SYNC_OUT       (* (reg8 *) h_sync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(h_sync__SIO_CFG)
    #define h_sync_SIO_HYST_EN        (* (reg8 *) h_sync__SIO_HYST_EN)
    #define h_sync_SIO_REG_HIFREQ     (* (reg8 *) h_sync__SIO_REG_HIFREQ)
    #define h_sync_SIO_CFG            (* (reg8 *) h_sync__SIO_CFG)
    #define h_sync_SIO_DIFF           (* (reg8 *) h_sync__SIO_DIFF)
#endif /* (h_sync__SIO_CFG) */

/* Interrupt Registers */
#if defined(h_sync__INTSTAT)
    #define h_sync_INTSTAT            (* (reg8 *) h_sync__INTSTAT)
    #define h_sync_SNAP               (* (reg8 *) h_sync__SNAP)
    
	#define h_sync_0_INTTYPE_REG 		(* (reg8 *) h_sync__0__INTTYPE)
#endif /* (h_sync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_h_sync_H */


/* [] END OF FILE */

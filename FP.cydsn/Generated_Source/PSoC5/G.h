/*******************************************************************************
* File Name: G.h  
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

#if !defined(CY_PINS_G_H) /* Pins G_H */
#define CY_PINS_G_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "G_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 G__PORT == 15 && ((G__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    G_Write(uint8 value);
void    G_SetDriveMode(uint8 mode);
uint8   G_ReadDataReg(void);
uint8   G_Read(void);
void    G_SetInterruptMode(uint16 position, uint16 mode);
uint8   G_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the G_SetDriveMode() function.
     *  @{
     */
        #define G_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define G_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define G_DM_RES_UP          PIN_DM_RES_UP
        #define G_DM_RES_DWN         PIN_DM_RES_DWN
        #define G_DM_OD_LO           PIN_DM_OD_LO
        #define G_DM_OD_HI           PIN_DM_OD_HI
        #define G_DM_STRONG          PIN_DM_STRONG
        #define G_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define G_MASK               G__MASK
#define G_SHIFT              G__SHIFT
#define G_WIDTH              1u

/* Interrupt constants */
#if defined(G__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in G_SetInterruptMode() function.
     *  @{
     */
        #define G_INTR_NONE      (uint16)(0x0000u)
        #define G_INTR_RISING    (uint16)(0x0001u)
        #define G_INTR_FALLING   (uint16)(0x0002u)
        #define G_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define G_INTR_MASK      (0x01u) 
#endif /* (G__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define G_PS                     (* (reg8 *) G__PS)
/* Data Register */
#define G_DR                     (* (reg8 *) G__DR)
/* Port Number */
#define G_PRT_NUM                (* (reg8 *) G__PRT) 
/* Connect to Analog Globals */                                                  
#define G_AG                     (* (reg8 *) G__AG)                       
/* Analog MUX bux enable */
#define G_AMUX                   (* (reg8 *) G__AMUX) 
/* Bidirectional Enable */                                                        
#define G_BIE                    (* (reg8 *) G__BIE)
/* Bit-mask for Aliased Register Access */
#define G_BIT_MASK               (* (reg8 *) G__BIT_MASK)
/* Bypass Enable */
#define G_BYP                    (* (reg8 *) G__BYP)
/* Port wide control signals */                                                   
#define G_CTL                    (* (reg8 *) G__CTL)
/* Drive Modes */
#define G_DM0                    (* (reg8 *) G__DM0) 
#define G_DM1                    (* (reg8 *) G__DM1)
#define G_DM2                    (* (reg8 *) G__DM2) 
/* Input Buffer Disable Override */
#define G_INP_DIS                (* (reg8 *) G__INP_DIS)
/* LCD Common or Segment Drive */
#define G_LCD_COM_SEG            (* (reg8 *) G__LCD_COM_SEG)
/* Enable Segment LCD */
#define G_LCD_EN                 (* (reg8 *) G__LCD_EN)
/* Slew Rate Control */
#define G_SLW                    (* (reg8 *) G__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define G_PRTDSI__CAPS_SEL       (* (reg8 *) G__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define G_PRTDSI__DBL_SYNC_IN    (* (reg8 *) G__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define G_PRTDSI__OE_SEL0        (* (reg8 *) G__PRTDSI__OE_SEL0) 
#define G_PRTDSI__OE_SEL1        (* (reg8 *) G__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define G_PRTDSI__OUT_SEL0       (* (reg8 *) G__PRTDSI__OUT_SEL0) 
#define G_PRTDSI__OUT_SEL1       (* (reg8 *) G__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define G_PRTDSI__SYNC_OUT       (* (reg8 *) G__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(G__SIO_CFG)
    #define G_SIO_HYST_EN        (* (reg8 *) G__SIO_HYST_EN)
    #define G_SIO_REG_HIFREQ     (* (reg8 *) G__SIO_REG_HIFREQ)
    #define G_SIO_CFG            (* (reg8 *) G__SIO_CFG)
    #define G_SIO_DIFF           (* (reg8 *) G__SIO_DIFF)
#endif /* (G__SIO_CFG) */

/* Interrupt Registers */
#if defined(G__INTSTAT)
    #define G_INTSTAT            (* (reg8 *) G__INTSTAT)
    #define G_SNAP               (* (reg8 *) G__SNAP)
    
	#define G_0_INTTYPE_REG 		(* (reg8 *) G__0__INTTYPE)
#endif /* (G__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_G_H */


/* [] END OF FILE */

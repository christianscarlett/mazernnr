/*******************************************************************************
* File Name: Color.h  
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

#if !defined(CY_PINS_Color_H) /* Pins Color_H */
#define CY_PINS_Color_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Color_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Color__PORT == 15 && ((Color__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Color_Write(uint8 value);
void    Color_SetDriveMode(uint8 mode);
uint8   Color_ReadDataReg(void);
uint8   Color_Read(void);
void    Color_SetInterruptMode(uint16 position, uint16 mode);
uint8   Color_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Color_SetDriveMode() function.
     *  @{
     */
        #define Color_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Color_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Color_DM_RES_UP          PIN_DM_RES_UP
        #define Color_DM_RES_DWN         PIN_DM_RES_DWN
        #define Color_DM_OD_LO           PIN_DM_OD_LO
        #define Color_DM_OD_HI           PIN_DM_OD_HI
        #define Color_DM_STRONG          PIN_DM_STRONG
        #define Color_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Color_MASK               Color__MASK
#define Color_SHIFT              Color__SHIFT
#define Color_WIDTH              1u

/* Interrupt constants */
#if defined(Color__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Color_SetInterruptMode() function.
     *  @{
     */
        #define Color_INTR_NONE      (uint16)(0x0000u)
        #define Color_INTR_RISING    (uint16)(0x0001u)
        #define Color_INTR_FALLING   (uint16)(0x0002u)
        #define Color_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Color_INTR_MASK      (0x01u) 
#endif /* (Color__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Color_PS                     (* (reg8 *) Color__PS)
/* Data Register */
#define Color_DR                     (* (reg8 *) Color__DR)
/* Port Number */
#define Color_PRT_NUM                (* (reg8 *) Color__PRT) 
/* Connect to Analog Globals */                                                  
#define Color_AG                     (* (reg8 *) Color__AG)                       
/* Analog MUX bux enable */
#define Color_AMUX                   (* (reg8 *) Color__AMUX) 
/* Bidirectional Enable */                                                        
#define Color_BIE                    (* (reg8 *) Color__BIE)
/* Bit-mask for Aliased Register Access */
#define Color_BIT_MASK               (* (reg8 *) Color__BIT_MASK)
/* Bypass Enable */
#define Color_BYP                    (* (reg8 *) Color__BYP)
/* Port wide control signals */                                                   
#define Color_CTL                    (* (reg8 *) Color__CTL)
/* Drive Modes */
#define Color_DM0                    (* (reg8 *) Color__DM0) 
#define Color_DM1                    (* (reg8 *) Color__DM1)
#define Color_DM2                    (* (reg8 *) Color__DM2) 
/* Input Buffer Disable Override */
#define Color_INP_DIS                (* (reg8 *) Color__INP_DIS)
/* LCD Common or Segment Drive */
#define Color_LCD_COM_SEG            (* (reg8 *) Color__LCD_COM_SEG)
/* Enable Segment LCD */
#define Color_LCD_EN                 (* (reg8 *) Color__LCD_EN)
/* Slew Rate Control */
#define Color_SLW                    (* (reg8 *) Color__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Color_PRTDSI__CAPS_SEL       (* (reg8 *) Color__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Color_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Color__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Color_PRTDSI__OE_SEL0        (* (reg8 *) Color__PRTDSI__OE_SEL0) 
#define Color_PRTDSI__OE_SEL1        (* (reg8 *) Color__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Color_PRTDSI__OUT_SEL0       (* (reg8 *) Color__PRTDSI__OUT_SEL0) 
#define Color_PRTDSI__OUT_SEL1       (* (reg8 *) Color__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Color_PRTDSI__SYNC_OUT       (* (reg8 *) Color__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Color__SIO_CFG)
    #define Color_SIO_HYST_EN        (* (reg8 *) Color__SIO_HYST_EN)
    #define Color_SIO_REG_HIFREQ     (* (reg8 *) Color__SIO_REG_HIFREQ)
    #define Color_SIO_CFG            (* (reg8 *) Color__SIO_CFG)
    #define Color_SIO_DIFF           (* (reg8 *) Color__SIO_DIFF)
#endif /* (Color__SIO_CFG) */

/* Interrupt Registers */
#if defined(Color__INTSTAT)
    #define Color_INTSTAT            (* (reg8 *) Color__INTSTAT)
    #define Color_SNAP               (* (reg8 *) Color__SNAP)
    
	#define Color_0_INTTYPE_REG 		(* (reg8 *) Color__0__INTTYPE)
#endif /* (Color__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Color_H */


/* [] END OF FILE */

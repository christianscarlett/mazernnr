/*******************************************************************************
* File Name: GameTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "GameTimer.h"

static GameTimer_backupStruct GameTimer_backup;


/*******************************************************************************
* Function Name: GameTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  GameTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void GameTimer_SaveConfig(void) 
{
    #if (!GameTimer_UsingFixedFunction)
        GameTimer_backup.TimerUdb = GameTimer_ReadCounter();
        GameTimer_backup.InterruptMaskValue = GameTimer_STATUS_MASK;
        #if (GameTimer_UsingHWCaptureCounter)
            GameTimer_backup.TimerCaptureCounter = GameTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!GameTimer_UDB_CONTROL_REG_REMOVED)
            GameTimer_backup.TimerControlRegister = GameTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: GameTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  GameTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void GameTimer_RestoreConfig(void) 
{   
    #if (!GameTimer_UsingFixedFunction)

        GameTimer_WriteCounter(GameTimer_backup.TimerUdb);
        GameTimer_STATUS_MASK =GameTimer_backup.InterruptMaskValue;
        #if (GameTimer_UsingHWCaptureCounter)
            GameTimer_SetCaptureCount(GameTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!GameTimer_UDB_CONTROL_REG_REMOVED)
            GameTimer_WriteControlRegister(GameTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: GameTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  GameTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void GameTimer_Sleep(void) 
{
    #if(!GameTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(GameTimer_CTRL_ENABLE == (GameTimer_CONTROL & GameTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            GameTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            GameTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    GameTimer_Stop();
    GameTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: GameTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  GameTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void GameTimer_Wakeup(void) 
{
    GameTimer_RestoreConfig();
    #if(!GameTimer_UDB_CONTROL_REG_REMOVED)
        if(GameTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                GameTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

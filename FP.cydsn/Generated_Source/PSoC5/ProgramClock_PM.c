/*******************************************************************************
* File Name: ProgramClock_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ProgramClock.h"

static ProgramClock_backupStruct ProgramClock_backup;


/*******************************************************************************
* Function Name: ProgramClock_SaveConfig
********************************************************************************
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
*  ProgramClock_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ProgramClock_SaveConfig(void) 
{
    #if (!ProgramClock_UsingFixedFunction)

        ProgramClock_backup.CounterUdb = ProgramClock_ReadCounter();

        #if(!ProgramClock_ControlRegRemoved)
            ProgramClock_backup.CounterControlRegister = ProgramClock_ReadControlRegister();
        #endif /* (!ProgramClock_ControlRegRemoved) */

    #endif /* (!ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_RestoreConfig
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
*  ProgramClock_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ProgramClock_RestoreConfig(void) 
{      
    #if (!ProgramClock_UsingFixedFunction)

       ProgramClock_WriteCounter(ProgramClock_backup.CounterUdb);

        #if(!ProgramClock_ControlRegRemoved)
            ProgramClock_WriteControlRegister(ProgramClock_backup.CounterControlRegister);
        #endif /* (!ProgramClock_ControlRegRemoved) */

    #endif /* (!ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_Sleep
********************************************************************************
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
*  ProgramClock_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ProgramClock_Sleep(void) 
{
    #if(!ProgramClock_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ProgramClock_CTRL_ENABLE == (ProgramClock_CONTROL & ProgramClock_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ProgramClock_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ProgramClock_backup.CounterEnableState = 0u;
        }
    #else
        ProgramClock_backup.CounterEnableState = 1u;
        if(ProgramClock_backup.CounterEnableState != 0u)
        {
            ProgramClock_backup.CounterEnableState = 0u;
        }
    #endif /* (!ProgramClock_ControlRegRemoved) */
    
    ProgramClock_Stop();
    ProgramClock_SaveConfig();
}


/*******************************************************************************
* Function Name: ProgramClock_Wakeup
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
*  ProgramClock_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ProgramClock_Wakeup(void) 
{
    ProgramClock_RestoreConfig();
    #if(!ProgramClock_ControlRegRemoved)
        if(ProgramClock_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ProgramClock_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ProgramClock_ControlRegRemoved) */
    
}


/* [] END OF FILE */

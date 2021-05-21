/*******************************************************************************
* File Name: ProgramClock.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 ProgramClock_initVar = 0u;


/*******************************************************************************
* Function Name: ProgramClock_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ProgramClock_Init(void) 
{
        #if (!ProgramClock_UsingFixedFunction && !ProgramClock_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ProgramClock_UsingFixedFunction && !ProgramClock_ControlRegRemoved) */
        
        #if(!ProgramClock_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ProgramClock_interruptState;
        #endif /* (!ProgramClock_UsingFixedFunction) */
        
        #if (ProgramClock_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ProgramClock_CONTROL &= ProgramClock_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ProgramClock_CONTROL2 &= ((uint8)(~ProgramClock_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ProgramClock_CONTROL3 &= ((uint8)(~ProgramClock_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ProgramClock_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ProgramClock_CONTROL |= ProgramClock_ONESHOT;
            #endif /* (ProgramClock_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ProgramClock_CONTROL2 |= ProgramClock_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ProgramClock_RT1 &= ((uint8)(~ProgramClock_RT1_MASK));
            ProgramClock_RT1 |= ProgramClock_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ProgramClock_RT1 &= ((uint8)(~ProgramClock_SYNCDSI_MASK));
            ProgramClock_RT1 |= ProgramClock_SYNCDSI_EN;

        #else
            #if(!ProgramClock_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ProgramClock_CONTROL & ((uint8)(~ProgramClock_CTRL_CMPMODE_MASK));
            ProgramClock_CONTROL = ctrl | ProgramClock_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ProgramClock_CONTROL & ((uint8)(~ProgramClock_CTRL_CAPMODE_MASK));
            
            #if( 0 != ProgramClock_CAPTURE_MODE_CONF)
                ProgramClock_CONTROL = ctrl | ProgramClock_DEFAULT_CAPTURE_MODE;
            #else
                ProgramClock_CONTROL = ctrl;
            #endif /* 0 != ProgramClock_CAPTURE_MODE */ 
            
            #endif /* (!ProgramClock_ControlRegRemoved) */
        #endif /* (ProgramClock_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ProgramClock_UsingFixedFunction)
            ProgramClock_ClearFIFO();
        #endif /* (!ProgramClock_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ProgramClock_WritePeriod(ProgramClock_INIT_PERIOD_VALUE);
        #if (!(ProgramClock_UsingFixedFunction && (CY_PSOC5A)))
            ProgramClock_WriteCounter(ProgramClock_INIT_COUNTER_VALUE);
        #endif /* (!(ProgramClock_UsingFixedFunction && (CY_PSOC5A))) */
        ProgramClock_SetInterruptMode(ProgramClock_INIT_INTERRUPTS_MASK);
        
        #if (!ProgramClock_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ProgramClock_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ProgramClock_WriteCompare(ProgramClock_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ProgramClock_interruptState = CyEnterCriticalSection();
            
            ProgramClock_STATUS_AUX_CTRL |= ProgramClock_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ProgramClock_interruptState);
            
        #endif /* (!ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void ProgramClock_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ProgramClock_UsingFixedFunction)
        ProgramClock_GLOBAL_ENABLE |= ProgramClock_BLOCK_EN_MASK;
        ProgramClock_GLOBAL_STBY_ENABLE |= ProgramClock_BLOCK_STBY_EN_MASK;
    #endif /* (ProgramClock_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ProgramClock_ControlRegRemoved || ProgramClock_UsingFixedFunction)
        ProgramClock_CONTROL |= ProgramClock_CTRL_ENABLE;                
    #endif /* (!ProgramClock_ControlRegRemoved || ProgramClock_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ProgramClock_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  ProgramClock_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ProgramClock_Start(void) 
{
    if(ProgramClock_initVar == 0u)
    {
        ProgramClock_Init();
        
        ProgramClock_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ProgramClock_Enable();        
}


/*******************************************************************************
* Function Name: ProgramClock_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void ProgramClock_Stop(void) 
{
    /* Disable Counter */
    #if(!ProgramClock_ControlRegRemoved || ProgramClock_UsingFixedFunction)
        ProgramClock_CONTROL &= ((uint8)(~ProgramClock_CTRL_ENABLE));        
    #endif /* (!ProgramClock_ControlRegRemoved || ProgramClock_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ProgramClock_UsingFixedFunction)
        ProgramClock_GLOBAL_ENABLE &= ((uint8)(~ProgramClock_BLOCK_EN_MASK));
        ProgramClock_GLOBAL_STBY_ENABLE &= ((uint8)(~ProgramClock_BLOCK_STBY_EN_MASK));
    #endif /* (ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void ProgramClock_SetInterruptMode(uint8 interruptsMask) 
{
    ProgramClock_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ProgramClock_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   ProgramClock_ReadStatusRegister(void) 
{
    return ProgramClock_STATUS;
}


#if(!ProgramClock_ControlRegRemoved)
/*******************************************************************************
* Function Name: ProgramClock_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   ProgramClock_ReadControlRegister(void) 
{
    return ProgramClock_CONTROL;
}


/*******************************************************************************
* Function Name: ProgramClock_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    ProgramClock_WriteControlRegister(uint8 control) 
{
    ProgramClock_CONTROL = control;
}

#endif  /* (!ProgramClock_ControlRegRemoved) */


#if (!(ProgramClock_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ProgramClock_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void ProgramClock_WriteCounter(uint32 counter) \
                                   
{
    #if(ProgramClock_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ProgramClock_GLOBAL_ENABLE & ProgramClock_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ProgramClock_GLOBAL_ENABLE |= ProgramClock_BLOCK_EN_MASK;
        CY_SET_REG16(ProgramClock_COUNTER_LSB_PTR, (uint16)counter);
        ProgramClock_GLOBAL_ENABLE &= ((uint8)(~ProgramClock_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(ProgramClock_COUNTER_LSB_PTR, counter);
    #endif /* (ProgramClock_UsingFixedFunction) */
}
#endif /* (!(ProgramClock_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ProgramClock_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 ProgramClock_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ProgramClock_UsingFixedFunction)
		(void)CY_GET_REG16(ProgramClock_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ProgramClock_COUNTER_LSB_PTR_8BIT);
	#endif/* (ProgramClock_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ProgramClock_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(ProgramClock_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(ProgramClock_STATICCOUNT_LSB_PTR));
    #endif /* (ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 ProgramClock_ReadCapture(void) 
{
    #if(ProgramClock_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(ProgramClock_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(ProgramClock_STATICCOUNT_LSB_PTR));
    #endif /* (ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void ProgramClock_WritePeriod(uint32 period) 
{
    #if(ProgramClock_UsingFixedFunction)
        CY_SET_REG16(ProgramClock_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(ProgramClock_PERIOD_LSB_PTR, period);
    #endif /* (ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 ProgramClock_ReadPeriod(void) 
{
    #if(ProgramClock_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(ProgramClock_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(ProgramClock_PERIOD_LSB_PTR));
    #endif /* (ProgramClock_UsingFixedFunction) */
}


#if (!ProgramClock_UsingFixedFunction)
/*******************************************************************************
* Function Name: ProgramClock_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void ProgramClock_WriteCompare(uint32 compare) \
                                   
{
    #if(ProgramClock_UsingFixedFunction)
        CY_SET_REG16(ProgramClock_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(ProgramClock_COMPARE_LSB_PTR, compare);
    #endif /* (ProgramClock_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ProgramClock_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 ProgramClock_ReadCompare(void) 
{
    return (CY_GET_REG32(ProgramClock_COMPARE_LSB_PTR));
}


#if (ProgramClock_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ProgramClock_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ProgramClock_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ProgramClock_CONTROL &= ((uint8)(~ProgramClock_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ProgramClock_CONTROL |= compareMode;
}
#endif  /* (ProgramClock_COMPARE_MODE_SOFTWARE) */


#if (ProgramClock_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ProgramClock_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ProgramClock_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ProgramClock_CONTROL &= ((uint8)(~ProgramClock_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ProgramClock_CONTROL |= ((uint8)((uint8)captureMode << ProgramClock_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ProgramClock_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ProgramClock_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void ProgramClock_ClearFIFO(void) 
{

    while(0u != (ProgramClock_ReadStatusRegister() & ProgramClock_STATUS_FIFONEMP))
    {
        (void)ProgramClock_ReadCapture();
    }

}
#endif  /* (!ProgramClock_UsingFixedFunction) */


/* [] END OF FILE */


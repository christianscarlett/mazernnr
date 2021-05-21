/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <math.h>

// Color RGB definitions
#define BLACK 0u
#define RED 1u
#define GREEN 2u
#define G 2u
#define YELLOW 3u
#define BLUE 4u
#define PURPLE 5u
#define P 5u
#define CYAN 6u
#define WHITE 7u
#define W 7u
// location for data of a single display row
uint8 line_buffer[50];
// buffer for data of whole display
uint8 display[20][25] = {
    { 0, RED, BLACK, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, GREEN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, YELLOW, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, BLUE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, PURPLE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, CYAN, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 255, WHITE},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, WHITE},
};

// This interrupt is called every time the VGA signal ends the data transmission portion
int display_row = 0;
void Line_Int_Handler(void) {
    if ( Control_Reg_2_Read() == 0 ) {
        // Do nothing if DMA not enabled (for alignment)
        return;
    }
    // Copy next line of display into DMA buffer
    int display_col;
    for (display_col=0; display_col<25; display_col++) {
        line_buffer[display_col] = display[display_row][display_col];
    }
    display_row = (display_row + 1) % 20;
    Line_Int_ClearPending();
}

void enable_dma(void) {
    /* Variable declarations for DMA_1 */
    /* Move these variable declarations to the top of the function */
    uint8 DMA_1_Chan;
    uint8 DMA_1_TD[1];
    /* DMA Configuration for DMA_1 */
    #define DMA_1_BYTES_PER_BURST 1
    #define DMA_1_REQUEST_PER_BURST 1
    #define DMA_1_SRC_BASE (CYDEV_SRAM_BASE)
    #define DMA_1_DST_BASE (CYDEV_PERIPH_BASE)
    DMA_1_Chan = DMA_1_DmaInitialize(DMA_1_BYTES_PER_BURST, DMA_1_REQUEST_PER_BURST, 
        HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
    DMA_1_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_1_TD[0], 25, DMA_1_TD[0], TD_TERMIN_EN | DMA_1__TD_TERMOUT_EN | TD_INC_SRC_ADR);
    CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)line_buffer), LO16((uint32)Control_Reg_1_Control_PTR));
    CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
    CyDmaChEnable(DMA_1_Chan, 1);
    // Enable hardware DMA trigger
    Control_Reg_2_Write(255);
}

/* JOYSTICK METHODS */
// State variables
#define LEFT 1
#define SLIGHT_LEFT 6
#define RIGHT 2
#define SLIGHT_RIGHT 7
#define UP 3
#define DOWN 4
#define CENTER 5

uint8 joystick_y_state = CENTER;
uint8 joystick_x_state = CENTER;

void update_joystick_x(void) {
    // Reading is between 0 and 255, 0 being leftmost and 255 being rightmost
    uint8 reading = ADC_SAR_1_GetResult8();
    if (reading > 207) {
        joystick_x_state = LEFT;
    } else if (reading > 147) {
        joystick_x_state = SLIGHT_LEFT;
    } else if (reading < 47) {
        joystick_x_state = RIGHT;
    } else if (reading < 107) {
        joystick_x_state = SLIGHT_RIGHT;
    } else {
        joystick_x_state = CENTER;
    }
}

void update_joystick_y(void) {
    // Reading is between 0 and 255, 0 being up and 255 being down
    uint8 reading = ADC_SAR_Seq_1_GetAdcResult();
    if (reading > 147) {
        joystick_y_state = DOWN;
    } else if (reading < 107) {
        joystick_y_state = UP;
    } else {
        joystick_y_state = CENTER;
    }
    
}

/* END JOYSTICK METHODS */


/* BUTTON METHODS */
// State variables
#define PUSHED 1 // Button just pushed down
#define PRESSED 2 // Button held down
#define RELEASED 3 // Button just released
#define UNPRESSED 4 // Button not held down

uint8 green_button_state = UNPRESSED;
uint8 red_button_state = UNPRESSED;

uint8 update_button_state(uint8 button_state, uint8 reading) {
    if (button_state == UNPRESSED) {
        if (reading == 0) return PUSHED;
        else return UNPRESSED;
    }
    else if (button_state == PUSHED) {
        if (reading == 0) return PRESSED;
        else return RELEASED;
    }
    else if (button_state == PRESSED) {
        if (reading == 0) return PRESSED;
        else return RELEASED;
    }
    else { // RELEASED
        if (reading == 0) return PUSHED;
        else return UNPRESSED;
    }
}

void update_green_button_state(void) {
    green_button_state = update_button_state(green_button_state, A_Read());
}

void update_red_button_state(void) {
    red_button_state = update_button_state(red_button_state, B_Read());
}
/* END BUTTON METHODS */


/* AUDIO METHODS */
// State variables
#define PLAYING 1
#define NOT_PLAYING 2
uint8 audio_state = NOT_PLAYING;
// High time and low time for PWM square wave
uint8 audio_high_time = 0;
uint8 audio_low_time = 0;

void audio_set_period(uint8 high_ms, uint8 low_ms) {
    audio_high_time = high_ms;
    audio_low_time = low_ms;
    audio_state = PLAYING;
}

void audio_stop(void) {
    audio_state = NOT_PLAYING;
}

/* END AUDIO METHODS */



/* GAME */

// Displays
// Each level matrix defines boundaries (walls, floor) with WHITE (W) pixels and the end goal with GREEN (G)
uint8 level_1[20][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, G, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, W, W, W, W, W, W, W, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, W, W, 0, 0, 0, 0, 0, 0, 0, W, W, 0, 0, W, W, W, 0, 0, 0, W, W, W, W, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, W, W, W, W, W, W, W, W, 0, W, 0, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, W, W, W, W, W, W, W, W, W, W, W, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W},
    { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
};

uint8 level_2[20][25] = {
    { 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, W, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, W, W, W, W, W, W, W, W, 0, W, 0, 0, 0, 0, W, W, W, 0, 0, 0, W},
    { 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, W, W},
    { 0, 0, 0, 0, W, 0, P, 0, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, W, 0, W, W, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, W, 0, 0, 0, W},
    { 0, 0, 0, 0, W, 0, W, W, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, W, W, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, W, W},
    { 0, 0, 0, W, W, 0, 0, 0, W, W, 0, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0, W, W, 0, 0, 0, W},
    { 0, 0, 0, 0, W, W, 0, 0, 0, 0, W, W, 0, W, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, W, W, W, 0, 0, 0, W, W, 0, 0, 0, 0, 0, 0, G, W, 0, 0, 0, W, W},
    { 0, 0, 0, 0, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W},
    { W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W},
};

uint8 level_3[20][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, G, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, W, W, 0, 0, 0, W, W, 0, 0, 0, W, W, 0, 0, 0, 0, W, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W, 0, 0, 0, W, W, 0, 0, 0, 0, W, W, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, W, W, 0, 0, 0, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, W, W, 0, 0, 0, W},
    { 0, 0, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
};

uint8 win_screen[20][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, W, 0, W, 0, W, W, W, 0, W, 0, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, W, W, W, 0, W, 0, W, 0, W, 0, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W, 0, W, 0, W, 0, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W, W, W, 0, W, W, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, 0, 0, W, 0, W, W, W, 0, W, 0, 0, W, 0, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, 0, 0, W, 0, W, 0, W, 0, W, W, 0, W, 0, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, 0, W, W, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, W, 0, W, 0, 0, W, W, W, 0, W, 0, 0, W, 0, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
};

uint8 loss_screen[20][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, W, 0, W, 0, W, W, W, 0, W, 0, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, W, W, W, 0, W, 0, W, 0, W, 0, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W, 0, W, 0, W, 0, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, W, W, W, 0, W, W, W, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, 0, 0, W, W, W, 0, 0, W, W, 0, W, W, W, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, 0, 0, W, 0, W, 0, W, 0, 0, 0, 0, W, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, 0, 0, 0, W, 0, W, 0, 0, W, W, 0, 0, W, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, W, W, W, 0, W, W, W, 0, W, W, 0, 0, 0, W, 0, W, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W},
};

uint8 menu[20][25] = {
    { 0, 0, 0, 0, W, 0, W, 0, 0, 0, W, W, 0, 0, W, W, W, W, 0, W, W, W, 0, 0, 0},
    { 0, 0, 0, W, 0, W, 0, W, 0, W, 0, 0, W, 0, 0, 0, 0, W, 0, W, 0, 0, 0, 0, 0},
    { 0, 0, 0, W, 0, 0, 0, W, 0, W, W, W, W, 0, 0, 0, W, 0, 0, W, W, W, 0, 0, 0},
    { 0, 0, 0, W, 0, 0, 0, W, 0, W, 0, 0, W, 0, 0, W, 0, 0, 0, W, 0, 0, 0, 0, 0},
    { 0, 0, 0, W, 0, 0, 0, W, 0, W, 0, 0, W, 0, W, W, W, W, 0, W, W, W, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, W, W, W, 0, W, 0, 0, W, 0, W, 0, 0, W, 0, W, W, W, 0, 0, 0, 0},
    { 0, 0, 0, 0, W, 0, W, 0, W, W, 0, W, 0, W, W, 0, W, 0, W, 0, W, 0, 0, 0, 0},
    { 0, 0, 0, 0, W, W, 0, 0, W, 0, W, W, 0, W, 0, W, W, 0, W, W, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, W, 0, W, 0, W, 0, 0, W, 0, W, 0, 0, W, 0, W, 0, W, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, W, W, W, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// Globals
// game tick at a given time
uint32 game_tick = 0;
// framework defining boundaries/platforms of level
uint8 framework[20][25];
// position of character start
uint8 start_x;
uint8 start_y;
// game state
#define WON 1
#define LOST 2
#define INGAME 3
#define MENU 4
uint8 game_state;

// Helpful methods
uint8 detect_collide(uint8 x, uint8 y) {
    /* Return 1 if there is an obstacle at position (x,y) or (x,y) is out of bounds, 0 otherwise */
    if (x < 0 || 24 < x || y < 0 || 19 < y || framework[y][x] == WHITE)
        return 1;
    return 0;
}


// Audio logic
uint32 game_audio_stop_tick = 0;
uint32 win_song_start_tick = 0;

void play_jump_sound(uint32 length) {
    // Notify game audio updater when to stop audio by setting this var
    game_audio_stop_tick = game_tick + length;
    // Call upon system audio to play square wave
    audio_set_period(1,1);
}

void play_adv_death_sound(uint32 length) {
    game_audio_stop_tick = game_tick + length;
    audio_set_period(2,1);
}

void play_character_death_sound(uint32 length) {
    game_audio_stop_tick = game_tick + length;
    audio_set_period(2,2);
}

void start_win_song(void) {
    // Schedule win song to start playing
    win_song_start_tick = game_tick;
    // Dont stop playing until song finished
    game_audio_stop_tick = game_tick + 108;
}

void update_win_sound(void) {
    if (game_tick - win_song_start_tick >= 108) // Dont play if song finished
        return;
    else if (game_tick - win_song_start_tick == 0) // Play note
        audio_set_period(2,2);
    else if (game_tick - win_song_start_tick == 12) // Stop note
        audio_stop();
    else if (game_tick - win_song_start_tick == 24)
        audio_set_period(2,2);
    else if (game_tick - win_song_start_tick == 36)
        audio_stop();
    else if (game_tick - win_song_start_tick == 48)
        audio_set_period(2,2);
    else if (game_tick - win_song_start_tick == 60)
        audio_stop();
    else if (game_tick - win_song_start_tick == 72)
        audio_set_period(2,1);
}

void update_game_audio(void) {
    update_win_sound();
    if (game_tick >= game_audio_stop_tick && audio_state == PLAYING) {
        audio_stop();
    }
}


// Character methods
#define ALIVE 1
#define DEAD 2
#define IMMUNE 3

// number of ticks between updates
#define CHARACTER_X_UPDATE_SPEED 16
#define CHARACTER_X_UPDATE_SPEED_SLOW 48
#define CHARACTER_Y_UPDATE_SPEED 16
#define IMMUNITY_TIME 300
#define IMMUNITY_TEXTURE_TIME 10

uint8 prev_character_x = 0;
uint8 prev_character_y = 0;
uint8 character_x = 0;
uint8 character_y = 19;

uint8 character_state = ALIVE;

uint32 last_jump_tick = 0;
uint32 last_damage_tick = 0;

uint8 character_texture = CYAN;

void update_character_pos(void) {
    if (character_state == DEAD)
        return;
    
    // Update character x
    if (game_tick % CHARACTER_X_UPDATE_SPEED == 0) {
        if (joystick_x_state == LEFT && detect_collide(character_x-1, character_y) == 0)
            character_x -= 1;
        else if (joystick_x_state == RIGHT && detect_collide(character_x+1, character_y) == 0)
            character_x += 1;
    }
    if (game_tick % CHARACTER_X_UPDATE_SPEED_SLOW == 0) {
        if (joystick_x_state == SLIGHT_LEFT && detect_collide(character_x-1, character_y) == 0)
            character_x -= 1;
        else if (joystick_x_state == SLIGHT_RIGHT && detect_collide(character_x+1, character_y) == 0)
            character_x += 1;
    }
    
    // Detect jump if jump button pressed and something to jump off of 
    if (green_button_state == PUSHED && detect_collide(character_x, character_y+1) == 1) {
        last_jump_tick = game_tick;
        play_jump_sound(12);
    }
    
    // Update character y
    if (last_jump_tick != 0) {
        uint32 jump_length = game_tick - last_jump_tick;
        if (jump_length % CHARACTER_Y_UPDATE_SPEED == 0) {
            // Go up for 2 periods, hang there for the 3rd period, otherwise apply gravity
            if (jump_length < 2*CHARACTER_Y_UPDATE_SPEED && detect_collide(character_x, character_y-1) == 0)
                character_y -= 1;
            else if (jump_length > 2*CHARACTER_Y_UPDATE_SPEED && detect_collide(character_x, character_y+1) == 0)
                character_y += 1;
        }
    } else if (detect_collide(character_x, character_y+1) == 0 && game_tick % CHARACTER_Y_UPDATE_SPEED == 0) {
        // Apply gravity even if not jumped yet
        character_y += 1;
    }
}

void update_character(void) {
    prev_character_x = character_x;
    prev_character_y = character_y;
    update_character_pos();
    if (character_state == IMMUNE) {
        // Handle immunity after taking damage while holding powerup
        if (game_tick >= last_damage_tick + IMMUNITY_TIME) {
            // Immunity timeout
            character_texture = CYAN;
            character_state = ALIVE;
        } else if (game_tick % IMMUNITY_TEXTURE_TIME == 0) {
            // Flash texture
            if (character_texture == CYAN)
                character_texture = BLUE;
            else
                character_texture = CYAN;
        }
    }
}


// Adversary methods
#define MAX_NUM_ADV 40
uint8 num_adv;
uint8 prev_adv_x[MAX_NUM_ADV];
uint8 prev_adv_y[MAX_NUM_ADV];
uint8 adv_x[MAX_NUM_ADV];
uint8 adv_y[MAX_NUM_ADV];
uint8 adv_dest_x[MAX_NUM_ADV];
uint8 adv_dest_y[MAX_NUM_ADV];
uint32 adv_speed[MAX_NUM_ADV];
uint8 adv_radius[MAX_NUM_ADV];
uint8 adv_dir[MAX_NUM_ADV];
uint8 adv_state[MAX_NUM_ADV];
uint8 adv_type[MAX_NUM_ADV];

void update_adv(uint8 adv) {
    // Don't update if it's not time or adversary dead
    if (adv_state[adv] == DEAD || game_tick % adv_speed[adv] != 0)
        return;
    prev_adv_x[adv] = adv_x[adv];
    prev_adv_y[adv] = adv_y[adv];
    if (adv_radius[adv] == 0)
        return;
    // Depending on direction, we will go one step in that direction.
    // Then, check if we've reached our destination.
    // If so, set a new destination and move in the opposite direction.
    if (adv_dir[adv] == UP) {
        adv_y[adv] = adv_y[adv] - 1;
        if (adv_y[adv] == adv_dest_y[adv]) {
            adv_dest_y[adv] = adv_y[adv] + adv_radius[adv];
            adv_dir[adv] = DOWN;
        }
    } else if (adv_dir[adv] == DOWN) {
        adv_y[adv] = adv_y[adv] + 1;
        if (adv_y[adv] == adv_dest_y[adv]) {
            adv_dest_y[adv] = adv_y[adv] - adv_radius[adv];
            adv_dir[adv] = UP;
        }
    } else if (adv_dir[adv] == LEFT) {
        adv_x[adv] = adv_x[adv] - 1;
        if (adv_x[adv] == adv_dest_x[adv]) {
            adv_dest_x[adv] = adv_x[adv] + adv_radius[adv];
            adv_dir[adv] = RIGHT;
        }
    } else if (adv_dir[adv] == RIGHT) {
        adv_x[adv] = adv_x[adv] + 1;
        if (adv_x[adv] == adv_dest_x[adv]) {
            adv_dest_x[adv] = adv_x[adv] - adv_radius[adv];
            adv_dir[adv] = LEFT;
        }
    }
}

void batch_update_adv(void) {
    uint8 adv;
    for (adv=0; adv<num_adv; adv++) {
        if (adv_state[adv] != DEAD)
            update_adv(adv);
    }
}

void define_adv(uint8 adv, uint8 x, uint8 y, uint8 dest_x, uint8 dest_y, uint32 speed, uint8 type) {
    /*
        Define starting values for a single adversary.
        Must call batch_init_adv after this method to complete initialization.
    */
    adv_x[adv] = x;
    adv_y[adv] = y;
    adv_dest_x[adv] = dest_x;
    adv_dest_y[adv] = dest_y;
    adv_speed[adv] = speed;
    adv_type[adv] = type;
}

void batch_init_adv(void) {
    /*
        Helper for level code to initialize adversaries. 
        Level code should only need to init number of adversaries, 
        start position, destination position, speed, and type.
    */
    uint8 adv;
    for (adv=0; adv<num_adv; adv++) {
        // prev location arbitrary upon init
        prev_adv_x[adv] = adv_x[adv];
        prev_adv_y[adv] = adv_y[adv];
        adv_state[adv] = ALIVE;
        // determine direction of motion (only support up/down or left/right)
        if (adv_dest_y[adv] != adv_y[adv]) {
            adv_dir[adv] = (adv_dest_y[adv] > adv_y[adv]) ? DOWN : UP;
            adv_radius[adv] = (adv_dest_y[adv] > adv_y[adv]) ? 
                adv_dest_y[adv] - adv_y[adv] : adv_y[adv] - adv_dest_y[adv];
        } else {
            adv_dir[adv] = (adv_dest_x[adv] > adv_x[adv]) ? RIGHT : LEFT;
            adv_radius[adv] = (adv_dest_x[adv] > adv_x[adv]) ? 
                adv_dest_x[adv] - adv_x[adv] : adv_x[adv] - adv_dest_x[adv];
        }
    }
}

// Level methods
void populate_framework(uint8 level[20][25]) {
    // Method for loading level into global framework
    int y;
    for (y=0; y<20; y++) {
        int x;
        for (x=0; x<25; x++) {
            framework[y][x] = level[y][x];
        }
    }
}

/*
    Level loader should:
        define character state and texture
        define start pos of character
        define number of adversaries, their start and destination positions, and speed
        move level definition into game framework
*/
void load_level_1(void) {
    character_state = ALIVE;
    character_texture = CYAN;
    start_x = 0;
    start_y = 18;
    
    num_adv = 4;
    define_adv(0, 10, 10, 10, 13, 30, RED);
    define_adv(1, 5 , 18, 20, 18, 30, RED);
    define_adv(2, 1, 6, 4, 6, 60, RED);
    define_adv(3, 5, 6, 7, 6, 60, RED);
    
    batch_init_adv();
    populate_framework(level_1);
}

void load_level_2(void) {
    character_state = ALIVE;
    character_texture = CYAN;
    start_x = 0;
    start_y = 0;
    
    num_adv = 24;
    define_adv(0, 0, 3, 3, 3, 60, YELLOW);
    define_adv(1, 3, 5, 0, 5, 60, YELLOW);
    define_adv(2, 0, 7, 3, 7, 60, YELLOW);
    
    define_adv(3, 0, 12, 3, 12, 30, YELLOW);
    define_adv(4, 3, 14, 0, 14, 30, YELLOW);
    
    define_adv(5, 4, 18, 4, 15, 30, YELLOW);
    define_adv(6, 6, 18, 6, 15, 30, YELLOW);
    
    define_adv(7, 14, 18, 14, 15, 30, YELLOW);
    define_adv(8, 18, 15, 18, 18, 30, YELLOW);
    
    
    define_adv(9 , 14, 4, 18, 4, 30, YELLOW);
    define_adv(10, 14, 6, 18, 6, 30, YELLOW);
    define_adv(11, 14, 8, 18, 8, 30, YELLOW);
    define_adv(12, 14, 10, 18, 10, 30, YELLOW);
    define_adv(13, 14, 12, 18, 12, 30, YELLOW);
    
    define_adv(14, 12, 3, 12, 3, 30, RED);
    define_adv(15, 12, 4, 12, 4, 30, RED);
    define_adv(16, 12, 5, 12, 5, 30, RED);
    define_adv(17, 12, 6, 12, 6, 30, RED);
    define_adv(18, 12, 7, 12, 7, 30, RED);
    define_adv(19, 12, 8, 12, 8, 30, RED);
    define_adv(20, 12, 9, 12, 9, 30, RED);
    define_adv(21, 12, 10, 12, 10, 30, RED);
    define_adv(22, 12, 11, 12, 11, 30, RED);
    define_adv(23, 12, 12, 12, 12, 30, RED);
    
    batch_init_adv();
    populate_framework(level_2);
}

void load_level_3(void) {
    character_state = ALIVE;
    character_texture = CYAN;
    start_x = 0;
    start_y = 18;
    
    num_adv = 24;
    define_adv(0, 6, 6, 6, 0, 30, RED);
    define_adv(1, 12, 6, 12, 0, 30, RED);
    
    define_adv(2, 2, 19, 2, 19, 30, YELLOW);
    define_adv(3, 3, 19, 3, 19, 30, RED);
    define_adv(4, 4, 19, 4, 19, 30, YELLOW);
    define_adv(5, 5, 19, 5, 19, 30, YELLOW);
    define_adv(6, 6, 19, 6, 19, 30, RED);
    define_adv(7, 7, 19, 7, 19, 30, YELLOW);
    define_adv(8, 8, 19, 8, 19, 30, YELLOW);
    define_adv(9, 9, 19, 9, 19, 30, RED);
    define_adv(10, 10, 19, 10, 19, 30, YELLOW);
    define_adv(11, 11, 19, 11, 19, 30, YELLOW);
    define_adv(12, 12, 19, 12, 19, 30, RED);
    define_adv(13, 13, 19, 13, 19, 30, YELLOW);
    define_adv(14, 14, 19, 14, 19, 30, YELLOW);
    define_adv(15, 15, 19, 15, 19, 30, RED);
    define_adv(16, 16, 19, 16, 19, 30, YELLOW);
    define_adv(17, 17, 19, 17, 19, 30, YELLOW);
    define_adv(18, 18, 19, 18, 19, 30, RED);
    define_adv(19, 19, 19, 19, 19, 30, YELLOW);
    define_adv(20, 20, 19, 20, 19, 30, YELLOW);
    define_adv(21, 21, 19, 21, 19, 30, RED);
    define_adv(22, 22, 19, 22, 19, 30, YELLOW);
    define_adv(23, 23, 19, 23, 19, 30, YELLOW);
    
    batch_init_adv();
    populate_framework(level_3);
}

// Video methods
void blackout(void) {
    // Erases everything on screen (good for transitions)
    int y;
    for (y=0; y<20; y++) {
        int x;
        for (x=0; x<25; x++) {
            display[y][x] = BLACK;
        }
    }
}

void populate_display(void) {
    // Move framework into display buffer (good for level init)
    int y;
    for (y=0; y<20; y++) {
        int x;
        for (x=0; x<25; x++) {
            display[y][x] = framework[y][x];
        }
    }
}

void render(void) {
    if (game_state == WON || game_state == LOST)
        return;
    // Restore display
    if (framework[character_y][character_x] == PURPLE) {
        // Powerup hit, remove from level
        framework[character_y][character_x] = BLACK;
    }
    if (prev_character_x != character_x || prev_character_y != character_y) {
        // If character moved, restore last position
        display[prev_character_y][prev_character_x] = framework[prev_character_y][prev_character_x];
    }
    int adv;
    for (adv=0; adv<num_adv; adv++) {
        if (prev_adv_x[adv] != adv_x[adv] || prev_adv_y[adv] != adv_y[adv]) {
            // If adversary moved, restore last position
            display[prev_adv_y[adv]][prev_adv_x[adv]] = framework[prev_adv_y[adv]][prev_adv_x[adv]];
        }
        if (adv_state[adv] == DEAD) {
            // If adversary killed, remove from level
            display[adv_y[adv]][adv_x[adv]] = framework[adv_y[adv]][adv_x[adv]];
        }
    }
    // Render character and adversaries
    display[character_y][character_x] = character_texture;
    for (adv=0; adv<num_adv; adv++) {
        if (adv_state[adv] == ALIVE)
            display[adv_y[adv]][adv_x[adv]] = adv_type[adv];
    }
}

// Menu methods
#define MENU_UPDATE_RATE 24
uint8 selected_level = 1;

void clear_selector(void) {
    display[10 + 2*selected_level][10] = BLACK;
}
void render_selector(void) {
    display[10 + 2*selected_level][10] = CYAN;
}

void load_selected_level(void) {
    if (selected_level == 1) {
        load_level_1();
    } else if (selected_level == 2) {
        load_level_2();
    } else {
        load_level_3();
    }
    character_x = start_x;
    character_y = start_y;
    game_state = INGAME;
    blackout();
    populate_display();
}

void load_menu(void) {
    game_state = MENU;
    populate_framework(menu);
    blackout();
    populate_display();
}

void update_menu(void) {
    if (game_tick % MENU_UPDATE_RATE == 0) {
        // Every so often, poll joystick for input and adjust level selector
        clear_selector();
        if (joystick_y_state == DOWN) {
            selected_level += 1;
        } else if (joystick_y_state == UP) {
            selected_level -= 1;
        }
        if (selected_level > 3) {
            selected_level = 3;
        } else if (selected_level < 1) {
            selected_level = 1;
        }
        render_selector();
    }
    if (green_button_state == PUSHED) {
        load_selected_level();
    }
}

// Game logic
void detect_hit(void) {
    uint8 adv;
    // For every living adversary, if it collides with the player from the top, it will die.
    // Otherwise, the player will do damage to it.
    for (adv=0; adv<num_adv; adv++) {
        if (adv_state[adv] == DEAD)
            continue;
        if (adv_x[adv] == character_x && adv_y[adv] == character_y) {
            if (prev_character_y < character_y && adv_type[adv] == RED) {
                // player comes from above, kills adversary
                adv_state[adv] = DEAD;
                play_adv_death_sound(12);
            }
            else {
                // player comes from another direction, gets damaged
                if (character_texture == BLUE && character_state == ALIVE) {
                    // Character is holding powerup, gets put into brief state of immunity
                    character_state = IMMUNE;
                    last_damage_tick = game_tick;
                    play_character_death_sound(12);
                } else if (character_state != IMMUNE) {
                    character_state = DEAD;
                    play_character_death_sound(12);
                }
            }
        } else if (adv_x[adv] == character_x && adv_y[adv] == character_y+1 && adv_type[adv] == RED) {
                // player comes from above, kills adversary
                adv_state[adv] = DEAD;
                play_adv_death_sound(12);
        }
    }
}

void detect_powerup(void) {
    if (framework[character_y][character_x] == PURPLE) {
        character_texture = BLUE;
    }
}

void detect_win_loss(void) {
    if (character_state == DEAD) {
        game_state = LOST;
        populate_framework(loss_screen);
        blackout();
        populate_display();
    } else if (framework[character_y][character_x] == GREEN) {
        game_state = WON;
        populate_framework(win_screen);
        blackout();
        populate_display();
        start_win_song();
    }
}

void init_game(void) {
    load_menu();
}

void update_game(void) {
    game_tick += 1;
    if (game_state == INGAME) {
        update_character();
        detect_powerup();
        detect_hit();
        batch_update_adv();
        detect_hit();
        detect_win_loss();
        render();
        if (red_button_state == PUSHED) {
            load_menu();
        }
    } else if (game_state == MENU) {
        update_menu();
    } else if (game_state == WON || game_state == LOST) {
        if (green_button_state == PUSHED) {
            load_selected_level();
        } else if (red_button_state == PUSHED) {
            load_menu();
        }
    }
    update_game_audio();
}

/* END GAME */




int main()
{    
    enable_dma();
    
    // test display
    line_buffer[0] = 255;
    line_buffer[23] = 255;
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Line_Int_StartEx( Line_Int_Handler );
    
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
    
    VDAC8_1_Start();
    
    // Game timer will decrement every millisecond
    GameTimer_Start();

    uint32 game_update_time = 0;
    uint32 audio_update_time = 0;
    uint8 audio_t = 0;
    
    // Game init
    init_game();
    for(;;)
    {
        // Negate unsigned down-counter to make it up-counter
        uint32 t = -GameTimer_ReadCounter();
        
        // Update game stuff every 4 milliseconds
        if (t - game_update_time > 3) {
            // UPDATE CONTROLLER STATE
            update_green_button_state();
            update_red_button_state();
            update_joystick_x();
            update_joystick_y();
            
            // UPDATE GAME STATE
            update_game();
            
            game_update_time = t;
            
        }
        
        // UPDATE AUDIO
        // update square wave every millisecond
        if (t - audio_update_time >= 1 && audio_state == PLAYING) {
            audio_t += 1;
            if (audio_t == audio_high_time) {
                VDAC8_1_SetValue(0);
            } else if (audio_t == audio_high_time + audio_low_time) {
                VDAC8_1_SetValue(255);
                audio_t = 0;
            }
            audio_update_time = t;
        }
        // UPDATE VIDEO IF NEEDED
    }
}

/* [] END OF FILE */

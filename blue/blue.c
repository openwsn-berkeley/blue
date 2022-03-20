#include "nrf52840.h"

//=========================== defines =========================================

// https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf52840_dk%2FUG%2Fdk%2Fhw_buttons_leds.html
// LED 1 P0.13
// LED 2 P0.14
// LED 3 P0.15
// LED 4 P0.16

//=========================== prototypes ======================================

int main_app(void);

//=========================== variables =======================================

typedef struct {
    uint32_t       dummy;
} app_vars_t;

app_vars_t app_vars;

typedef struct {
    uint32_t       dummy;
} app_dbg_t;

app_dbg_t app_dbg;

//=========================== main ============================================

int main(void) {
    
    // all LEDs enabled
    NRF_P0->PIN_CNF[13]                = 0x00000003;            // LED 1
    NRF_P0->PIN_CNF[14]                = 0x00000003;            // LED 2
    NRF_P0->PIN_CNF[15]                = 0x00000003;            // LED 3
    NRF_P0->PIN_CNF[16]                = 0x00000003;            // LED 4

    // all LEDs off
    NRF_P0->OUTSET                     = (0x00000001 << 13);    // LED 1
    NRF_P0->OUTSET                     = (0x00000001 << 14);    // LED 2
    NRF_P0->OUTSET                     = (0x00000001 << 15);    // LED 3
    NRF_P0->OUTSET                     = (0x00000001 << 16);    // LED 4

    // LED3 on
    //NRF_P0->OUTCLR                   = (0x00000001 << 13);    // LED 1
    //NRF_P0->OUTCLR                   = (0x00000001 << 14);    // LED 2
    NRF_P0->OUTCLR                     = (0x00000001 << 16);    // LED 3
    //NRF_P0->OUTCLR                   = (0x00000001 << 15);    // LED 4

    // handover to app
    return main_app();
}

int __attribute((section(".ARM.__at_0x0001000"))) main_app(void) {
    
    // LED1 on
    NRF_P0->OUTCLR                     = (0x00000001 << 13);    // LED 1

    // loop
    while(1) {

        // wait for event
        __SEV(); // set event
        __WFE(); // wait for event
        __WFE(); // wait for event
    }
}

//=========================== helpers =========================================

//=========================== interrupt handlers ==============================

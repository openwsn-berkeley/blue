#include "nrf52840.h"
#include "app.h"

//=========================== defines =========================================

// https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf52840_dk%2FUG%2Fdk%2Fhw_buttons_leds.html
// LED 1 P0.13
// LED 2 P0.14
// LED 3 P0.15
// LED 4 P0.16

//=========================== prototypes ======================================

//=========================== variables =======================================

typedef struct {
    uint32_t       dummy;
} blue_vars_t;

blue_vars_t blue_vars;

typedef struct {
    uint32_t       dummy;
} blue_dbg_t;

blue_dbg_t blue_dbg;

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
    return app_main();
}

//=========================== helpers =========================================

//=========================== interrupt handlers ==============================

#include <string.h>
#include "nrf52840.h"
#include "app.h"

//=========================== defines =========================================

// https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf52840_dk%2FUG%2Fdk%2Fhw_buttons_leds.html
// LED 1 P0.13
// LED 2 P0.14
// LED 3 P0.15
// LED 4 P0.16

#define CONTAINER_APP_CURRENT (512*1024)    // address of the container of the current app
#define CONTAINER_APP_NEW     (768*1024)    // address of the container of the new app, if any
#define CONTAINER_APP_LENGTH  (4*1024)      // length of an app container, in bytes

//=========================== prototypes ======================================

typedef int appfunc_t(void);

//=========================== variables =======================================

typedef struct {
    appfunc_t*     appfunc;
    uint32_t*      word;
} blue_vars_t;

blue_vars_t blue_vars;

typedef struct {
    uint32_t       dummy;
} blue_dbg_t;

blue_dbg_t blue_dbg;

//=========================== main ============================================

int main(void) {
    
    // initialize
    memset(&blue_vars,0x00,sizeof(blue_vars_t));

    //=== set LEDs indicating execution started

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
    NRF_P0->OUTCLR                     = (0x00000001 << 15);    // LED 3
    
    //=== load new app, if needed

    // WARNING: not immune to powering off during this section of code,
    //     i.e. you brick the part if you switch off the device during step 2 or step 3

    // determine whether there is anything in the container for new apps
    blue_vars.word = (uint32_t*)(CONTAINER_APP_NEW);
    if (*blue_vars.word!=0xffffffff) {
        // there is a new app in the new app container@

        // step 1. clear current app container
        NRF_NVMC->CONFIG               = 0x00000002; // 2 == Erase enabled
        NRF_NVMC->ERASEPAGE            = CONTAINER_APP_CURRENT;
        while(NRF_NVMC->READY==0);
        NRF_NVMC->CONFIG               = 0x00000000; // 0 == Read only access

        // step 2. copy data over
        NRF_NVMC->CONFIG               = 0x00000001; // 1 == Write enabled
        memcpy((uint8_t*)(CONTAINER_APP_CURRENT),(uint8_t*)(CONTAINER_APP_NEW),CONTAINER_APP_LENGTH);
        NRF_NVMC->CONFIG               = 0x00000000; // 0 == Read only access

        // step 3. clear new app container
        NRF_NVMC->CONFIG               = 0x00000002; // 2 == Erase enabled
        NRF_NVMC->ERASEPAGE            = CONTAINER_APP_NEW;
        while(NRF_NVMC->READY==0);
        NRF_NVMC->CONFIG               = 0x00000000; // 0 == Read only access

    }

    //=== handover to app

    // WARNING: no attempt to verify this code runs
    // recommended fix:
    //  - have a CRC in the image, check that before running
    //  - arms a watchdog timer before handing over; cancel that watchdog from within the app if working
    blue_vars.appfunc                  = (appfunc_t*)(CONTAINER_APP_CURRENT+1); // we shift by one byte to point to the right entry of the function
    return blue_vars.appfunc();
}

//=========================== helpers =========================================

//=========================== interrupt handlers ==============================

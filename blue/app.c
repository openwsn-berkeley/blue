#include <string.h>
#include "nrf52840.h"

//=========================== defines =========================================

// simple program which sets LED2, crafted to be loaded at address 0x00080000
const uint8_t newprogram[] = {
    0x40,0xF2,0x0C,0x51, 0xC5,0xF2,0x00,0x01, 0x4F,0xF4,0x80,0x40, 0x08,0x60,0x40,0xBF,
    0x20,0xBF,0x20,0xBF, 0xFB,0xE7,
                                   0xff,0xff // padding
}; 

//=========================== prototypes ======================================

//=========================== variables =======================================

//=========================== public ==========================================

int __attribute((section(".app1"))) app_main(void) {
    
    // LED on
    NRF_P0->OUTCLR                     = (0x00000001 << 13);    // LED 1
    //NRF_P0->OUTCLR                   = (0x00000001 << 14);    // LED 2

    // write new program in CONTAINER_APP_NEW
    NRF_NVMC->CONFIG                   = 0x00000001; // 1 == Write enabled
    memcpy((uint8_t*)(768*1024),&newprogram,sizeof(newprogram));
    NRF_NVMC->CONFIG                   = 0x00000000; // 0 == Read only access

    // loop
    while(1) {

        // wait for event
        __SEV(); // set event
        __WFE(); // wait for event
        __WFE(); // wait for event
    }
}

//=========================== private =========================================

#pragma once  // Move this to the top 

#define MAX_DEFERRED_EXECUTORS 10 
#define COMBO_COUNT COMBO_LENGTH 
#define TAPPING_TERM 160 

/* Split Settings */
#define SPLIT_USB_DETECT
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define SELECT_SOFT_SERIAL_SPEED 1 // Sets a slower, more stable communication speed
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000
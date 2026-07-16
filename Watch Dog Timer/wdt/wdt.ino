#include <Arduino.h>

// Watchdog timeout in seconds
#define WDT_TIMEOUT 2
int i = 1;
void setupWatchdog()
{
    // Configure watchdog
    NRF_WDT->CONFIG = WDT_CONFIG_SLEEP_Run;    // Run during sleep
    NRF_WDT->CRV = WDT_TIMEOUT * 32768;        // Timeout = 5 seconds
    NRF_WDT->RREN = WDT_RREN_RR0_Enabled;      // Enable Reload Register 0
    NRF_WDT->TASKS_START = 1;                  // Start Watchdog
}

void feedWatchdog()
{
    // Reload watchdog timer
    NRF_WDT->RR[0] = WDT_RR_RR_Reload;
}

void setup()
{
    Serial.begin(115200);

    while (!Serial)
        ;

    Serial.println("Starting...");

    setupWatchdog();
}

void loop()
{
    // Your application code
    Serial.println("System Running");
    Serial.println(i);
    // Feed watchdog

    feedWatchdog();
    i=i+1;
    delay(4000);
    
}
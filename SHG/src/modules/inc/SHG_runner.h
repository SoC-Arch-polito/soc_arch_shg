#include <stdbool.h>
#ifndef _SHG_RUNNER_H
#define _SHG_RUNNER_H

    void SHG_runner(void const * argument);
    void SHG_start();
    void SHG_stop();
    void SHG_rst();
    void SHG_connect();
    bool SHG_getHeatingSystemStatus();
    bool SHG_getWaterSystemStatus();
    bool SHG_getLightSystemStatus();
    int SHG_getTemperature();
    int SHG_getLight();
    int SHG_getHumidity();    
    bool SHG_getPowered();
    bool SHG_getPairStatus();
    int SHG_getTresholdTemperature();
    int SHG_getTresholdHumidity();
    int SHG_getTresholdLight();
    void SHG_setTresholdTemperature(int Temperature);
    void SHG_setTresholdHumidity(int Humidity);
    void SHG_setTresholdLight(int Light);
    void SHG_heatingSystemOn();
    void SHG_waterSystemOn();
    void SHG_lightSystemOn();
    void SHG_heatingSystemOff();
    void SHG_waterSystemOff();
    void SHG_lightSystemOff();

#endif
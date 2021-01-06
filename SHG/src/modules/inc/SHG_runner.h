#ifndef _SHG_RUNNER_H
#define _SHG_RUNNER_H

    void SHG_runner(void const * argument);
    void SHG_start();
    void SHG_stop();
    void SHG_rst();
    int SHG_getTemperature();
    int SHG_getLight();
    int SHG_getHumidity();    
    int SHG_getTresholdTemperature();
    int SHG_getTresholdHumidity();
    int SHG_getTresholdLight();
    void SHG_setTresholdTemperature(int Temperature);
    void SHG_setTresholdHumidity(int Humidity);
    void SHG_setTresholdLight(int Light);

#endif
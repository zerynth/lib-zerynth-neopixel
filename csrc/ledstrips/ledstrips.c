#include "viper.h"


#define MUL_DIV_APPROX(x,mul,div) (((x)*(mul))/(div))


//timings are here: https://learn.adafruit.com/adafruit-neopixel-uberguide/advanced-coding
C_NATIVE(neopixel_ledstrip_on) {
    C_NATIVE_UNWARN();


    register uint32_t cyc, time, t;
    uint8_t *p;
    int32_t n;
    int32_t pin;

    if (parse_py_args("is", nargs, args, &pin, &p, &n) != 2)
        return ERR_TYPE_EXC;
    uint32_t UTICKS = _system_frequency / 1000000;
    uint32_t TIME_800_0 = MUL_DIV_APPROX(UTICKS, 200, 1000);
    uint32_t TIME_800_1 = MUL_DIV_APPROX(UTICKS, 700, 1000);
    uint32_t PERIOD_800 = MUL_DIV_APPROX(UTICKS, 1200, 1000);
    uint8_t pix, mask;
    uint32_t i;
    volatile uint32_t *now = vosTicks();
    void *port = vhalPinGetPort(pin);
    int pad = vhalPinGetPad(pin);

    //FORMAT is GRB!!!

    //debug("neopixel_ledstrip_on: pin %x n %i t0: %i t1: %i tp: %i now:%x %x\n", pin, n, TIME_800_0, TIME_800_1, PERIOD_800, *now, now);
    vosSysLock();
    //vhalPinFastClear(port, pad);
    //time = *now;
    //while (*now - time < MUL_DIV_APPROX(UTICKS, 50000, 1000));
    time = *now;
    for (i = 0; i < n; i++) {
        pix = p[i];
        while (mask) {
            t = (pix & mask) ? TIME_800_1 : TIME_800_0;
            //TH
            time = *now;
            vhalPinFastSet(port, pad);
            while (*now - time < t);
            //TL
            vhalPinFastClear(port, pad);
            mask = mask >> 1;
            while (*now - time < (PERIOD_800));
        }
        mask = 128;
        //while (*now - time < PERIOD_800);
    }
    vosSysUnlock();
    vhalPinFastClear(port, pad);
    time = *now;
    while (*now - time < MUL_DIV_APPROX(UTICKS, 50000, 1000));
    return ERR_OK;
}

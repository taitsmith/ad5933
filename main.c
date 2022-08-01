#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "ad5933.h"

float           temperature = 0;
float           impedanceK  = 0;
double          impedance   = 0;
double          gainFactor  = 0;

int main() {

    //initialise our device
    struct ad5933_dev ad5933Dev;
    ad5933Dev = *(struct ad5933_dev *)malloc(sizeof(ad5933Dev));

    struct ad5933_init_param ad5933InitParam;

    if (ad5933_init((struct ad5933_dev **) &ad5933Dev, ad5933InitParam) == 0) {
        printf("Device OK");
    } else {
        printf("Device Error");
        return -1; //oops
    }

    //reset
    ad5933_reset(&ad5933Dev);

    //set system clock
    ad5933_set_system_clk(&ad5933Dev, AD5933_CONTROL_INT_SYSCLK, 0);

    //set range and gain
    ad5933_set_range_and_gain(&ad5933Dev, AD5933_RANGE_2000mVpp, AD5933_GAIN_X5);

    //read and display temp
    temperature = ad5933_get_temperature(&ad5933Dev);
    printf("%f", temperature);

    //config sweep params
    //change these to change the range of your sweep or the granularity
    ad5933_config_sweep(&ad5933Dev,
                        30000, //start at 30khz
                        1000,
                        500);   //500 increments

    //start sweep
    ad5933_start_sweep(&ad5933Dev);

    return 0;
}

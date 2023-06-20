#include <stdio.h>
#include <stdint.h>

#define    TEMPERATURE_INTERVAL    10

static uint16_t Pt100Table[] = {
        ///-200~ -110
        1849, 2280, 2708, 3132, 3553, 3971, 4387, 4800, 5211, 5619,
        ///-100 ~ -10
        6025, 6430, 6833, 7233, 7633, 8031, 8427, 8822, 9216, 9609,
        ///0~90
        10000, 10390, 10779, 11167, 11554, 11940, 12324, 12707, 13089, 13470,
        ///100~190
        13850, 14229, 14606, 14982, 15358, 15731, 16104, 16476, 16846, 17216,
        ///200~290
        17584, 17951, 18317, 18682, 19045, 19407, 19769, 20129, 20488, 20845,
        ///300~390
        21202, 21560, 21915, 22268, 22620, 22971, 23321, 23670, 24017, 24364,
        ///400~490
        24709, 25053, 25396, 25737, 26078, 26417, 26756, 27093, 27429, 27764,
        ///500~590
        28097, 28430, 28761, 29091, 29420, 29748, 30075, 30401, 30725, 31048,
        ///600~690
        31370, 31691, 32011, 32330, 32647, 32964, 33279, 33593, 33906, 34217,
        ///700~790
        34528, 34837, 35146, 35453, 35759, 36063, 36367, 36669, 36971, 37271,
        ///800~850
        37570, 37868, 38165, 38460, 38754, 39048,

};

static int16_t PtSensorOhmsToTemperature(uint16_t Ohms) {
    uint8_t i;
    int16_t ScaledValue;
    float diff, span, InterpolatedValue;

    for (i = 0; i < 106; i++) //-200 ~ 850
    {
        if (Pt100Table[i] > Ohms) {
            span = Pt100Table[i] - Pt100Table[i - 1];
            diff = ((Ohms) - (Pt100Table[i - 1]));
            InterpolatedValue = (diff / span) * TEMPERATURE_INTERVAL;
            InterpolatedValue *= 10;
            //Keeps  decimal places
            ScaledValue = (-200 + ((i - 1) * 10)) * 10;
            //decimal places
            ScaledValue = (ScaledValue) + (int16_t) InterpolatedValue;
            break;
        }
    }
    return (int16_t) ScaledValue;
}

/*
 *  PT100阻值温度对照表
 *  https://www.guilcor.com/content/31-table-de-conversion-des-sondes-pt100
 */

int main() {
    uint16_t PT100_Ohms = 12355;
    uint16_t Temperature = PtSensorOhmsToTemperature(PT100_Ohms);
    printf("PT100_Ohms: %d Temperature value: %d\n",PT100_Ohms, Temperature);
    return 0;
}
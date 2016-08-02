#include <stdio.h>
#include <stdlib.h>

#define PAD_CTL_LVE                     (1 << 22)
#define PAD_CTL_HYS                     (1 << 16)
#define PAD_CTL_PUE                     (1 << 13)
#define PAD_CTL_PKE                     (1 << 12)
#define PAD_CTL_ODE                     (1 << 11)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


int main(int argc, char *argv[])
{
    if (argc<2) return 0;
    long num = (long)strtol(argv[1], NULL, 16);

    printf("m: [%c] %c [%c%c%c%c%c] %c %c%c %c %c %c [%c%c%c] %c%c %c%c%c [%c%c] %c\n",
             BYTE_TO_BINARY(num>>16), BYTE_TO_BINARY(num>>8), BYTE_TO_BINARY(num));


    if (num == 0x80000000) {
        printf("Default, do not change\n");
        return 0;
    }

    if (num & PAD_CTL_LVE) {
        printf("LVE:\t1\tLow voltage\n");
    } else {
        printf("LVE:\t0\tHigh voltage\n");
    }

    if (num & PAD_CTL_HYS) {
        printf("HYS:\t1\tSchmitt trigger input\n");
    } else {
        printf("HYS:\t0\tCMOS input\n");
    }

    const char *pullupdowns[4] = {
        "100k ohm pull down",
        "47k ohm pull up",
        "100k ohm pull up",
        "22k ohm pull up"
    };
    int pullupdown = (num & (3 << 14)) >> 14;
    printf("PUS:\t%d\tPull up/down: %s\n", pullupdown, pullupdowns[pullupdown]);

    if (num & PAD_CTL_PUE) {
        printf("PUE:\t1\tPull enabled\n");
    } else {
        printf("PUE:\t0\tKeeper enabled\n");
    }

    printf("PKE:\t%d\tPull/keeper ", (num & PAD_CTL_PKE) ? 1 : 0);
    if (num & PAD_CTL_PKE) {
        printf("enabled\n");
    } else {
        printf("disabled\n");
    }

    if (num & PAD_CTL_ODE) {
        printf("ODE:\t1\tOpen drain output (enabled)\n");
    } else {
        printf("ODE:\t0\tCMOS output (disabled)\n");
    }

    const char *speeds[4] = { "Reserved", "Low, 50MHz", "Medium, 100MHz", "Maximum, 200MHz" };
    long speed = (num & (3 << 6)) >> 6;
    printf("SPEED\t%d\t%s\n", speed, speeds[speed]);

    const char *drivestrengths[8] = {
            "HI-Z",
            "247 ohm",
            "126 ohm",
            "84 ohm",
            "57 ohm",
            "47 ohm",
            "40 ohm",
            "34 ohm"
    };
    long drivestrength = (num & (7 << 3)) >> 3;
    printf("DSE:\t%d\tDrive strength: %s\n", drivestrength, drivestrengths[drivestrength]);

    printf("SRE:\t%d\tSlew rate control: ", num & 1);
    if (num & 1) {
        printf("fast\n");
    } else {
        printf("slow\n");
    }

    return 0;
}

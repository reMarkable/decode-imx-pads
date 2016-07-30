#include <stdio.h>
#include <stdlib.h>

#define PAD_CTL_LVE                     (1 << 22)
#define PAD_CTL_HYS                     (1 << 16)
#define PAD_CTL_PUE                     (1 << 13)
#define PAD_CTL_PKE                     (1 << 12)
#define PAD_CTL_ODE                     (1 << 11)

int main(int argc, char *argv[])
{
    if (argc<2) return 0;
    int num = (int)strtol(argv[1], NULL, 16);

    printf("Slew rate control: ");
    if (num & 1) {
        printf("fast\n");
    } else {
        printf("slow\n");
    }

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
    printf("Drive strength: %s\n", drivestrengths[(num & (7 << 3)) >> 3]);

    const char *speeds[4] = { "Reserved", "Low, 50MHz", "Medium, 100MHz", "Maximum, 200MHz" };
    printf("Speed: %s\n", speeds[(num & (3 << 6)) >> 6]);

    if (num & PAD_CTL_ODE) {
        printf("Open drain output\n");
    } else {
        printf("CMOS output\n");
    }

    printf("Pull/keeper ");
    if (num & PAD_CTL_PKE) {
        printf("enabled\n");
    } else {
        printf("disabled\n");
    }

    if (num & PAD_CTL_PUE) {
        printf("Pull enabled\n");
    } else {
        printf("Keeper enabled\n");
    }

    const char *pullupdowns[4] = {
        "100k ohm pull down",
        "47k ohm pull up",
        "100k ohm pull up",
        "22k ohm pull up"
    };
    printf("Pull up/down: %s\n", pullupdowns[(num & (3 << 14) >> 14)]);

    if (num & PAD_CTL_HYS) {
        printf("Schmitt trigger input\n");
    } else {
        printf("CMOS input\n");
    }

    if (num & PAD_CTL_LVE) {
        printf("Low voltage\n");
    } else {
        printf("High voltage\n");
    }

    return 0;
}

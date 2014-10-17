#include <stdio.h>
#include <stdint.h>

#include "geohash.h"

void print_binary(uint32_t value)
{
    if (!value)
        return;
    while(value) {
        printf("%d", value & 1);
        value >>= 1;
    }
    printf("\n");
}

int main(int ac, char **av)
{
    CCGeohashStruct geohash;

    geohash.latitude = 48.8567f;
    geohash.longitude = 2.3508f;

    init_from_coordinates(&geohash);
    printf("initial: %f %f %s\n", geohash.latitude, geohash.longitude, geohash.hash);

}

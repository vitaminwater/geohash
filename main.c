#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
    if (ac == 1) {
        printf("Usage: %s [latitude longitude]|[geohash]", av[0]);
        return 1;
    }
    CCGeohashStruct geohash;
    if (ac == 3) {
        CCGeohashStruct geohash;

        geohash.latitude = atof(av[1]);
        geohash.longitude = atof(av[2]);

        init_from_coordinates(&geohash);
    } else {
        memset(geohash.hash, '0', MAX_GEOHASH_LENGTH);
        geohash.hash[MAX_GEOHASH_LENGTH] = 0;
        memcpy(geohash.hash, av[1], strlen(av[1]));
        init_from_hash(&geohash);

    }
    printf("%f %f %s\n", geohash.latitude, geohash.longitude, geohash.hash);
    return 0;
}

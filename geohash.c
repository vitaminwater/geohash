#include "geohash.h"

#define CCGEOHASH_DIV .001373291015625f // 360 / 2^18


/* private functions */

void generate_hash(CCGeohashStruct *geohash)
{
    uint8_t iter = sizeof(geohash->hash) - 1;
    uint32_t longitudebits = geohash->longitudebits;
    uint32_t latitudebits = geohash->latitudebits;
    for (uint8_t i = 0; i < iter; ++i) {
        if (i == iter - 1)
            geohash->hash[iter - i - 1] = '0' + (((longitudebits & 3) << 1) | (latitudebits & 1));
        else
            geohash->hash[iter - i - 1] = '0' + (((longitudebits & 1) << 1) | (latitudebits & 1));
        longitudebits >>= 1;
        latitudebits >>= 1;
    }
    geohash->hash[iter] = 0;
}

void generate_coordinates(CCGeohashStruct *geohash)
{
    geohash->longitude = (double)geohash->longitudebits * CCGEOHASH_DIV + CCGEOHASH_DIV / 2.0f - 180.0f;
    geohash->latitude = (double)geohash->latitudebits * CCGEOHASH_DIV + CCGEOHASH_DIV / 2.0f - 90.0f;
}

/* public functions */

CCGeohashStruct init_neighbour(CCGeohashStruct *geohash, int longitude, int latitude)
{
    CCGeohashStruct result = *geohash;

    result.longitudebits += longitude;
    result.latitudebits += latitude;

    generate_hash(&result);
    generate_coordinates(&result);

    return result;
}

void init_from_hash(CCGeohashStruct *geohash)
{
    uint8_t iter = sizeof(geohash->hash) - 1;
    uint32_t longitudebits = 0;
    uint32_t latitudebit = 0;
    geohash->longitudebits = 0;
    geohash->latitudebits = 0;
    for (int i = 0; i < iter; ++i) {
        uint8_t value = geohash->hash[i] - '0';

        longitudebits = value >> 1;
        latitudebit = value & 1;

        geohash->longitudebits |= longitudebits << (iter - i - 1);
        geohash->latitudebits |= latitudebit << (iter - i - 1);
    }

    generate_coordinates(geohash);
}

void init_from_coordinates(CCGeohashStruct *geohash)
{
    geohash->longitudebits = (geohash->longitude + 180.0f) / CCGEOHASH_DIV;
    geohash->latitudebits = (geohash->latitude + 90.0f) / CCGEOHASH_DIV;

    generate_hash(geohash);
}


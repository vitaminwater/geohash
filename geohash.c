#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct s_geohash
{
    
    double latitude;
    double longitude;
    
    uint32_t latitudebits;
    uint32_t longitudebits;
    
    char hash[18];
    
} CCGeohashStruct;

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

uint32_t generate_bits(double value, double span, uint8_t length, bool firstBy4)
{
    uint32_t result = 0;
    uint8_t offset = length;
    uint8_t div = firstBy4 ? 4 : 2;
    
    //printf("%f %f %d\n", value, span, offset);

    while(offset) {
        span /= div;
        uint32_t div_number = value / span;
        
        value -= span * div_number;
        
        --offset;
        result |= (div_number << offset);
        div = 2;
        //printf("%f %f %d %d\n", value, span, offset, div_number);
    }
    
    //print_binary(result);

    return result;
}

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

CCGeohashStruct init_neighboor(CCGeohashStruct *geohash, int longitude, int latitude)
{
    CCGeohashStruct result = *geohash;

    result.longitudebits += longitude;
    result.latitudebits += latitude;

    generate_hash(&result);

    return result;
}

void init_from_hash(CCGeohashStruct *geohash)
{
    geohash->latitude = 0;
    geohash->longitude = 0;

    uint8_t iter = sizeof(geohash->hash) - 1;
    uint32_t longitudebits = 0;
    uint32_t latitudebit = 0;
    double longitudespan = 360;
    double latitudespan = 180;
    uint8_t div = 4;
    for (int i = 0; i < iter; ++i) {
        uint8_t value = geohash->hash[i] - '0';

        longitudebits = value >> 1;
        latitudebit = value & 1;

        geohash->longitudebits |= longitudebits << (iter - i - 1);
        geohash->latitudebits |= latitudebit << (iter - i - 1);

        geohash->longitude += longitudespan / div * longitudebits;
        longitudespan /= div;
        div = 2;
        geohash->latitude += latitudespan / div * latitudebit;
        latitudespan /= div;
    }

    geohash->longitude += -180 + longitudespan / div;
    geohash->latitude += -90 + latitudespan / div;
}

void init_from_coordinates(CCGeohashStruct *geohash)
{
    geohash->longitudebits = generate_bits(geohash->longitude + 180, 360, 17, true);
    geohash->latitudebits = generate_bits(geohash->latitude + 90, 180, 17, false);

    generate_hash(geohash);
}

int main(int ac, char **av)
{
    CCGeohashStruct geohash;

    geohash.latitude = 0.0f;
    geohash.longitude = 0.0f;

    init_from_coordinates(&geohash);

    print_binary(geohash.longitudebits);
    print_binary(geohash.latitudebits);
    printf("%f %f %s\n", geohash.latitude, geohash.longitude, geohash.hash);

    init_from_hash(&geohash);
    print_binary(geohash.longitudebits);
    print_binary(geohash.latitudebits);
    printf("%f %f %s\n", geohash.latitude, geohash.longitude, geohash.hash);

    CCGeohashStruct neighboorgeohash = init_neighboor(&geohash, 1, 0);
    init_from_hash(&neighboorgeohash);
    printf("neighboor: %f %f %s\n", neighboorgeohash.latitude, neighboorgeohash.longitude, neighboorgeohash.hash);

    neighboorgeohash = init_neighboor(&geohash, 0, 1);
    init_from_hash(&neighboorgeohash);
    printf("neighboor: %f %f %s\n", neighboorgeohash.latitude, neighboorgeohash.longitude, neighboorgeohash.hash);

    neighboorgeohash = init_neighboor(&geohash, 0, 2);
    init_from_hash(&neighboorgeohash);
    printf("neighboor: %f %f %s\n", neighboorgeohash.latitude, neighboorgeohash.longitude, neighboorgeohash.hash);

    neighboorgeohash = init_neighboor(&geohash, 2, 0);
    init_from_hash(&neighboorgeohash);
    printf("neighboor: %f %f %s\n", neighboorgeohash.latitude, neighboorgeohash.longitude, neighboorgeohash.hash);
}

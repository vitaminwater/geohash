#ifndef GEOHASH_H
#define GEOHASH_H

#define MAX_GEOHASH_LENGTH 17

typedef struct s_geohash
{
    
    double latitude;
    double longitude;
    
    char hash[MAX_GEOHASH_LENGTH + 1];
    
    uint32_t latitudebits;
    uint32_t longitudebits;

} CCGeohashStruct;

// creates a neighbour from another geohash
// longitude and latitude are block based unit offset
CCGeohashStruct init_neighbour(CCGeohashStruct *geohash, int longitude, int latitude);

// fills the latitude and longitude fields given a CCGeohashStruct containing a hash in the hash field
void init_from_hash(CCGeohashStruct *geohash);

// fills the hash field given a CCGeohashStruct containing a latitude and longitude
void init_from_coordinates(CCGeohashStruct *geohash);

#endif // GEOHASH_H

#ifndef GEOHASH_H
#define GEOHASH_H

typedef struct s_geohash
{
    
    double latitude;
    double longitude;
    
    uint32_t latitudebits;
    uint32_t longitudebits;
    
    char hash[18];
    
} CCGeohashStruct;

// creates a neighbour from another geohash
// longitude and latitude are block based unit offset
CCGeohashStruct init_neighbour(CCGeohashStruct *geohash, int longitude, int latitude);

// fills the latitude and longitude fields given a CCGeohashStruct containing a hash in the hash field
void init_from_hash(CCGeohashStruct *geohash);

// fills the hash field given a CCGeohashStruct containing a latitude and longitude
void init_from_coordinates(CCGeohashStruct *geohash);

#endif // GEOHASH_H

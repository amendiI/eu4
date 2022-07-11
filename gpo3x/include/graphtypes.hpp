#pragma once
#include <stdint.h>

typedef enum {
    UNDEFINED = 0,
    GRASSLANDS,
    FARMLANDS,
    DRYLANDS,
    COASTLINE,
    SAVANNAH,
    WOODS,
    FOREST,
    HIGHLANDS,
    STEPPES,
    HILLS,
    MARSH,
    COASTAL_DESERT,
    JUNGLE,
    MOUNTAIN,
    DESERT,
    GLACIAL
} terrain;

typedef enum {
    TEMPERATE = 0,
    ARID,
    ARCTIC,
    TROPICAL
} climate;

typedef struct {
    terrain prov_terrain;
    climate prov_climate;
    uint8_t trade_modifier;
    uint8_t cot;
    double goods_modifier;
    double unique_modifier;
} province_data;

typedef struct {
    uint16_t province_id;
    province_data* data;
    double score;
    uint16_t n_neighbors;
    uint16_t* neighbors;
} graphnode;
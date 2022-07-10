#pragma once
#include <stdint.h>

typedef struct {
    char terrain;
    char climate;
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
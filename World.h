#pragma once
#include <Arduboy2.h>
#include "lfsr.h"

class World {
  public:
    static const uint8_t mapWidth = 24; 
    static const uint8_t mapHeight = 24;
    static const uint8_t tileTypes = 16;
//    static const uint8_t miniWidth = 4; 
//    static const uint8_t miniHeight = 6;

    static const uint8_t mainLeft = 0;
    static const uint8_t mainRight = 80;
    static const uint8_t mainTop = 0;
    static const uint8_t mainBottom = HEIGHT;
    
    static const uint8_t miniLeft = 0; //mainRight;
    static const uint8_t miniRight = WIDTH;
    static const uint8_t miniTop = 0;
    static const uint8_t miniBottom = HEIGHT;

    static const uint32_t minSeed = 1;
    static const uint32_t maxSeed = (1ul<<20)-1;
    
    void init(uint32_t seed);    
    void draw(int16_t x, int16_t y);
    void drawMini(int16_t x, int16_t y);
    
  private:
    uint32_t seed;
    LFSR     lfsr;
    uint8_t  tiles[mapWidth*mapHeight];

    int8_t getTile(int16_t x, int16_t y);
    int8_t tileType(int8_t tile);
    int8_t calcTile(int16_t playerX, int16_t playerY);
    void drawTile(const unsigned char *sprites, uint8_t tile, uint8_t sx, uint8_t sy, uint8_t tx, uint8_t ty, uint8_t mx, uint8_t my);
};
    

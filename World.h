#pragma once
#include <Arduboy2.h>
#include "lfsr.h"

class World {
  public:
    static const uint16_t mapWidth = 256; 
    static const uint16_t mapHeight = 256;
    static const uint8_t tileTypes = 16;

    static const uint8_t mainLeft = 0;
    static const uint8_t mainRight = 80;
    static const uint8_t mainTop = 0;
    static const uint8_t mainBottom = HEIGHT;
    
    static const uint8_t miniLeft = mainRight;
    static const uint8_t miniRight = WIDTH;
    static const uint8_t miniTop = 0;
    static const uint8_t miniBottom = HEIGHT;

    static const uint32_t minSeed = 1;
    static const uint32_t maxSeed = (1ul<<20)-1;

    uint32_t seed;
        
    void init(uint32_t seed, int32_t x, int32_t y);    
    void draw(int16_t x, int16_t y);
    void drawMini(int32_t x, int32_t y);
    
  private:
    LFSR     lfsr;
    int16_t  lfsrX;
    int16_t  lfsrY;

    int8_t getTile(int16_t x, int16_t y);
    int8_t peekTile(int16_t x, int16_t y);
    int8_t tileType(int8_t tile);
    int8_t calcTile(int16_t playerX, int16_t playerY);
    void drawTile(const unsigned char *sprites, uint8_t tile, uint8_t sx, uint8_t sy, uint8_t tx, uint8_t ty, uint8_t mx, uint8_t my);
};
    

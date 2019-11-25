#include "World.h"
#include "SavedSprites.h"

extern Arduboy2 arduboy;

void World::init(uint32_t newSeed) {
  seed = newSeed;
  lfsr.lfsr = seed;

  Serial.print("min = ");
  Serial.println(minSeed,HEX);
  Serial.print("max = ");
  Serial.println(maxSeed,HEX);
  Serial.print("SEED = ");
  Serial.println(seed,HEX);
  
  for (int8_t y=0; y < mapHeight; y++) {
    Serial.print(y);
    Serial.print(":");
    for (int8_t x=0; x < mapWidth; x++) {
      uint8_t tile = 4 + (lfsr.lfsr & 0xf);
      tiles[y*mapWidth+x] = tile;
      Serial.print(tile&0x3);
      lfsr.forward4();
    }
    Serial.println();
  }
}

int8_t World::getTile(int16_t x, int16_t y) {

  if (
    (y < 0) || (y >= mapHeight) ||
    (x < 0) || (x >= mapWidth)) {
      return -1;
  }
  return tiles[y*mapWidth+x];
}

int8_t World::tileType(int8_t tile) {
  if (tile<0) return tile;
  return tile>>2;
}

int8_t World::calcTile(int16_t playerX, int16_t playerY) {
  int8_t x = playerX >> 3;
  int8_t y = playerY >> 3;
  int8_t tile = getTile(x,y);
  if (tile < 0) return tile;
  int8_t fullTile = tilesMiniMapFull + (tile&0x3);
  switch(tileType(tile)) {
    case tilesMiniMapNoNorth: return (tileType(getTile(x,y-1)) == tilesMiniMapNoSouth) ? tile : fullTile;
    case tilesMiniMapNoEast:  return (tileType(getTile(x+1,y)) == tilesMiniMapNoWest)  ? tile : fullTile;
    case tilesMiniMapNoSouth: return (tileType(getTile(x,y+1)) == tilesMiniMapNoNorth) ? tile : fullTile;
    case tilesMiniMapNoWest:  return (tileType(getTile(x-1,y)) == tilesMiniMapNoEast)  ? tile : fullTile;
    default: return tile;
  }
}
/* 
 * The player is always centered on the map, so the x,y are the player world coordinates.
 * Coordinates uses lower 3 bits for offset and the rest for which tile. 
 */
void World::drawMini(int16_t playerX, int16_t playerY) {
  uint8_t offsetX = playerX & 0x7;
  uint8_t offsetY = playerY & 0x7;
  int16_t tileX = playerX - (miniRight-miniLeft)/2;
  int16_t tileY = playerY - (miniBottom-miniTop)/2;

  uint8_t ty = offsetY;
  for (uint8_t y=miniTop; y < miniBottom; y += (y == miniTop) ? 8-offsetY : 8) {
    uint8_t tx = offsetX;
    for (uint8_t x=miniLeft; x < miniRight; x += (x == miniLeft) ? 8-offsetX : 8) {
      int8_t tile = calcTile(tileX+x-miniLeft,tileY+y-miniTop);
      tile = (tile < 0) ? tilesMiniMapVoid : tile;
      drawTile(tilesMiniMap,tile,x,y,tx,ty,miniRight,miniBottom);
      tx=0;
    }
    ty=0;
  }
}

/*
 * Draws an 8x8 tile:
 *  sx,sy - where to start on the screen
 *  tx,ty - where to start within a tile
 *  mx,my - max x,y.  Only change pixels less than these values.
 *  Note, 'my' must be a multiple of 8
 */
void World::drawTile(const unsigned char *sprites, uint8_t tile, uint8_t sx, uint8_t sy, uint8_t tx, uint8_t ty, uint8_t mx, uint8_t my) {
  int16_t tileOffset = 2+(tile*8)+tx;
  uint16_t sp = (sy/8)*WIDTH + sx;
  uint8_t offsetY = sy % 8;
  uint8_t mask1 = 0xff << offsetY;
  uint8_t mask2 = 0xff << (offsetY-ty);
  for (uint8_t x=sx; x < min(sx+8-tx,mx); x++) {
    uint8_t tileData = pgm_read_byte(sprites + tileOffset) >> ty;
    arduboy.sBuffer[sp] = (arduboy.sBuffer[sp] & ~mask1) | ((tileData << offsetY) & mask1);
    if ((offsetY + 8 - ty > 8) && (sy+8 < my)) {
      arduboy.sBuffer[sp+WIDTH] = (arduboy.sBuffer[sp+WIDTH] & mask2) | ((tileData >> (8-offsetY)) & ~mask2);      
    }
    sp++;
    tileOffset++;
  }
}

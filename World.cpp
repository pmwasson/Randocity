#include "World.h"
#include "SavedSprites.h"

extern Arduboy2 arduboy;

void World::init(uint32_t newSeed) {
  seed = newSeed;
  lfsr.lfsr = seed;
  lfsrX=0;
  lfsrY=0;
  Serial.print("SEED = ");
  Serial.println(seed,HEX);
}

int8_t World::getBlock(int16_t x, int16_t y) {

  if (
    (y < 0) || (y >= mapHeight) ||
    (x < 0) || (x >= mapWidth)) {
      return -1;
  }

  // Move LFSR to correct position
  while(lfsrX < x) {
    lfsr.forward(4);
    lfsrX++;
  }
  while(lfsrX > x) {
    lfsr.backward(4);
    lfsrX--;
  }
  while(lfsrY < y) {
    lfsr.forward1024();
    lfsrY++;
  }
  while(lfsrY > y) {
    lfsr.backward1024();
    lfsrY--;
  }
  
  return lfsr.lfsr & 0xf;
}

int8_t World::peekBlock(int16_t x, int16_t y) {
  uint32_t savedLfsr = lfsr.lfsr;
  int16_t savedLfsrX = lfsrX;
  int16_t savedLfsrY = lfsrY;

  int8_t block = getBlock(x,y);

  lfsr.lfsr = savedLfsr;
  lfsrX = savedLfsrX;
  lfsrY = savedLfsrY;
  
  return block;
}

int8_t World::blockType(int8_t block) {
  if (block<0) return block;
  return block>>2;
}

int8_t World::calcBlock(int16_t x, int16_t y) {
  int8_t block = getBlock(x,y);
  if (block < 0) return block;
  int8_t fullBlock = tilesMiniMapFull + (block&0x3);
  switch(blockType(block)) {
    case blockNoNorth: return (blockType(peekBlock(x,y-1)) == blockNoSouth) ? block : fullBlock;
    case blockNoEast:  return (blockType(peekBlock(x+1,y)) == blockNoWest)  ? block : fullBlock;
    case blockNoSouth: return (blockType(peekBlock(x,y+1)) == blockNoNorth) ? block : fullBlock;
    case blockNoWest:  return (blockType(peekBlock(x-1,y)) == blockNoEast)  ? block : fullBlock;
    default: return block;
  }
}
/* 
 * The player is always centered on the map, so the x,y are the player world coordinates.
 * Coordinates uses lower 3 bits for offset and the rest for which block. 
 */
void World::drawMini(int32_t playerX, int32_t playerY) {
  uint8_t offsetX = playerX & 0x7;
  uint8_t offsetY = playerY & 0x7;
  int16_t tileX = playerX - (miniRight-miniLeft)/2;
  int16_t tileY = playerY - (miniBottom-miniTop)/2;

  uint8_t ty = offsetY;
  for (uint8_t y=miniTop; y < miniBottom; y += (y == miniTop) ? 8-offsetY : 8) {
    
    // set LFSR save point
    calcBlock(tileX>>3,(tileY+y-miniTop)>>3);

    // Save LFSR for next row
    uint32_t savedLfsr = lfsr.lfsr;
    int16_t savedLfsrX = lfsrX;
    int16_t savedLfsrY = lfsrY;

    uint8_t tx = offsetX;
    for (uint8_t x=miniLeft; x < miniRight; x += (x == miniLeft) ? 8-offsetX : 8) {
      int8_t block = calcBlock((tileX+x-tx-miniLeft)>>3,(tileY+y-ty-miniTop)>>3);
      block = (block < 0) ? tilesMiniMapVoid : block;
      drawTile(tilesMiniMap,block,x,y,tx,ty,miniRight,miniBottom);
      tx=0;
    }
    ty=0;

    // Restore LFSR
    lfsr.lfsr = savedLfsr;
    lfsrX = savedLfsrX;
    lfsrY = savedLfsrY;
  }
}

void World::draw(int32_t playerX, int32_t playerY) {
  uint8_t offsetX = playerX & 0x7;
  uint8_t offsetY = playerY & 0x7;
  int16_t blockX = playerX >> 9;
  int16_t blockY = playerY >> 9;
  
  // Get tile (upper-left)
  int8_t block = calcBlock(blockX,blockY);

  // Since corners have no roads, only need 1 other block for transition
  // If within 8, choose that direction
  int8_t otherBlockX = calcBlock(blockX+1,blockY);
  int8_t otherBlockY = calcBlock(blockX,blockY+1);

  uint8_t segments = pgm_read_byte(blockSegments + block);
  uint8_t otherSegmentsH = pgm_read_byte(blockSegments + otherBlockX);
  uint8_t otherSegmentsV = pgm_read_byte(blockSegments + otherBlockY);
  uint8_t firstY = 0x3f&((playerY-offsetY)>>3);
  uint8_t firstX = 0x3f&((playerX-offsetX)>>3);
  
  uint8_t ty = offsetY;  
  for (uint8_t y=mainTop; y < mainBottom; y += (y == mainTop) ? 8 - offsetY : 8) {
    uint8_t tx = offsetX;
    uint8_t lookupY = 0x3f&((playerY+y-ty-mainTop)>>3);
    uint8_t segmentsY = (lookupY < firstY) ? otherSegmentsV : segments;
    
    for (uint8_t x=mainLeft; x < mainRight; x += (x == mainLeft) ? 8 - offsetX : 8) {
      uint8_t lookupX = 0x3f&((playerX+x-tx-mainLeft)>>3);
      uint8_t segmentsX = (lookupX < firstX) ? otherSegmentsH : segmentsY;
      int8_t tile = tileInBlock(segmentsX,lookupX,lookupY);
      drawTile(tilesRoad,tile,x,y,tx,ty,mainRight,mainBottom);
      tx=0;
    }
    ty=0;
  }
}

int8_t World::tileAt(int32_t playerX, int32_t playerY) {
  int16_t blockX = playerX >> 9;
  int16_t blockY = playerY >> 9;
  int8_t  block = calcBlock(blockX,blockY);
  uint8_t segments = pgm_read_byte(blockSegments + block);
  uint8_t lookupY = 0x3f&((playerY+4)>>3);
  uint8_t lookupX = 0x3f&((playerX+4)>>3);
  return tileInBlock(segments,lookupX,lookupY);
}

int8_t World::tileInBlock(uint8_t segments, int16_t tileX, int16_t tileY) {
  int8_t tileH  = tilesRoadGravel;
  if ( (((segments & blockSegmentNorth) != 0) && (tileY < 32) ||
       (((segments & blockSegmentSouth) != 0) && (tileY > 31) )) &&
       (tileX > 28) && (tileX < 35)) {
      tileH = (((tileX==31) && (tileY%2)) || (tileX==34)) ? tilesRoadStripeEast :
              (((tileX==32) && (tileY%2)) || (tileX==29)) ? tilesRoadStripeWest :
              tilesRoadBlackTop;
  }
  int8_t tile = tileH;

  int8_t tileV  = tilesRoadGravel;
  if ( (((segments & blockSegmentWest) != 0) && (tileX < 32) ||
       (((segments & blockSegmentEast) != 0) && (tileX > 31) )) &&
       (tileY > 28) && (tileY < 35)) {
      tileV = (((tileY==31) && (tileX%2)) || (tileY==34)) ? tilesRoadStripeSouth :
              (((tileY==32) && (tileX%2)) || (tileY==29)) ? tilesRoadStripeNorth :
              tilesRoadBlackTop;
  }
  tile = mergeTile(tile,tileV);

  int8_t tileD1 = tilesRoadGravel;
  int16_t tileXmY = tileX - tileY;
  if ( (((segments & blockSegmentNorthEast) != 0) && ( tileXmY > 27) && ( tileXmY < 37)) ||  
       (((segments & blockSegmentSouthWest) != 0) && (-tileXmY > 27) && (-tileXmY < 37))) {
      tileD1 =((abs(tileXmY)==32) && (tileY%2)) ? tilesRoadStripeNW2SE 
             :((tileXmY==28) || (tileXmY==-36)) ? tilesRoadEdgeSW
             :((tileXmY==36) || (tileXmY==-28)) ? tilesRoadEdgeNE
             :                                    tilesRoadBlackTop;
  }
  tile = mergeTile(tile,tileD1);
  
  int8_t tileD2 = tilesRoadGravel;
  int16_t tileXpY = 64 - (tileX + tileY);
  if ( (((segments & blockSegmentNorthWest) != 0) && ( tileXpY > 27) && ( tileXpY < 37)) ||  
       (((segments & blockSegmentSouthEast) != 0) && (-tileXpY > 27) && (-tileXpY < 37))) {
      tileD2 =((abs(tileXpY)==32) && (tileY%2)) ? tilesRoadStripeNE2SW 
             :((tileXpY==28) || (tileXpY==-36)) ? tilesRoadEdgeSE
             :((tileXpY==36) || (tileXpY==-28)) ? tilesRoadEdgeNW
             :                                    tilesRoadBlackTop;
  }
  tile = mergeTile(tile,tileD2);

  return tile;
}

int8_t World::mergeTile(int8_t tile1, int8_t tile2) {
  if (tile1 == tilesRoadGravel) return tile2;
  if (tile2 == tilesRoadGravel) return tile1;
  if (tile1 == tilesRoadBlackTop) return tile1;
  if (tile2 == tilesRoadBlackTop) return tile2;
  // conflict
  return tilesRoadBlackTop;
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

// Light-cycle (overhead)
const unsigned char PROGMEM tilesCycle[] = {
16,16,

// Vertical
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xFC,0xC0,0xFF,0xDE,0xFF,0xDE,0xFF,0xC0,0xFF,0xF8,0xFC,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x3F,0x03,0xFF,0x73,0xFF,0x73,0xFF,0x03,0xFF,0x1F,0x3F,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xFC,0xC0,0xFF,0xDA,0xFF,0xDA,0xFF,0xC0,0xFF,0xF8,0xFC,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x3F,0x03,0xFF,0x5B,0xFF,0x5B,0xFF,0x03,0xFF,0x1F,0x3F,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xFC,0xC0,0xFF,0xCE,0xFF,0xCE,0xFF,0xC0,0xFF,0xF8,0xFC,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x3F,0x03,0xFF,0x7B,0xFF,0x7B,0xFF,0x03,0xFF,0x1F,0x3F,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

// Horizontal
0x00,0xC0,0x80,0xC0,0x80,0xF0,0xA0,0xF0,0xA0,0xF0,0x20,0xF0,0xE0,0xF0,0xE0,0xF0,0xE0,0xF0,0xE0,0xF0,0x20,0xF0,0x20,0xF0,0xA0,0xF0,0x80,0xF0,0x80,0xC0,0x00,0xC0,0x00,0x03,0x01,0x03,0x01,0x0F,0x05,0x0F,0x05,0x0F,0x04,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x04,0x0F,0x04,0x0F,0x05,0x0F,0x01,0x0F,0x01,0x03,0x00,0x03,
0x00,0xC0,0x80,0xC0,0x00,0xF0,0xA0,0xF0,0xA0,0xF0,0x20,0xF0,0xE0,0xF0,0xE0,0xF0,0xE0,0xF0,0xE0,0xF0,0x20,0xF0,0xA0,0xF0,0xA0,0xF0,0x00,0xF0,0x80,0xC0,0x00,0xC0,0x00,0x03,0x01,0x03,0x00,0x0F,0x05,0x0F,0x05,0x0F,0x04,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x04,0x0F,0x05,0x0F,0x05,0x0F,0x00,0x0F,0x01,0x03,0x00,0x03,
0x00,0xC0,0x80,0xC0,0x80,0xF0,0xA0,0xF0,0x20,0xF0,0x20,0xF0,0xE0,0xF0,0xE0,0xF0,0xE0,0xF0,0xE0,0xF0,0x20,0xF0,0xA0,0xF0,0xA0,0xF0,0x80,0xF0,0x80,0xC0,0x00,0xC0,0x00,0x03,0x01,0x03,0x01,0x0F,0x05,0x0F,0x04,0x0F,0x04,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x07,0x0F,0x04,0x0F,0x05,0x0F,0x05,0x0F,0x01,0x0F,0x01,0x03,0x00,0x03,

// Diagonal (SW/NE)
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,0xE8,0xFC,0xC4,0xFE,0xB0,0xFE,0x38,0xFE,0x90,0xFE,0x44,0xFE,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x7E,0x32,0x7F,0x39,0x7F,0x1C,0x7F,0x0D,0x7F,0x23,0x7F,0x17,0x3F,0x0F,0x1F,0x07,0x0F,0x03,0x07,0x01,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,0xE8,0xFC,0xC4,0xFE,0xA0,0xFE,0x08,0xFE,0x9C,0xFE,0x4C,0xFE,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x7E,0x32,0x7F,0x39,0x7F,0x10,0x7F,0x05,0x7F,0x23,0x7F,0x17,0x3F,0x0F,0x1F,0x07,0x0F,0x03,0x07,0x01,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF0,0xF8,0xE8,0xFC,0xC4,0xFE,0xB0,0xFE,0x38,0xFE,0x9C,0xFE,0x4C,0xFE,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x7F,0x09,0x7F,0x1C,0x7F,0x0D,0x7F,0x23,0x7F,0x17,0x3F,0x0F,0x1F,0x07,0x0F,0x03,0x07,0x01,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,

// Diagonal (SE/NW)
0x00,0x00,0x00,0x7E,0x44,0xFE,0x90,0xFE,0x38,0xFE,0xB0,0xFE,0xC4,0xFE,0xE8,0xFC,0xF0,0xF8,0xE0,0xF0,0xC0,0xE0,0x80,0xC0,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x17,0x3F,0x23,0x7F,0x0D,0x7F,0x1C,0x7F,0x39,0x7F,0x32,0x7F,0x00,0x7E,0x00,0x00,
0x00,0x00,0x00,0x7E,0x4C,0xFE,0x9C,0xFE,0x08,0xFE,0xA0,0xFE,0xC4,0xFE,0xE8,0xFC,0xF0,0xF8,0xE0,0xF0,0xC0,0xE0,0x80,0xC0,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x17,0x3F,0x23,0x7F,0x05,0x7F,0x10,0x7F,0x39,0x7F,0x32,0x7F,0x00,0x7E,0x00,0x00,
0x00,0x00,0x00,0x7E,0x4C,0xFE,0x9C,0xFE,0x38,0xFE,0xB0,0xFE,0xC4,0xFE,0xE8,0xFC,0xF0,0xF8,0xE0,0xF0,0xC0,0xE0,0x80,0xC0,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x17,0x3F,0x23,0x7F,0x0D,0x7F,0x1C,0x7F,0x09,0x7F,0x22,0x7F,0x00,0x7E,0x00,0x00,

};

// Road tiles

static const uint8_t tilesRoadGravel      = 0;
static const uint8_t tilesRoadBlackTop    = 1;
static const uint8_t tilesRoadStripeNorth = 2;
static const uint8_t tilesRoadStripeEast  = 3;
static const uint8_t tilesRoadStripeSouth = 4;
static const uint8_t tilesRoadStripeWest  = 5;
static const uint8_t tilesRoadStripeNW2SE = 6;
static const uint8_t tilesRoadStripeNE2SW = 7;
static const uint8_t tilesRoadEdgeNE      = 8;
static const uint8_t tilesRoadEdgeSE      = 9;
static const uint8_t tilesRoadEdgeSW      = 10;
static const uint8_t tilesRoadEdgeNW      = 11;
static const uint8_t tilesRoadDirt        = 12;

const unsigned char PROGMEM tilesRoad[] = {
8,8,
0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA, // 0  Gravel
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    Black top
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, //    Stripe - North
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF, //    Stripe - East
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80, //    Stripe - South
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    Stripe - West
0x00,0x06,0x0E,0x1C,0x38,0x70,0x60,0x00, //    Stripe - NW2SE 
0x00,0x60,0x70,0x38,0x1C,0x0E,0x06,0x00, //    Stripe - NE2SW
0x01,0x02,0x05,0x0A,0x15,0x2A,0x55,0xAA, //    Edge - NE 
0x80,0xC0,0x60,0xB0,0x58,0xAC,0x56,0xAB, //    Edge - SE
0x55,0xAA,0x54,0xA8,0x50,0xA0,0x40,0x80, //    Edge - SW 
0xD5,0x6A,0x35,0x1A,0x0D,0x06,0x03,0x01, //    Edge - NW
0x55,0x00,0xAA,0x00,0x55,0x00,0xAA,0x00, //    Dirt
};
// mini-map

static const uint8_t tilesMiniMapFull = 16;
static const uint8_t tilesMiniMapVoid = 24;

static const uint8_t blockNoNorth = 0;
static const uint8_t blockNoEast  = 1;
static const uint8_t blockNoSouth = 2;
static const uint8_t blockNoWest  = 3;

// City edge cases
static const uint8_t tilesMiniMapCrossNoNorth = 0*4+1;
static const uint8_t tilesMiniMapCrossNoEast  = 1*4+1;
static const uint8_t tilesMiniMapCrossNoSouth = 2*4+1;
static const uint8_t tilesMiniMapCrossNoWest  = 3*4+1;
static const uint8_t tilesMiniMapCrossNoNE    = 20;
static const uint8_t tilesMiniMapCrossNoSE    = 21;
static const uint8_t tilesMiniMapCrossNoSW    = 22;
static const uint8_t tilesMiniMapCrossNoNW    = 23;

const unsigned char PROGMEM tilesMiniMap[] = {
8,8,
// no north
0x38, 0x70, 0xE0, 0xC0, 0xC0, 0xE0, 0x70, 0x38, 
0x18, 0x18, 0x18, 0xF8, 0xF8, 0x18, 0x18, 0x18, 
0x38, 0x78, 0xF8, 0xD8, 0x98, 0x18, 0x18, 0x18, 
0x18, 0x18, 0x18, 0x98, 0xD8, 0xF8, 0x78, 0x38,
// no east
0x3C, 0x7E, 0xE7, 0xC3, 0x81, 0x00, 0x00, 0x00, 
0x18, 0x18, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
0x38, 0x70, 0xE0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
0x1C, 0x0E, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 
// no south
0x1C, 0x0E, 0x07, 0x03, 0x03, 0x07, 0x0E, 0x1C, 
0x18, 0x18, 0x18, 0x1F, 0x1F, 0x18, 0x18, 0x18, 
0x18, 0x18, 0x18, 0x19, 0x1B, 0x1F, 0x1E, 0x1C, 
0x1C, 0x1E, 0x1F, 0x1B, 0x19, 0x18, 0x18, 0x18, 
// no west
0x00, 0x00, 0x00, 0x81, 0xC3, 0xE7, 0x7E, 0x3C, 
0x00, 0x00, 0x00, 0xFF, 0xFF, 0x18, 0x18, 0x18, 
0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x0E, 0x1C, 
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xE0, 0x70, 0x38, 
// fully connected (diamond, cross, backward-slash, forward-slash)
0x3C, 0x7E, 0xE7, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C, 
0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18, 
0x38, 0x70, 0xE0, 0xC1, 0x83, 0x07, 0x0E, 0x1C, 
0x1C, 0x0E, 0x07, 0x83, 0xC1, 0xE0, 0x70, 0x38,
// Edge - corners (NE,SE,SW,NW)
0x38, 0x70, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 
0x1C, 0x0E, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0E, 0x1C, 
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x38,
// Void
0x55, 0x00, 0xAA, 0x00, 0x55, 0x00, 0xAA, 0x00,
};

// Segments:
// 
//           7/|\4   
//           / 0 \   
//          *-3+1-*   
//           \ 2 /    
//           6\|/5   
//

static const uint8_t blockSegmentNorth      = 0b00000001;  
static const uint8_t blockSegmentEast       = 0b00000010;
static const uint8_t blockSegmentSouth      = 0b00000100;
static const uint8_t blockSegmentWest       = 0b00001000;
static const uint8_t blockSegmentNorthEast  = 0b00010000;
static const uint8_t blockSegmentSouthEast  = 0b00100000;
static const uint8_t blockSegmentSouthWest  = 0b01000000;  
static const uint8_t blockSegmentNorthWest  = 0b10000000;

const unsigned char PROGMEM blockSegments[] = {
  0b01100000, // diamond (no north)
  0b00001110, // cross (no north)
  0b01001010, // backward-slash (no north)
  0b00101010, // forward-slash (no north)

  0b11000000, // diamond (no east)
  0b00001101, // cross (no east)
  0b01000101, // backward-slash (no east)
  0b10000101, // forward-slash (no east)

  0b10010000, // diamond (no south)
  0b00001011, // cross (no south)
  0b00011010, // backward-slash (no south)
  0b10001010, // forward-slash (no south)

  0b00110000, // diamond (no west)
  0b00000111, // cross (no west)
  0b00010101, // backward-slash (no west)
  0b00100101, // forward-slash (no west)
  
  0b11110000, // diamond
  0b00001111, // cross
  0b01010000, // backward-slash
  0b10100000, // forward-slash

  0b01000000, // Void-NE
  0b10000000, // Void-SE
  0b00010000, // Void-SW
  0b00100000, // Void-NW

  0b00000000, // Void
};

const unsigned char PROGMEM tilesBullseye[] = {
8,8,
0x3C,0x3C,0x42,0x42,0x81,0xBD,0x99,0xBD,0x99,0xBD,0x81,0xBD,0x42,0x42,0x3C,0x3C
};

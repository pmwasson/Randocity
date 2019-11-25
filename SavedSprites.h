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

static const uint8_t tilesRoadSpeed = 17;

const unsigned char PROGMEM tilesRoad[] = {
8,8,
0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA, // 0  Off road
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //    Black top
0xD5,0x6A,0x35,0x1A,0x0D,0x06,0x03,0x01, //    Edge - NW
0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA, //    Off road
0x57,0xAE,0x5C,0xB8,0x70,0xE0,0xC0,0x80, // 4  Edge - SW
0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAB, //    Edge - SW (fill-in)
0x80,0xC0,0x60,0xB0,0x58,0xAC,0x56,0xAB, //    Edge - SE
0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA, //    Off road
0x01,0x03,0x07,0x0E,0x1D,0x3A,0x75,0xEA, // 8  Edge - NE
0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA, //    Off road
0x55,0xAA,0x55,0xFF,0xFF,0x00,0x00,0x00, //    Edge - W
0x00,0x00,0x00,0xFF,0xFF,0xAA,0x55,0xAA, //    Edge - E
0x1D,0x1A,0x1D,0x1A,0x1D,0x1A,0x1D,0x1A, // 12 Edge - N
0x58,0xB8,0x58,0xB8,0x58,0xB8,0x58,0xB8, //    Edge - S
0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00, //    Stripe - East
0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00, //    Stripe - West
0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06, // 16 Stripe - North
0x7E,0x91,0xA1,0xC1,0xC1,0x81,0x81,0x7E,  // Speeddometer 1
0x7E,0x89,0xB1,0xC1,0xC1,0x81,0x81,0x7E,  //              2
0x7E,0x81,0x8D,0xF1,0xC1,0x81,0x81,0x7E,  //              3
0x7E,0x81,0x81,0xFD,0xC1,0x81,0x81,0x7E,  //              4
0x7E,0x81,0x81,0xC1,0xFD,0x81,0x81,0x7E,  //              5
0x7E,0x81,0x81,0xC1,0xF1,0x8D,0x81,0x7E,  //              6
0x7E,0x81,0x81,0xC1,0xC1,0xB1,0x89,0x7E,  //              7
0x7E,0x81,0x81,0xC1,0xC1,0xA1,0x91,0x7E,  //              8
};
// mini-map

static const uint8_t tilesMiniMapFull = 16;
static const uint8_t tilesMiniMapVoid = 20;

static const uint8_t tilesMiniMapNoNorth = 0;
static const uint8_t tilesMiniMapNoEast = 1;
static const uint8_t tilesMiniMapNoSouth = 2;
static const uint8_t tilesMiniMapNoWest = 3;

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
// fully connected
0x3C, 0x7E, 0xE7, 0xC3, 0xC3, 0xE7, 0x7E, 0x3C, 
0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18, 
0x38, 0x70, 0xE0, 0xC1, 0x83, 0x07, 0x0E, 0x1C, 
0x1C, 0x0E, 0x07, 0x83, 0xC1, 0xE0, 0x70, 0x38, 
// Void
0x55, 0x00, 0xAA, 0x00, 0x55, 0x00, 0xAA, 0x00,
};

const unsigned char PROGMEM tilesBullseye[] = {
8,8,
0x3C,0x3C,0x42,0x42,0x81,0xBD,0x99,0xBD,0x99,0xBD,0x81,0xBD,0x42,0x42,0x3C,0x3C
};

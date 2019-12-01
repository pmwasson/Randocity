#include <Arduboy2.h>
#include <Sprites.h>
#include <ArduboyTones.h>
#include "FatFont.h"
#include "World.h"
#include "SavedSprites.h"

Arduboy2 arduboy;
Sprites  sprites;
ArduboyTones sound(arduboy.audio.enabled);
FatFont font;
World world;

// Player coordinates (19 bits each)
// Bits Range   Unit      Usage
// ---- ------- --------- ---------------------------
// 8    [18:11] Blocks    Within 256x256 map (blocks)
// 6    [10:5]  Tiles     Within 64x64 block (tiles)
// 3    [4:2]   Pixels    Within 8x8 tile (pixel)
// 2    [1:0]   Sub-pixel Within pixel

enum Direction : uint8_t {north, northeast, east, southeast, south, southwest, west, northwest};
static const uint8_t targetMidH  = (world.mainRight+world.mainLeft-16)/2;
static const uint8_t targetMidV  = (world.mainTop+world.mainBottom-16)/2;
static const uint8_t targetRight = targetMidH + 28;
static const uint8_t targetLeft = targetMidH - 28;
static const uint8_t targetDown = targetMidV + 20;
static const uint8_t targetUp = targetMidV - 20;


static const uint16_t colorBG = 0x5a5a;
static const uint8_t  colorFG = WHITE;

Direction playerDirection = north;
uint8_t frame = 0;
int32_t playerX = ((int32_t)world.mapWidth/2l)<<11;
int32_t playerY = (((int32_t)world.mapHeight/2l)<<11) - (32l<<5);
int32_t savePlayerX;
int32_t savePlayerY;
int8_t  playerSpeed = 0;
static const int8_t maxSpeed = 20;
uint8_t offsetX = targetMidH;
uint8_t offsetY = targetMidV;
uint8_t targetX = offsetX;
uint8_t targetY = offsetY;

enum Mode : uint8_t {title, main, menu, viewMap, help, enterSeed, displayMessage};
Mode mode = title;

int8_t menuItem = 0;
static const int8_t menuMaxItem = 5; 
uint32_t seedNew;
uint32_t seedRandom;
uint8_t helpPage;
static const int8_t helpPageMax = 5;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  Serial.begin(9600);

  generateWorld();
}

void loop() {
  switch(mode) {
    case main: 
      mainLoop();
      return;
    case menu:
      menuLoop();
      return;
    case viewMap:
      mapLoop();
      return;
    case enterSeed:
      seedLoop();
      return;
    case help:
      helpLoop();
      return;
  }
  titleLoop();
  return;    
}

void generateWorld() {
  uint32_t seed = random(world.minSeed,world.maxSeed);
//  arduboy.clear();
//  font.setCursor(0,0);
//  font.print(F("GENERATING\n  WORLD...\n\nSEED: "));
//  printSeed(seed);
//  arduboy.display();
//  
//  delay(500);
  world.init(seed);
}

void initPlayer() {
  playerDirection = north;
  playerX = ((int32_t)world.mapWidth/2l)<<11;
  playerY = (((int32_t)world.mapHeight/2l)<<11) - (32l<<5);
}

void printSeed(uint32_t seed) {
  uint32_t seedCopy = seed|1l;
  while(seedCopy < world.maxSeed/16) {
    font.print(F("0"));
    seedCopy *= 16;
  }
  font.print(seed,HEX);
}

void titleLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0x0101);

  font.setCursor(0,3);
  font.println(F("  LINEAR FEEDBACK  "));
  font.println(F("       CITY        "));
  font.println();
  font.println(F("  BY PAUL WASSON   ")); 
  font.println(F("  DECEMBER, 2019   "));
  font.println();  
  font.println(F("  PRESS _ FOR MENU "));

  arduboy.display();

  if (arduboy.justPressed(B_BUTTON)) {
    mode = menu;
  }
}

void menuLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0);

  font.setCursor(0,0);
  font.print(F("MENU:\n  FREE ROAM\n  RACE TO THE EDGE\n  CRAZY CURIER\n  VIEW MAP\n  HELP\n\nPRESS _ TO SELECT"));
  font.setCursor(0,(menuItem+1)*8);
  font.print(F("]"));
  arduboy.display();

  if (arduboy.justPressed(UP_BUTTON)) {
    if (--menuItem < 0) {
      menuItem = menuMaxItem-1;
    }
  }
  
  if (arduboy.justPressed(DOWN_BUTTON)) {
    if (++menuItem >= menuMaxItem) {
      menuItem = 0;
    }
  }
  if (arduboy.justPressed(B_BUTTON)) {
    switch(menuItem) {
      case 0:
      case 1:
      case 2:
        arduboy.clear();
        font.setCursor(0,24);
        font.print(F("  PRESS \\ AND @\n  FOR MENU"));
        arduboy.display();
        delay(3000);
        mode = main;
        break;
      case 3:
        savePlayerX = playerX;
        savePlayerY = playerY;
        world.miniLeft   = 0;
        world.miniRight  = WIDTH;
        world.miniTop    = 8;
        world.miniBottom = HEIGHT-8;
        mode = viewMap;
        break;
      default:
        helpPage = 1;
        mode = help;
        break;
    }
  }
}

void mapLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0);

  world.drawMini(playerX>>8,playerY>>8);
  arduboy.drawRect(world.miniLeft,world.miniTop,world.miniRight-world.miniLeft,world.miniBottom-world.miniTop);

  font.setCursor(0,0);
  font.print(F("SEED:"));
  printSeed(world.seed);
  font.print(F(" "));
  font.print((playerX+(1l<<10)) >> 11);
  font.print(F(","));
  font.print((playerY+(1l<<10)) >> 11);
  
  font.setCursor(0,HEIGHT-7);
  font.print(F("@ MENU, _ NEW SEED"));
  
  if (arduboy.frameCount % 16 < 8) {
    sprites.drawPlusMask(
      (world.miniRight+world.miniLeft-8)/2,
      (world.miniBottom+world.miniTop-8)/2,
      tilesBullseye,1);
  } 

  arduboy.display();

  if (arduboy.pressed(LEFT_BUTTON))  playerX-=512;
  if (arduboy.pressed(RIGHT_BUTTON)) playerX+=512;
  if (arduboy.pressed(UP_BUTTON))    playerY-=512;
  if (arduboy.pressed(DOWN_BUTTON))  playerY+=512;
  
  if (arduboy.justPressed(B_BUTTON)) {
      seedNew = world.seed;
      seedRandom = random(world.minSeed,world.maxSeed);
      menuItem = 0;
      mode = enterSeed;
  }
  if (arduboy.justPressed(A_BUTTON)) {
      playerX = savePlayerX;
      playerY = savePlayerY;
      world.miniLeft   = world.mainRight;
      world.miniRight  = WIDTH;
      world.miniTop    = world.mainTop;
      world.miniBottom = world.mainBottom;
      mode = menu;
  }
}

void seedLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0);

  font.setCursor(0,0);
  font.print(F("SEED:"));
  printSeed(world.seed);
  font.print(F("\n\n  RANDOM: "));
  printSeed(seedRandom);
  font.print(F("\n  ENTER:  "));
  printSeed(seedNew);
  font.print(F("\n\n\n@ RETURN, _ SELECT"));
  
  if (menuItem ==0) {
    font.setCursor(0,(0+2)*8);
    font.print(F("]"));
    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON)) {
      menuItem = 1;
    }
  }
  else {
    font.setCursor(0,(1+2)*8);
    font.print(F("]"));    
    font.setCursor((10+menuItem-1)*7,32);
    font.print(F("^"));    

    int8_t digit = 4*(5-menuItem);
    uint32_t mask = (0xfl << digit);
    if (arduboy.justPressed(UP_BUTTON)) {
      seedNew = (seedNew + (1l << digit) & mask) + (seedNew & ~mask);
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
      seedNew = (seedNew - (1l << digit) & mask) + (seedNew & ~mask);
    }
    if (arduboy.justPressed(LEFT_BUTTON)) {
      menuItem--;
    }
    if (arduboy.justPressed(RIGHT_BUTTON)) {
      menuItem++;
      if (menuItem > 5) menuItem = 5;
    }
  }

  if (arduboy.justPressed(B_BUTTON)) {
    if (menuItem == 0) {
      world.init(seedRandom);
      seedRandom = random(world.minSeed,world.maxSeed);
    }
    else {
      world.init(seedNew);      
    }
  }
  
  if (arduboy.justPressed(A_BUTTON)) {
    menuItem = 3; // VIEW MAP
    mode = viewMap;
  }

  arduboy.display();
}

void helpLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0);

  font.setCursor(3,0);
  font.print(F("HELP PAGE "));
  font.print(helpPage);
  font.print(F("/"));
  font.print(helpPageMax);
  arduboy.drawRect(0,8,WIDTH-1,HEIGHT-17);

  font.setCursor(3,10);
  switch(helpPage) {
    case(1): 
    font.print(F("MOVEMENT:\n [ ] TURN\n   _ ACCELERATE\n @   BRAKE\n \\+_ MENU"));
    break;
    case(2): 
    font.print(F("IF YOU GO OFF\nROAD, PRESS _\nREPEATEDLY TO GET\nBACK ON."));
    break;
    case(3): 
    font.print(F("FREE ROAM:\nEXPLORE THE CITY\nAT YOUR OWN PACE."));
    break;
    case(4): 
    font.print(F("RACE TO THE EDGE:\nTRY TO GET OUT OF\nTHE CITY AS FAST\nAS POSSIBLE!"));
    break;
    case(5): 
    font.print(F("CRAZY COURIER:\nPICK UP PACKAGES\nAND DROP THEM OFF\nFAST FOR POINTS\nAND MORE TIME!"));
    break;
  }

  font.setCursor(3,HEIGHT-7);
  font.print(F("^\\ PAGE, @ EXIT"));

  if (arduboy.justPressed(UP_BUTTON)) {
    helpPage = max(helpPage-1,1); 
  }
  if (arduboy.justPressed(DOWN_BUTTON)) {
    helpPage = min(helpPage+1,helpPageMax); 
  }
  if (arduboy.justPressed(A_BUTTON)) {
    mode = menu; 
  }

  arduboy.display();
}

void mainLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  // What is underfoot?
  int8_t playerTile = world.tileAt(playerX>>2,playerY>>2);

  // Count to 3
  if ((playerSpeed > 0) && (arduboy.everyXFrames(1+maxSpeed-playerSpeed))) {
    frame = (frame == 2) ? 0 : frame+1;
  }

  if (playerTile == tilesRoadGravel) {
    playerSpeed = max(playerSpeed-1,0);  
  }
  
  if (arduboy.justPressed(A_BUTTON)) {
    playerSpeed = max(playerSpeed-2,0);  
    if (playerSpeed > 0)
      soundBreak();
    if (arduboy.pressed(DOWN_BUTTON)) {
      mode = menu;
    }
  }

  if (arduboy.justPressed(B_BUTTON)) {
    playerSpeed = min(playerSpeed+2+(playerTile == tilesRoadGravel),maxSpeed);  
    if (playerSpeed < maxSpeed)
      soundAccel();
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
    playerDirection = (Direction) ((playerDirection == northwest) ? north : playerDirection + 1);  
    soundTurn();
  }

  if (arduboy.justPressed(LEFT_BUTTON)) {
    playerDirection = (Direction) ((playerDirection == north) ? northwest : playerDirection - 1);  
    soundTurn();
  }



  uint8_t playerFrame = 0;
  switch(playerDirection) {
    case north: 
      playerFrame = 2-frame;
      playerY -= 3*playerSpeed;
      targetX = targetMidH;
      targetY = targetDown;
      break;

    case northeast: 
      playerFrame = 8-frame;
      playerY -= 2*playerSpeed;
      playerX += 2*playerSpeed;
      targetX = targetLeft;
      targetY = targetDown;
      break;

    case east: 
      playerFrame = 3+frame;
      playerX += 3*playerSpeed;
      targetX = targetLeft;
      targetY = targetMidV;
      break;

    case southeast: 
      playerFrame = 9+frame;
      playerY += 2*playerSpeed;
      playerX += 2*playerSpeed;
      targetX = targetLeft;
      targetY = targetUp;
      break;

    case south: 
      playerFrame = 0+frame;
      playerY += 3*playerSpeed;
      targetX = targetMidH;
      targetY = targetUp;
      break;

    case southwest: 
      playerFrame = 6+frame;
      playerY += 2*playerSpeed;
      playerX -= 2*playerSpeed;
      targetX = targetRight;
      targetY = targetUp;
      break;

    case west: 
      playerFrame = 5-frame;
      playerX -= 3*playerSpeed;
      targetX = targetRight;
      targetY = targetMidV;
      break;

    case northwest: 
      playerFrame = 11-frame;
      playerY -= 2*playerSpeed;
      playerX -= 2*playerSpeed;
      targetX = targetRight;
      targetY = targetDown;
      break;
  }

  if (offsetX < targetX) {
    offsetX++;
  }
  else if (offsetX > targetX) {
    offsetX--;
  }
  if (offsetY < targetY) {
    offsetY++;
  }
  else if (offsetY > targetY) {
    offsetY--;
  }

  world.draw((playerX>>2)-offsetX,(playerY>>2)-offsetY);
  sprites.drawPlusMask(offsetX,offsetY,tilesCycle,playerFrame);
  
//  sprites.drawOverwrite(world.miniLeft,HEIGHT-8,tilesRoad,tilesRoadSpeed+playerSpeed/2);
//  arduboy.fillRect(2,2,8,60,!colorFG);
//  arduboy.drawRect(2,2,8,60,colorFG);
//  arduboy.fillRect(4,62-playerSpeed*6,4,playerSpeed*6,colorFG);
////  arduboy.setCursor(0,0);
////  arduboy.print(playerSpeed);

  world.drawMini(playerX>>8,playerY>>8);
  arduboy.drawRect(world.miniLeft,world.miniTop,world.miniRight-world.miniLeft,world.miniBottom-world.miniTop);
  if (arduboy.frameCount % 16 < 8) {
    sprites.drawPlusMask(
      (world.miniRight+world.miniLeft-8)/2,
      (world.miniBottom+world.miniTop-8)/2,
      tilesBullseye,0);
  }

//
//  arduboy.setCursor(0,HEIGHT-16);
//  arduboy.println(arduboy.cpuLoad());
  
  soundMotor();
  arduboy.display();
}

void backGround(uint16_t color) {
  uint16_t offset = 0;
  for(uint16_t offset=0; offset < WIDTH*HEIGHT/8;) {
    arduboy.sBuffer[offset++] = ((color&0xf000)>>8) + ((color&0xf000)>>12);
    arduboy.sBuffer[offset++] = ((color&0x0f00)>>4) + ((color&0x0f00)>>8); 
    arduboy.sBuffer[offset++] =  (color&0x00f0)     + ((color&0x00f0)>>4);
    arduboy.sBuffer[offset++] =  (color&0x000f)     + ((color&0x000f)<<4);
  }
}

void drawRoad() {

  int16_t gridX = offsetX - (playerX>>2);
  uint8_t mapX = gridX >> 3;
  uint8_t mapOffsetX = gridX & 7;

  int16_t gridY = offsetY - (playerY>>2);
  uint8_t mapY = gridY >> 3;
  uint8_t mapOffsetY = gridY & 7;
  
  for(int8_t y=-1; y < HEIGHT/8; y++) { 
    for(int8_t x=-1; x < WIDTH/8; x++) {
      uint8_t locX = x - mapX;
      uint8_t locY = y - mapY;
      uint8_t tile  = (locX==0) ? 10                  // west edge
                    : (locX<4)  ? 1                   // 
                    : (locX==4) ? ((locY%4) < 2 ? 1 : 15)
                    : (locX==7) ? 14
                    : (locX==8) ? 15
                    : (locX<11)  ? 1
                    : (locX==11) ? ((locY%4) <2  ? 1 : 14)
                    : (locX<15)  ? 1
                    : (locX==15) ? 11
                    : (locY==0)  ? 12
                    : (locY==3)  ? ((locX%2) ? 1 : 16)
                    : (locY<5)   ? 1
                    : (locY==5)  ? 13
                    : 0;
      
//      int16_t xloc = x - gridX;
//      int16_t yloc = y - gridY;
//      uint8_t tile  = (xloc > -24) && (xloc <=  24) ? 1  // black-top
//                    : (yloc > -24) && (yloc <=  24) ? 1  // black-top
//                    : (xloc > -32) && (xloc <= -24) ? 10 //
//                    : (xloc >  24) && (xloc <=  32) ? 11 //
//                    : (yloc > -32) && (yloc <= -24) ? 12 //
//                    : (yloc >  24) && (yloc <=  32) ? 13 //
//                    : 0; // offroad
      sprites.drawOverwrite(x*8+mapOffsetX,y*8+mapOffsetY,tilesRoad,tile);      
    }
  }

//  arduboy.setCursor(WIDTH-16,HEIGHT-16);
//  arduboy.println(gridX);
//  arduboy.setCursor(WIDTH-16,HEIGHT-8);
//  arduboy.println(mapX);
  

}
void drawGridPoints(uint8_t color) {
  uint8_t gridX = (offsetX - (playerX >> 2)) & 0x3f;
  uint8_t gridY = (offsetY - (playerY >> 2)) & 0x1f;
  
  for(uint8_t y=gridY; y < HEIGHT; y+=32) { 
    for(uint8_t x=gridX; x < WIDTH; x+=64) {
      arduboy.drawPixel(x,y,color); 
      arduboy.drawPixel(x+1,y,color); 
    }
  }
}


void drawStars(uint16_t seed, uint8_t layer) {
  uint16_t background = -((playerY >> layer) << 7) - (playerX >> layer);
  for(uint16_t i=0; i < WIDTH*HEIGHT; i+=seed) {
    background += seed;
    arduboy.drawPixel (background & 0x7f, (background >> 7) & 0x3f, WHITE);
  }
}

void soundMotor() {  
  if ((playerSpeed > 0) && !sound.playing()) {
    sound.tone(NOTE_C2H+playerSpeed*50,10, NOTE_REST,80-playerSpeed*3);
  }
}

void soundTurn() {  
  sound.tone(NOTE_F7,20,NOTE_E7,20,NOTE_D7,20);
}

void soundBreak() {  
  sound.tone(NOTE_C5,30);
}

void soundAccel() {  
  sound.tone(NOTE_C1,40);
}

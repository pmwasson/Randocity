#include <Arduboy2.h>
#include <Sprites.h>
#include <ArduboyTones.h>
#include "FatFont.h"
#include "World.h"
#include "SavedSprites.h"
#include "Timer.h"

Arduboy2 arduboy;
Sprites  sprites;
ArduboyTones sound(arduboy.audio.enabled);
FatFont font;
World world;

Timer gameTimer;
Timer startTimer;

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

enum Mode : uint8_t {title, freeRoam, edgeRace, crazyCourier, menu, viewMap, help, enterSeed, displayMessage};
Mode mode = title;

int8_t menuItem = 0;
static const int8_t menuMaxItem = 5; 
uint32_t seedNew;
uint32_t seedRandom;
uint8_t helpPage;
static const int8_t helpPageMax = 5;

uint16_t playerScore = 0;
int32_t courierX = (((int32_t)world.mapWidth/2l)<<11) - (8l<<2);
int32_t courierY = (((int32_t)world.mapHeight/2l)<<11) + (32l<<5) - (8l<<2);

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  Serial.begin(9600);

  generateWorld();
  setMiniTitle();
  setPlayerCenter();
}

void setMiniTitle() {
  // Set up mini-map for title screen
  world.miniLeft   = 0;
  world.miniRight  = WIDTH;
  world.miniTop    = HEIGHT-24;
  world.miniBottom = HEIGHT;
}

void setMapView() {
  // Set up mini-map for map screen
  world.miniLeft   = 0;
  world.miniRight  = WIDTH;
  world.miniTop    = 8;
  world.miniBottom = HEIGHT-8;
}

void setMapGame() {
  // Set up mini-map for game screen
  world.miniLeft   = world.mainRight;
  world.miniRight  = WIDTH;
  world.miniTop    = 0;
  world.miniBottom = HEIGHT;
}

void setMapTimer() {
  // Set up mini-map for game screen with timer
  world.miniLeft   = world.mainRight;
  world.miniRight  = WIDTH;
  world.miniTop    = 0;
  world.miniBottom = HEIGHT-8;
}

void setMapScore() {
  // Set up mini-map for game screen with timer & score
  world.miniLeft   = world.mainRight;
  world.miniRight  = WIDTH;
  world.miniTop    = 8;
  world.miniBottom = HEIGHT-8;
}

void setPlayerCenter() {
  playerX =  ((int32_t)world.mapWidth/2l)<<11;
  playerY =  (((int32_t)world.mapHeight/2l)<<11) - (32l<<5);
}

void loop() {
  switch(mode) {
    case freeRoam: 
    case edgeRace: 
    case crazyCourier: 
      gameLoop();
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
  world.init(seed);
}

void initPlayer() {
  playerDirection = north;
  playerSpeed = 0;
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

void printTimer() {
  if (!gameTimer.isDone() || ((arduboy.frameCount % 32) < 16)) {
    if (gameTimer.timerMinutes < 10) {
      font.print(F("0"));
    }
    font.print(gameTimer.timerMinutes);
    font.print(F(":"));
    if (gameTimer.timerSeconds < 10) {
      font.print(F("0"));
    }
    font.print(gameTimer.timerSeconds);
  }
  else {
    font.print(F("  :  "));
  }
}

void printScore() {
  uint16_t scoreCopy = playerScore|1;
  while(scoreCopy < 1000) {
    font.print(F("0"));
    scoreCopy *= 10;
  }
  font.print(playerScore);
  font.print("0");
}

void infoLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0x0101);

  font.setCursor(0,3);
  font.println(F("    RANDO CITY     "));
  font.println();
  font.println(F("  BY PAUL WASSON   ")); 
  font.println(F("  DECEMBER, 2019   "));
  font.println();  
  font.println(F("  PRESS @ FOR MENU "));

  arduboy.display();

  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
    mode = menu;
  }
}


void titleLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0x0000);

  world.drawMini(playerX>>8,playerY>>8);
  playerX+=112;
  playerY+=112;
  if ((playerX > (240l << 11)) || (playerY > (240l << 11))) {
    playerX = playerY = (16l << 11); 
  }
  
  sprites.drawErase(0, HEIGHT-24, title_mask, 0);
  sprites.drawSelfMasked(0, 0, title_image, 0);

  arduboy.display();

  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
    setPlayerCenter();
    mode = menu;
  }
}

void menuLoop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  backGround(0);

  font.setCursor(0,0);
  font.print(F("MENU:\n  FREE ROAM\n  RACE TO THE EDGE\n  CRAZY COURIER\n  VIEW MAP\n  HELP\n\nPRESS _ TO SELECT"));
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
        mode = freeRoam;
        setMapGame();
        break;
      case 1:
        mode = edgeRace;
        initPlayer();
        setMapTimer();
        gameTimer.startCountUp();
        startTimer.startCountDown(0,5);
        break;
      case 2:
        mode = crazyCourier;
        initPlayer();
        setMapScore();
        randomizeCourier();
        playerScore = 0;
        gameTimer.startCountDown(2,0);
        startTimer.startCountDown(0,5);
        break;
      case 3:
        setMapView();
        savePlayerX = playerX;
        savePlayerY = playerY;
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

void gameLoop() {
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

  if (startTimer.isDone()) {
    
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

  // Draw world
  world.draw((playerX>>2)-offsetX,(playerY>>2)-offsetY);

  if (mode == crazyCourier) {
    // Draw objects
    int16_t courierScreenX = ((courierX-playerX)>>2)+offsetX;
    int16_t courierScreenY = ((courierY-playerY)>>2)+offsetY;
    if ((courierScreenX >= world.mainLeft-16) && (courierScreenX < world.mainRight) &&
        (courierScreenY >= world.mainTop-16) && (courierScreenY < world.mainBottom)) {
      sprites.drawPlusMask(courierScreenX,courierScreenY,tilesCycle,13);
    }
  }
  
  // Draw player
  sprites.drawPlusMask(offsetX,offsetY,tilesCycle,playerFrame);

  // Draw map
  world.drawMini(playerX>>8,playerY>>8);

  if (mode == crazyCourier) {
    int32_t courierMiniScreenX = (world.miniRight+world.miniLeft-8)/2 + ((courierX - playerX + 128)>>8);
    int32_t courierMiniScreenY = (world.miniBottom+world.miniTop-8)/2 + ((courierY - playerY + 128)>>8);
    bool offMap = (courierMiniScreenX < world.miniLeft) || (courierMiniScreenX > world.miniRight-8) ||
                  (courierMiniScreenY < world.miniTop)  || (courierMiniScreenY > world.miniBottom-8); 
    courierMiniScreenX = min(max(world.miniLeft,courierMiniScreenX),world.miniRight-8);
    courierMiniScreenY = min(max(world.miniTop,courierMiniScreenY),world.miniBottom-8);
    
    if (arduboy.frameCount % 32 < 16) {
        sprites.drawPlusMask(courierMiniScreenX,courierMiniScreenY,tilesBullseye,1+offMap);
    }
  }
  
  if (arduboy.frameCount % 16 < 8) {
    sprites.drawPlusMask(
      (world.miniRight+world.miniLeft)/2-4,
      (world.miniBottom+world.miniTop)/2-4,
      tilesBullseye,0);
  }
  
  arduboy.drawRect(world.miniLeft,world.miniTop,world.miniRight-world.miniLeft,world.miniBottom-world.miniTop);

  // Start Timer
  if (!startTimer.isDone()) {
    if (arduboy.everyXFrames(30)) {
      startTimer.tick();
      if ((startTimer.timerSeconds >= 2) && (startTimer.timerSeconds <= 4)) {
        soundStart1();
      }
      else if (startTimer.timerSeconds == 1) {
        soundStart2();        
      }
    }
    if ((startTimer.timerSeconds >= 2) && (startTimer.timerSeconds <= 4)) {
      font.setCursor((world.mainLeft + world.mainRight - 8)/2,(world.mainTop + world.mainBottom - 8)/2);
      font.print(startTimer.timerSeconds-1);
    }
    else if (startTimer.timerSeconds == 1) {
      font.setCursor((world.mainLeft + world.mainRight - 24)/2,(world.mainTop + world.mainBottom - 8)/2);
      font.print(F("GO!"));
    }
  }
  // Timer
  if (mode != freeRoam) {
    if (startTimer.isDone() && arduboy.everyXFrames(30)) gameTimer.tick();
    arduboy.fillRect(world.miniLeft,world.miniBottom,world.miniRight-world.miniLeft,HEIGHT-world.miniBottom,BLACK);
    arduboy.drawRect(world.miniLeft,world.miniBottom-1,world.miniRight-world.miniLeft,HEIGHT-world.miniBottom+1);
    font.setCursor(world.miniLeft+8,HEIGHT-7);
    printTimer();

    if (isPlayerOutside()) gameTimer.setDone(); 
  }

  // Score
  if (mode == crazyCourier) {
    arduboy.fillRect(world.miniLeft,0,world.miniRight-world.miniLeft,world.miniTop,BLACK);
    arduboy.drawRect(world.miniLeft,0,world.miniRight-world.miniLeft,world.miniTop+1);
    font.setCursor(world.miniLeft+8,0);
    printScore();

    if (isPlayerOnTarget()) {
      playerScore += min(gameTimer.timerMinutes*10 + gameTimer.timerSeconds/10,9999);
      gameTimer.startCountDown(2,0);
      randomizeCourier();
      soundGood();
    }
  }
  
//  arduboy.setCursor(0,0);
//  arduboy.print(playerX>>11);
//  arduboy.print(",");
//  arduboy.print(playerY>>11);
//  arduboy.print(":");
//  arduboy.print(world.segmentsAt(playerX>>2,playerY>>2),HEX);
//
//  arduboy.setCursor(0,HEIGHT-8);
//  arduboy.print(courierX>>11);
//  arduboy.print(",");
//  arduboy.print(courierY>>11);
//  arduboy.print(":");
//  arduboy.print(world.segmentsAt(courierX>>2,courierY>>2),HEX);
  
//  arduboy.println(arduboy.cpuLoad());
  
  soundMotor();
  arduboy.display();
}

bool isPlayerOutside() {
  return (((playerX >> 11) < 0)   ||
          ((playerX >> 11) > 255) ||
          ((playerY >> 11) < 0)   ||
          ((playerY >> 11) > 255) );
}

bool isPlayerOnTarget() {
  return (( ((playerX+16) >> 5) == ((courierX+16) >> 5) ) &&
          ( ((playerY+16) >> 5) == ((courierY+16) >> 5) ));
}

void randomizeCourier() {
  courierX = ((playerX >> 11) + random(-5,5)) << 11; 
  courierY = ((playerY >> 11) + random(-5,5)) << 11;
  // pick a safe direction
  if ((world.segmentsAt(courierX>>2,courierY>>2)&0b10010001) != 0) {
    // North 
    courierX += (32l<<5);
  }
  else {
    // West
    courierY += (32l<<5);
  }
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

void soundGood() {
  sound.tone(NOTE_C4H,50,NOTE_D4H,50,NOTE_F4H,75);
}

void soundBad() {
  sound.tone(NOTE_C5H,100,NOTE_D4H,100);
}

void soundStart1() {
  sound.tone(NOTE_C5H,250);
}

void soundStart2() {
  sound.tone(NOTE_F5H,500);
}

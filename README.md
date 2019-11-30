# ProceduralCity
## Introduction
Arduboy open-world procedurally generated city motorcycle toy
* The city is generated from a random seed.  But a given seed will always produce the exact same city.
  * The underlying algorithm uses an LFSR (linear feedback shift register) for the random element, but for a given seed the sequence is always the same.
* The city is 256x256 blocks with each block being 64x64 tiles and each tile is 8x8 pixels. 
* Assuming a block is 100m, then the random city is about the size of El Paso, TX
  * 100m/block * 256 block = 25.6km ~= 15.9 miles
  * (15.9 miles)<sup>2</sup> = 252.8 miles<sup>2</sup>
  * El Paso is about 255.2 miles<sup>2</sup>
* You start out in the middle of the city and it takes about 10 minutes of playtime to reach the edge
* I call it a toy, since a game has goals and rules whereas a toy is just something to play with.
## Controls
* Left/Right buttons turn
* B button accelerates each time it is pressed
* A button brakes each time it is pressed
* Holding the DOWN button and pressing A will generate a new city with a new random seed but keeps the motorcycle in the same position within the city.
* Going off road will stop the motorcycle.  To get back on the road, press B repeatedly.
## To Do
* Add a menu system
  * Record and enter city seed
  * Explore map
* Turn into a game
  * Race-to-the-edge
  * Crazy-taxi (random location you must reach is a certain time)
  

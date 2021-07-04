#ifndef CONSTANTS_H
#define CONSTANTS_H

// size of matrix
const int HEIGHT = 31;     
const int WIDTH = 31;   
const int SQUARE_OF_MAZE = WIDTH * HEIGHT;
// marks in matrix
const int WALL = 0;     
const int PATH = 1;    
const int PLAYER = 2;  
const int EXIT = 3;    
// start position
const int START_Y = 1;
const int START_X = 1;
// win position
const int WIN_Y = HEIGHT - 2;
const int WIN_X = WIDTH - 2;
//
const char BRICK = static_cast<unsigned char>(178);  // ASCII symbol for wall

#endif //  CONSTANTS_H

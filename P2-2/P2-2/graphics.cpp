// ============================================
// The graphics class file
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "graphics.h"
#include "globals.h"




///////////////////////////////////////////
// Drawing Images based on Characters
///////////////////////////////////////////

//Additional color definitions
#define YELLOW 0xFFFF00
#define RED    0xFF0000 
#define BROWN  0xD2691E
#define DIRT   BROWN
// You can define more hex colors here


//Function to draw images based on characters
// - The function takes an image array and changes the color 
//   labeled by a character to a hex value (ex: 'Y' -> 0xFFF00)
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        //You can add more characters by defining their hex values above
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'B') colors[i] = BLUE;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}


///////////////////////////////////////////
//Simple drawing of objects using uLCD methods
///////////////////////////////////////////

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_player(int u, int v, int key, int run)
{
    if (key)
    {
        const char* img = 
        "     B     "
        "    BBB    "
        "   BBBBB   "
        "  BBBBBBB  "
        " BBBBYBBBB "
        "BBBBYYYBBBB"
        " BBBBYBBBB "
        "  BBBBBBB  "
        "   BBBBB   "
        "    BBB    "
        "     B     ";
    draw_img(u, v, img);
    }
    if (run)
    {
        const char* img = 
        "     B     "
        "    BBB    "
        "   BBBBB   "
        "  BBBBBBB  "
        " BBBBGBBBB "
        "BBBBGGGBBBB"
        " BBBBGBBBB "
        "  BBBBBBB  "
        "   BBBBB   "
        "    BBB    "
        "     B     ";
    draw_img(u, v, img);
        
    } else {
         const char* img = 
        "     B     "
        "    BBB    "
        "   BBBBB   "
        "  BBBBBBB  "
        " BBBBRBBBB "
        "BBBBRRRBBBB"
        " BBBBRBBBB "
        "  BBBBBBB  "
        "   BBBBB   "
        "    BBB    "
        "     B     ";
    draw_img(u, v, img);
        
    }
}


void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_door(int u, int v)
{
    draw_nothing(u,v);
    uLCD.line(u, v+6, u+11, v+6, 0xFFFF00);
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status(int lives, int x, int y)
{
    char str1[4]; // character array to store the string
    char str2[4]; // character array to store the string
    
    // Convert integer to string using sprintf
    uLCD.filled_rectangle(0, 18, 127, 18, BLACK);
    sprintf(str1, "%02d", x);
    sprintf(str2, "%02d", y);
    uLCD.text_height(1);
    uLCD.locate(9, 0);
    uLCD.color(WHITE);
    uLCD.puts("x:");
    uLCD.puts(str1);
    uLCD.locate(14, 0);
    uLCD.puts("Y:");
    uLCD.puts(str2);
    const char* img =
        "RRRR   RRRR"
        "RRRRR RRRRR"
        "RRRRRRRRRRR"
        " RRRRRRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "    RR     "
        "           ";

        const char* img1 =
        "               "
        "                "
        "                "
        "                "
        "               "
        "                "
        "             "
        "           ";
        if (lives > 0) {
    draw_img(1, 0, img);
        }  else {
    draw_img(1,0, img1);
    }

    if (lives > 1) {
    draw_img(20,0, img);
    } else {
    draw_img(20,0, img1);
    }

    if (lives > 2) {
    draw_img(40, 0, img);
    }  else {
    draw_img(40,0, img1);
    }
}

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     12, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

///////////////////////////////////////////
//Sprite drawing of objects using draw_img function
///////////////////////////////////////////

void draw_plant(int u, int v)
{
    const char* img = 
        "           "
        " GGGGGGGG  "
        " GGGGGGGGG "
        "GGGGGGGGGGG"
        "GGGGGGGGGGG"
        " GGGGGGGG  "
        "    DD     "
        "    DD     "
        "    DD     "
        "   DDDDD   "
        "  D  D  D  ";
    draw_img(u, v, img);
}



void draw_big_plant(int u, int v)
{
    int new_piskel_data[121] = {
0xff0c8a2a, 0xff0d8a2b, 0xff0c8b2b, 0xff0c8a2a, 0xff0c8b2b, 0xff0c8a2a, 0xff0c8b2b, 0xff174125, 0xff0c8b2a, 0xff0c8b2b, 0xff0c8a2b, 
0xff0c8b2a, 0xff0d8b2a, 0xff0c8a2a, 0xff0c8b2b, 0xff0d8a2a, 0xff0c8a2a, 0xff0d8b2a, 0xff164125, 0xff174025, 0xff164025, 0xff174125, 
0xff44ca74, 0xff0c8b2b, 0xff0d8a2b, 0xff0c8a2a, 0xff0c8b2a, 0xff44ca74, 0xff0c8b2a, 0xff174025, 0xff174124, 0xff0d8b2b, 0xff174025, 
0xff45cb75, 0xff0c8a2a, 0xff44ca75, 0xff45ca75, 0xff45ca74, 0xff44cb74, 0xff0d8a2b, 0xff164124, 0xff174025, 0xff0c8b2a, 0xff164024, 
0xff44cb74, 0xff45ca75, 0xff45ca75, 0xff45ca75, 0xff45cb74, 0xff0d8a2a, 0xff0c8a2b, 0xff174024, 0xff0c8a2b, 0xff0c8b2a, 0xff164125, 
0xff0d8b2a, 0xff0c8b2a, 0xff0c8b2a, 0xff44ca75, 0xff44ca75, 0xff44cb75, 0xff44ca75, 0xff44cb75, 0xff44ca74, 0xff0d8b2b, 0xff164025, 
0xff0c8b2a, 0xff0d8b2b, 0xff0c8b2a, 0xff0c8b2b, 0xff45ca75, 0xff45cb74, 0xff44cb75, 0xff44ca75, 0xff45ca75, 0xff0c8a2a, 0xff164024, 
0xff0c8b2b, 0xff0c8b2a, 0xff0d8a2a, 0xff0c8a2a, 0xff44ca75, 0xff44ca75, 0xff44cb74, 0xff44ca74, 0xff44ca75, 0xff0d8b2a, 0xff164124, 
0xff0c8b2b, 0xff0d8a2b, 0xff45ca75, 0xff174025, 0xff0c8b2b, 0xff0d8b2a, 0xff0c8a2a, 0xff0c8b2a, 0xff0d8b2b, 0xff164024, 0xff164125, 
0xff45cb75, 0xff44ca75, 0xff44ca74, 0xff174024, 0xff164025, 0xff0c8a2b, 0xff0c8a2a, 0xff0c8b2a, 0xff0c8a2b, 0xff174024, 0xff0c8b2b, 
0xff0d8a2a, 0xff0c8a2a, 0xff0c8b2a, 0xff0d8a2b, 0xff174025, 0xff164024, 0xff164025, 0xff164125, 0xff164125, 0xff164025, 0xff0c8b2a
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        

        
}






void draw_empty_tree(int u, int v)
{
    int new_piskel_data[121] = {
0xff0fbb11, 0xff0fbb10, 0xff0fbb10, 0xff0fba10, 0xff0fba11, 0xff0eba11, 0xff0fba11, 0xff0ebb10, 0xff0fba11, 0xff0fbb11, 0xff0eba10, 
0xff0fba11, 0xff0fba11, 0xff0fbb11, 0xff0fbb11, 0xff0fba11, 0xff0fba10, 0xff0eba10, 0xff0fbb11, 0xff0fbb11, 0xff0ebb11, 0xff0ebb10, 
0xff0fba11, 0xff0fba10, 0xff0fba11, 0xff0ebb10, 0xff0fba10, 0xff0fba10, 0xff0eba10, 0xff0eba11, 0xff0fbb11, 0xff0ebb10, 0xff0fbb11, 
0xff0ebb10, 0xff0fbb11, 0xff0fbb11, 0xff0fbb10, 0xff0ebb11, 0xff0fbb10, 0xff0fbb10, 0xff0eba11, 0xff0fbb10, 0xff0eba11, 0xff0fba11, 
0xff0fba11, 0xff0ebb11, 0xff0fbb11, 0xff0eba11, 0xff0ebb11, 0xff0fbb11, 0xff0fba11, 0xff0ebb11, 0xff0eba11, 0xff0fbb10, 0xff0fbb11, 
0xff0ebb10, 0xff0fba10, 0xff0fbb11, 0xff0fbb11, 0xff0fbb11, 0xff0fba11, 0xff0fbb11, 0xff0ebb10, 0xff0fbb11, 0xff0fbb10, 0xff0ebb11, 
0x00000001, 0x00000101, 0x00000100, 0x00000000, 0xff19189d, 0xff19189c, 0xff19199c, 0x00000000, 0x00010000, 0x00010001, 0x00010101, 
0x00000001, 0x00000000, 0x00000001, 0x00010001, 0xff19199d, 0xff19189c, 0xff19199d, 0x00000100, 0x00000100, 0x00000100, 0x00000001, 
0x00000101, 0x00000001, 0x00000001, 0x00010000, 0xff19199d, 0xff19199d, 0xff19199c, 0x00000000, 0x00000001, 0x00000001, 0x00010000, 
0x00010000, 0x00010000, 0x00000100, 0x00010000, 0xff18199d, 0xff19189c, 0xff18189d, 0x00000001, 0x00010000, 0x00010101, 0x00000100, 
0x00010000, 0x00010100, 0x00000100, 0x00010001, 0xff19189d, 0xff19189c, 0xff19199d, 0x00000100, 0x00000000, 0x00000001, 0x00000000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        

        
}






void draw_apple_tree(int u, int v)
{
    int new_piskel_data[121] = {
0xff0fbb11, 0xff0fba11, 0xff0fbb10, 0xff0fba11, 0xff0fba10, 0xff0fba11, 0xff0eba10, 0xff0fbb11, 0xff0fba11, 0xff0fbb10, 0xff0ebb11, 
0xff0fbb10, 0xff0101ff, 0xff0100ff, 0xff0ebb11, 0xff0fba11, 0xff0fba11, 0xff0001ff, 0xff0000ff, 0xff0ebb11, 0xff0ebb10, 0xff0fbb10, 
0xff0fba11, 0xff0100ff, 0xff0000ff, 0xff0fba10, 0xff0fba10, 0xff0eba10, 0xff0000fe, 0xff0100ff, 0xff0ebb10, 0xff0fbb11, 0xff0ebb11, 
0xff0fba11, 0xff0fba10, 0xff0eba11, 0xff0ebb11, 0xff0000ff, 0xff0100fe, 0xff0fbb10, 0xff0fbb11, 0xff0ebb11, 0xff0000fe, 0xff0100ff, 
0xff0fbb11, 0xff0fba11, 0xff0fba11, 0xff0fba11, 0xff0100ff, 0xff0100ff, 0xff0fba11, 0xff0fbb10, 0xff0ebb10, 0xff0000ff, 0xff0001ff, 
0xff0fba11, 0xff0eba11, 0xff0fbb10, 0xff0fbb11, 0xff0ebb11, 0xff0ebb10, 0xff0fbb10, 0xff0fba11, 0xff0ebb10, 0xff0fbb11, 0xff0fbb10, 
0x00010000, 0x00010000, 0x00010100, 0x00000100, 0xff18199d, 0xff19199c, 0xff19199c, 0x00000001, 0x00000100, 0x00000101, 0x00000001, 
0x00000000, 0x00010100, 0x00000101, 0x00000000, 0xff19199d, 0xff18199d, 0xff18199d, 0x00000100, 0x00000001, 0x00000000, 0x00010000, 
0x00010001, 0x00000100, 0x00010100, 0x00010001, 0xff18189c, 0xff18199d, 0xff19199c, 0x00010101, 0x00000000, 0x00000001, 0x00000000, 
0x00010000, 0x00010000, 0x00010000, 0x00010001, 0xff18189d, 0xff19189d, 0xff19199c, 0x00000100, 0x00000000, 0x00000001, 0x00000001, 
0x00000101, 0x00010100, 0x00010001, 0x00000001, 0xff19199d, 0xff19199d, 0xff19189d, 0x00010001, 0x00010101, 0x00010100, 0x00010101
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        

        
}

void draw_talking_npc(int u, int v)
{
     const char* img = 

        " RRRRRRRRR "
        " RRRRRRRRR "
        "RRRRRYRRRRR"
        "RRRRRRRRRRR"
        " RRRRRRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "           "
        "    RRR    ";
    draw_img(u, v-10, img);

    const char* img1 = 
        "     R     "
        "    RRR    "
        "   RRRRR   "
        "  RRRRRRR  "
        " RRRRYRRRR "
        "RRRRYYYRRRR"
        " RRRRYRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "    RRR    "
        "     R     ";
    draw_img(u, v, img1);
}

void draw_npc(int u, int v)
{
 /*if (speech) {
     const char* img1 = 

        " RRRRRRRRR "
        " RRRRRRRRR "
        "RRRRRYRRRRR"
        "RRRRRRRRRRR"
        " RRRRRRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "           "
        "    RRR    ";
    draw_img(u, v-10, img1);
 }*/
    const char* img = 
        "     R     "
        "    RRR    "
        "   RRRRR   "
        "  RRRRRRR  "
        " RRRRYRRRR "
        "RRRRYYYRRRR"
        " RRRRYRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "    RRR    "
        "     R     ";
    draw_img(u, v, img);
}

void draw_stairs(int u, int v)
{
    const char* img =
        "        333"
        "        353"
        "      33333"
        "      35553"
        "    3333333"
        "    3555553"
        "  333333333"
        "  355555553"
        "33333333333"
        "35555555553"
        "33333333333";
    draw_img(u, v, img);
}



////////////////////////////////////////////
//Examples of Piskel sprite C array export
////////////////////////////////////////////

void draw_buzz(int u, int v)
{

int new_piskel_data[121] = {
0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xff0000ff, 0xff606060, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff0000ff, 0xffffffff, 0xff0000ff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffffff00, 0xffffff00, 0xffffff00, 0xff0000ff, 0xff0000ff, 0xff606060, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff137bff, 0xffffffff, 0x00000000, 0x00000000, 
0xff137bff, 0x00000000, 0xff137bff, 0xff58110c, 0xff58110c, 0xff58110c, 0xffffff00, 0xff58110c, 0xff137bff, 0x00000000, 0x00000000, 
0x00000000, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0xffffff00, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xffffff00, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_buzz2(int u, int v)
{

int new_piskel_data[121] = {
0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0xffffffff, 0xff0000ff, 0xff606060, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffff0000, 0xffff0000, 0xff0000ff, 0xffffffff, 0xff0000ff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff0000ff, 0xff0000ff, 0xff606060, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0xffff0000, 0xffffffff, 0xffffffff, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0xffff0000, 0xff58110c, 0xff58110c, 0xff137bff, 0xffffffff, 0x00000000, 0x00000000, 
0xff137bff, 0x00000000, 0xff137bff, 0xff58110c, 0xff58110c, 0xff58110c, 0xffff0000, 0xff58110c, 0xff137bff, 0x00000000, 0x00000000, 
0x00000000, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0xffff0000, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0xffff0000, 0xff58110c, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xffff0000, 0xffff0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_water(int u, int v)
{


int new_piskel_data[121] = {

0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0x00000000, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff7c7cff, 0xff0101c4, 0xff0101c4, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0xff0101c4, 0x00000000, 0x00000000, 0x00000000

};    
   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_fire(int u, int v)
{

int new_piskel_data[121] = {

0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0xffff0009, 0xffff0009, 0xffff0009, 0xffff0009, 0x00000000, 0xffff0009, 0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 0x00000000, 
0xffff0009, 0xffff0009, 0xffdeb200, 0xffff0009, 0x00000000, 0xffff0009, 0xffdeb200, 0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 
0x00000000, 0xffff0009, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffff0009, 0x00000000, 0x00000000, 
0x00000000, 0xffff0009, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffff0009, 0xffff0009, 0x00000000, 
0x00000000, 0xffff0009, 0xffde4600, 0xffde4600, 0xffdeb200, 0xffdeb200, 0xffdeb200, 0xffff0009, 0xffff0009, 0xffff0009, 0xffff0009, 
0xffff0009, 0xffff0009, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffff0009, 0xffde4600, 0xffde4600, 0xffff0009, 
0xffff0009, 0xffb30007, 0xffb30007, 0xffb30007, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffde4600, 0xffff0009, 0xffff0009, 
0xffff0009, 0xffb30007, 0xffb30007, 0xffb30007, 0xffde4600, 0xffde4600, 0xffb30007, 0xffb30007, 0xffb30007, 0xffff0009, 0x00000000, 
0xffff0009, 0xffff0009, 0xffff0009, 0xffb30007, 0xffb30007, 0xffb30007, 0xffb30007, 0xffb30007, 0xffff0009, 0xffff0009, 0xffff0009

};    
   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_earth(int u, int v)
{

int new_piskel_data[121] = {

0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffffff, 0xff00659e, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0x00000000, 
0xffffffff, 0xffffffff, 0xff00659e, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0x00000000, 
0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0x00000000, 
0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e, 
0xff00659e, 0xff00659e, 0xff00659e, 0xff00659e, 0xffffffff, 0xff00659e, 0xffffffff, 0xffffffff, 0xff00659e, 0xff00659e, 0xff00659e

};    
   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}





///////////////////////////////////////////
//Other sprites
///////////////////////////////////////////

void draw_cave1(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave2(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave3(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333000"
        "33333333000"
        "33333333000";
    draw_img(u, v, img);
}
void draw_cave4(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}


void draw_mud(int u, int v)
{
   const char* img = 
        "DDDDDDDDDDD"
        "DDD3333DD3D"
        "D33D33D33DD"
        "D3DDD33D33D"
        "DD333D333DD"
        "D33D33DDDD"
        "DDD333D333D"
        "DD3DDD3DD3D"
        "D3D333D33DD"
        "DDDDD33DDDD"
        "DDDDDDDDDDD";
    draw_img(u, v, img);
}


void draw_skull(int u, int v)
{

int new_piskel_data[121] = {
0x00000100, 0x00000101, 0x00010100, 0x00010001, 0x00010100, 0x00000100, 0x00000101, 0x00010000, 0x00000001, 0x00010001, 0x00010000, 
0x00000000, 0x00000001, 0x00000101, 0x00000100, 0x00000000, 0x00010001, 0x00010000, 0x00000000, 0x00010000, 0x00010000, 0x00010000, 
0x00000001, 0x00000001, 0x00010100, 0x00010100, 0x00010000, 0x00010001, 0x00000100, 0x00000000, 0x00010001, 0x00000000, 0x00010001, 
0x00010101, 0x00000100, 0xfffffeff, 0xfffefeff, 0xfffffffe, 0xfffffeff, 0xffffffff, 0xffffffff, 0xfffeffff, 0x00000000, 0x00000100, 
0x00010001, 0x00010001, 0xfffefefe, 0xfffffefe, 0xfffeffff, 0xfffeffff, 0xfffffffe, 0xffffffff, 0xfffffeff, 0x00000000, 0x00000000, 
0x00000000, 0xfffffeff, 0xfffffeff, 0xff010001, 0xff000101, 0xffffffff, 0xff000001, 0xff010001, 0xfffffefe, 0xfffefeff, 0x00010100, 
0x00000000, 0xfffffeff, 0xff000001, 0xff010000, 0xff000000, 0xffffffff, 0xff000000, 0xff010100, 0xff000000, 0xfffefeff, 0x00010001, 
0x00000000, 0xfffffefe, 0xff000000, 0xff000000, 0xff010100, 0xfffefffe, 0xff010101, 0xff000100, 0xff000001, 0xfffffffe, 0x00010000, 
0x00010100, 0x00010000, 0xfffefefe, 0xfffeffff, 0xfffffffe, 0xfffffeff, 0xfffefeff, 0xfffeffff, 0xfffffffe, 0x00000000, 0x00010101, 
0x00010101, 0x00010000, 0xfffffefe, 0xffffffff, 0xfffffeff, 0xff000100, 0xfffefffe, 0xffffffff, 0xffffffff, 0x00000101, 0x00000000, 
0x00000000, 0x00000101, 0xfffffffe, 0xff000000, 0xfffffefe, 0xffffffff, 0xfffefeff, 0xff000000, 0xfffeffff, 0x00010001, 0x00000101
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_dead_skull(int u, int v)
{

int new_piskel_data[121] = {
0x00000001, 0x00000000, 0x00000101, 0x00000000, 0x00000001, 0x00010000, 0x00010001, 0x00000000, 0x00000000, 0x00000000, 0x00010101, 
0x00010100, 0x00000101, 0x00000001, 0x00010100, 0x00000100, 0x00000000, 0x00010000, 0x00000100, 0x00000100, 0x00010000, 0x00010000, 
0x00000001, 0x00010000, 0x00010000, 0x00000001, 0x00000101, 0x00010100, 0x00000100, 0x00000000, 0x00010000, 0x00000100, 0x00010100, 
0xff1e1ee9, 0xff1e1fe9, 0xffa3a2ac, 0xffa3a2ac, 0xffa3a2ad, 0xffa3a2ad, 0xffa3a2ac, 0xff1e1fe9, 0xff1f1ee8, 0x00010000, 0x00000001, 
0x00010100, 0xff1f1fe8, 0xff1e1ee9, 0xffa2a3ad, 0xffa3a3ad, 0xffa2a2ad, 0xff1e1fe9, 0xff1f1ee9, 0xffa2a2ac, 0x00010100, 0x00000000, 
0x00000001, 0xffa2a2ac, 0xff1e1ee9, 0xff1e1ee8, 0xff000101, 0xff1f1ee9, 0xff1f1ee9, 0xff010100, 0xffa2a2ac, 0xffa2a2ad, 0x00000100, 
0x00010100, 0xffa2a2ac, 0xff000100, 0xff1f1ee9, 0xff1f1ee9, 0xff1e1fe9, 0xff000000, 0xff010001, 0xff010100, 0xffa2a2ac, 0x00000000, 
0x00000001, 0xffa3a2ad, 0xff000001, 0xff1f1ee9, 0xff1f1ee8, 0xff1f1ee9, 0xff010000, 0xff000000, 0xff000100, 0xffa2a2ac, 0x00000000, 
0x00000001, 0x00010000, 0xff1e1ee8, 0xff1f1fe8, 0xffa2a2ac, 0xff1f1ee9, 0xff1f1fe9, 0xffa3a2ac, 0xffa2a3ac, 0x00010001, 0x00010000, 
0x00010001, 0xff1e1fe9, 0xff1e1ee9, 0xffa3a2ac, 0xffa2a2ac, 0xff000101, 0xff1e1fe9, 0xff1f1fe9, 0xffa2a3ac, 0x00010000, 0x00010101, 
0xff1e1ee9, 0xff1f1fe9, 0xffa3a3ad, 0xff000000, 0xffa3a3ac, 0xffa3a2ac, 0xffa2a2ad, 0xff1e1fe9, 0xff1e1ee8, 0xff1e1ee9, 0x00010000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

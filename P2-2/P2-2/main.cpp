//=================================================================
// The main program file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// Projet includes
#include "globals.h"
#include "hardware.h"
#include "hash_table.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include <math.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);


/////////////////////////
// Struct of Player 
/////////////////////////

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;            // Current locations
    int px, py;   
    int px2, py2;         // Previous locations
    bool has_key;       // flag when obtained the key
    bool game_solved1;   // flag when game is complete
    bool game_solved2;   // flag when game is complete
    bool talked_to_npc; // flag when you've talked to npc
    bool ramblin;
    bool run;
    bool win_game;
    int lives;
    int plives;
    bool water;
    bool fire;
    bool earth;
    int speed;

    //You may add more flags as needed

} Player;



/////////////////////////
// Get Action
/////////////////////////

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define RAMBLIN 7
#define RUN 8

int get_action(GameInputs inputs)
{
    //******************
    
    if (inputs.b1) {
        return ACTION_BUTTON;
    }
     if (inputs.b2) {
        return RUN;
    }
     if (inputs.b3) {
        return RAMBLIN;
    }
     if (inputs.ns_up) {
        return GO_UP;
    }
     if (inputs.ns_down) {
        return GO_DOWN;
    }
     if (inputs.ns_left) {
        return GO_LEFT;
    }
     if (inputs.ns_right) {
        return GO_RIGHT;
    }
     if (inputs.ns_center) {
        return NO_ACTION;
    }
    //******************
    
    // 1. Check your action and menu button inputs and return the corresponding action value
    
    // 2. Check for your navigation switch inputs and return the corresponding action value
    
    // If no button is pressed, just return no action value
    return NO_ACTION;
}
 



/////////////////////////
// Helper Functions:
void go_up() 
{
        Player.x = Player.px;
        Player.y =Player.py + 1;
}

void go_down() 
{
        Player.x = Player.px;
        Player.y =Player.py - 1;
}
void go_left() 
{
        Player.x = Player.px -1;
        Player.y =Player.py;
}
void go_right() 
{
        
        Player.x = Player.px + 1;
        Player.y =Player.py;
       
        
}

void talk_to_npc (int x, int y) {
                if (!Player.game_solved1 || !Player.game_solved2) {
                  Player.talked_to_npc = true;
                  char* NPC_Speech[10] = {"Hello Adventurer","We need your help","Evil buzz's have","been causing havoc", "Only you can ","defeat them", "yellow Buzz","is hydrophobic", "and Red Buzz", "is flame phobic"};
                  long_speech(NPC_Speech, 10);
                  pc.printf("in the npc function\n");

                  }else {
                    char* NPC_thanks[6] = {"You defeated","the BUZZs"," THANK YOU!!", "We are so grateful", "Here is the key", "to the door"};
                    long_speech(NPC_thanks, 6);
                 
                  Player.has_key = true;
    }
}


void tree_pick (int x, int y) {
                if (Player.lives != 3) {
                  Player.lives++;
                  char* tree_Speech[2] = {"You gained ","a life!!!"};
                  long_speech(tree_Speech, 2);
                  pc.printf("in the tree function\n");
                  add_empty_tree(x, y);  
                  }else {
                    char* tree_done[3] = {"max lives given"," come back with", "low health"};
                    long_speech(tree_done, 3);
    }
}

/////////////////////////
// Feel free to define any helper functions here for update game





/////////////////////////
// Update Game
/////////////////////////

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    Player.plives = Player.lives;
    
    MapItem* item = NULL;
    
    
    //******************
    if (action == RAMBLIN && Player.ramblin == false) {
        Player.ramblin = true;
         pc.printf("Player is ramblin: %d\n", Player.ramblin);
        speech( "you are in ", "RAMBLIN MODE");
        return FULL_DRAW;
    } else if (action == RAMBLIN && Player.ramblin == true) {
        Player.ramblin = false;
         pc.printf("Player is ramblin: %d\n", Player.ramblin);
        speech( "you have exited", "RAMBLIN MODE");
        return FULL_DRAW;
    }
    //******************


    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    
    switch(action)
    {
        case GO_UP:
            item = get_north(Player.x,Player.y);
            if (item->walkable) { 
                go_up();
            }
            if (item->type == WALL && Player.ramblin) { 
                go_up();
            }
            //TODO: Implement
            //1. Check the item north of the player
            //2. Make sure to not walk through walls
            //3. If it is not a wall, the walk up by updating player's coordinates
            break;
            
        case GO_LEFT:
            item = get_west(Player.x,Player.y);
            if (item->walkable) {
                go_left();
            }
            if (item->type == WALL && Player.ramblin) { 
                go_left();
            }
            //TODO: Implement
            break;
            
        case GO_DOWN:
            item = get_south(Player.x,Player.y);
            if (item->walkable) {
                go_down();
            }
            if (item->type == WALL && Player.ramblin) { 
                go_down();
            }
            //TODO: Implement
            break;
            
        case GO_RIGHT:
            item = get_east(Player.x,Player.y);
            if (item->walkable) {
                go_right();
            }
            if (item->type == WALL && Player.ramblin) { 
                go_right();
            }

            
            //TODO: Implement
            break;

        case RUN:
            if (Player.run == false) {
                Player.run = true;
                pc.printf("Player is running: %d\n", Player.run);
                speech( "you are in ", "RUN MODE");
                Player.speed = 20;
                return FULL_DRAW;
            } else if (Player.run == true) {
                Player.run = false;
                pc.printf("Player is running: %d\n", Player.run);
                speech( "you have exited", "RUN MODE");
                Player.speed =200;
                return FULL_DRAW;
            }
            


        case ACTION_BUTTON:

            //******************
          //*************Skull*******************
            item = get_north(Player.x,Player.y);
            if (item->type == SKULL) {
              char* speech[5] = {"You destroyed the","skull"};
              long_speech(speech,2 );
              add_dead_skull(Player.x,Player.y+1);
            return FULL_DRAW;
            }

            item = get_south(Player.x,Player.y);
            if (item->type == SKULL) {
              Player.lives --;
              char* speech[5] = {"You destroyed the","skull"};
              long_speech(speech,2 );
              add_dead_skull(Player.x,Player.y-1);
            return FULL_DRAW;
            }

            item = get_west(Player.x,Player.y);
            if (item->type == SKULL) {
              Player.lives --;
              char* speech[5] = {"You lost a life.","Don't attack from ","the side " ,"only attack from ","above or below" };
              long_speech(speech,5 );
            return FULL_DRAW;
            }

            item = get_east(Player.x,Player.y);
            if (item->type == SKULL) {
               Player.lives --;
             char* speech[5] = {"You lost a life.","Don't attack from ","the side " ,"only attack from ","above or below" };
              long_speech(speech,5 );
            return FULL_DRAW;
            }

        //*************Skull*******************
              
              item = get_north(Player.x,Player.y);
              if (item->type == NPC) {
              talk_to_npc (Player.x,Player.y+1);
                return FULL_DRAW;
              }

            item = get_south(Player.x,Player.y);
            if (item->type == DOOR) { 
                if (Player.has_key) {
                  speech("Door is unlocking","......");
                  Player.win_game = true;
                } else {
                    speech("you need the key","to unlock the door");
                }
                return FULL_DRAW;
              }

              
              item = get_south(Player.x,Player.y);
              if (item->type == NPC) {
                talk_to_npc (Player.x,Player.y-1);
                return FULL_DRAW;
              }
             

              item = get_east(Player.x,Player.y);
              if (item->type == NPC) {
                talk_to_npc (Player.x,Player.y+1);
                return FULL_DRAW;
              }
              

              item = get_west(Player.x,Player.y);  
              if (item->type == NPC) {
                talk_to_npc (Player.x-1,Player.y);
                return FULL_DRAW;
              }
              
              item = get_here(Player.x,Player.y);  
              if (item->type == CAVE && Player.talked_to_npc) {
                  speech("you are entering ","the cave");
                  pc.printf("in the cave function\n"); 
                StairsData* data = (StairsData*)item->data;
                Player.x = data->tx;
                Player.y =data->ty; 
                set_active_map(1);
                return FULL_DRAW;
              }

              if (item->type == STAIRS) {
                  speech("you are climbing","the stairs");
                  pc.printf("in the stair function\n"); 
                StairsData* data = (StairsData*)item->data;
                Player.x = data->tx;
                Player.y =data->ty; 
                set_active_map(0);
                return FULL_DRAW;
              }

                if (item->type == WATER) {
                  char* water_spell[2] = {"You have selected"," Water Spell"};
                  long_speech( water_spell,2);
                  pc.printf("in the water function\n"); 
                  Player.water =true;
                return FULL_DRAW;
              }

              if (item->type == FIRE) {
                  char* fire_spell[4] = {"You have selected"," Fire Spell","Fire destroys", "fire buzz"};
                  Player.fire =true;
                  long_speech(fire_spell,4);
                 
                return FULL_DRAW;
              }

              if (item->type == EARTH) {
                  char* earth_spell[4] = {"You have selected"," Earth Spell","Buzzs will", "be unaffected"};
                  long_speech( earth_spell,4);
                  Player.earth = true;
                return FULL_DRAW;
              }

              if (item->type == BUZZ) {
                  char* buzz_speech[4] = {"HAHA!!! ","I am BUZZ!!","You dare challenge", "me!!!!"};
                  long_speech( buzz_speech,4);
                  
                return FULL_DRAW;
              }


              //*********attack buzz *********
              item = get_east(Player.x,Player.y);  
              if (item->type == BUZZ) {
                if (Player.water) {
                  Player.lives--;
                  char* buzz_speech[4] = {"You attacked Buzz ","head on","You lost a", "life"};
                  long_speech(buzz_speech,4 );
                } else {
                  Player.lives--;
                  char* buzz_speech[4] = {"You need the  ","water spell","To defeat", "Buzz"};
                  long_speech(buzz_speech,4 );  
                }
                return FULL_DRAW;
              }

              item = get_west(Player.x,Player.y);  
              if (item->type == BUZZ) {
                if (Player.water) {
                  add_slain_buzz(12, 5);  
                  char* buzz_speech[3] = {"You attacked Buzz ","from behind","BUZZ BEGONE!!!"};
                  long_speech(buzz_speech,3 );
                   Player.game_solved1 = true;
                } else {
                  Player.lives--;
                  char* buzz_speech[4] = {"You need the  ","water spell","To defeat", "Buzz"};
                  long_speech(buzz_speech,4 );  
                }
                return FULL_DRAW;
              }






              item = get_east(Player.x,Player.y);  
              if (item->type == BUZZ2) {
                if (Player.fire) {
                  Player.lives--;
                  char* buzz_speech[4] = {"You attacked Buzz ","head on","You lost a", "life"};
                  long_speech(buzz_speech,4 );
                } else {
                  Player.lives--;
                  char* buzz_speech[4] = {"You need the  ","fire spell","To defeat", "Fire Buzz"};
                  long_speech(buzz_speech,4 );  
                }
                return FULL_DRAW;
              }

              item = get_west(Player.x,Player.y);  
              if (item->type == BUZZ2) {
                if (Player.fire) {
                  add_slain_buzz(12, 9);  
                  char* buzz_speech[3] = {"You attacked Buzz ","from behind","BUZZ BEGONE!!!"};
                  long_speech(buzz_speech,3 );
                   Player.game_solved2 = true;
                } else {
                  Player.lives--;
                  char* buzz_speech[4] = {"You need the  ","fire spell","To defeat", "Fire Buzz"};
                  long_speech(buzz_speech,4 );  
                }
                return FULL_DRAW;
              }
              

              //*******trees**********************
                item = get_north(Player.x,Player.y); 
                if (item->type == APPLETREE) {
                    tree_pick(Player.x,Player.y+1);
                    return FULL_DRAW;
                }
                item = get_south(Player.x,Player.y);
                if (item->type == APPLETREE) {
                    tree_pick(Player.x,Player.y-1);
                    return FULL_DRAW;
                } 
                item = get_east(Player.x,Player.y); 
                if (item->type == APPLETREE) {
                    tree_pick(Player.x+1,Player.y);
                    return FULL_DRAW;
                }
                item = get_west(Player.x,Player.y); 
                if (item->type == APPLETREE) {
                    tree_pick(Player.x-1,Player.y);
                    return FULL_DRAW;
                }





            //****************** menu **************

            item = get_here(Player.x, Player.y);
            if (item == NULL) {
                uLCD.text_width(1);
                uLCD.text_height(1);
                uLCD.filled_rectangle(0, 0, 127, 127, BLACK);

                
                if (Player.has_key) {
                    uLCD.text_string( "Has key- YES", 0, 2, FONT_7X8, WHITE);
                } else {
                    uLCD.text_string( "Has key- NO", 0, 2, FONT_7X8, WHITE);
                }

                if (Player.talked_to_npc) {
                    uLCD.text_string( "Talked to NPC- YES ", 0, 4, FONT_7X8, WHITE);
                } else {
                    uLCD.text_string( "Talked to NPC- NO ", 0, 4, FONT_7X8, WHITE);
                }

                if (Player.water) {
                    uLCD.text_string( "Water spell- YES", 1, 8, FONT_7X8, WHITE);
                } else {
                    uLCD.text_string( "Water spell- NO", 1, 8, FONT_7X8, WHITE);
                }

                if (Player.fire) {
                    uLCD.text_string( "Fire spell- YES", 1, 10, FONT_7X8, WHITE);
                } else {
                    uLCD.text_string( "Fire spell- NO", 1, 10, FONT_7X8, WHITE);
                }

                if (Player.earth) {
                    uLCD.text_string( "Earth spell- YES", 1, 12, FONT_7X8, WHITE);
                } else {
                    uLCD.text_string( "Earth spell- NO", 1, 12, FONT_7X8, WHITE);
                }
   

                while (1) {
                GameInputs exit = read_inputs();
                if (get_action(exit)) {
                break;
            
                }
                }
                draw_upper_status(Player.lives, Player.x, Player.y);
                return FULL_DRAW;
            }



            //***************menu*************

            //******************

            // 1. Check if near NPC, 
            //     - if so, mark the player has talked and give instructions on what to do
            //     - if the game is solved (defeated Buzz), give the player the key
            //     - return FULL_DRAW to redraw the scene


            // 2. Check if near a door
            //    - if the player has the key, you win the game
            //    - if not, show speech bubbles that the play needs to get the key 
            //     -return FULL_DRAW to redraw the scene
            


            // 3. Check if on Buzz's cave
            //    - if the player has talked to the npc, then start the speech bubble to fight buzz
            //    - set the players coordinates for the small map
            //    - and set the map to the small map
            //     -return FULL_DRAW to redraw the scene


            // 4. Check if on a stairs
            //    - if so, move the player the correct coordinates
            //    - and set the map back to the main big map
            //     -return FULL_DRAW to redraw the scene


            // 5. Check if at the right spell to end the game
            //    - if so, use speech bubbles to declare that Buzz has been defeated
            //    - and flag that the game is solved
            //     -return FULL_DRAW to redraw the scene


            // Feel free to add more functions as you make the game!

    
            break;
    }
    
    return NO_RESULT;
}




/////////////////////////
// Draw Game
/////////////////////////

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;

                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
//            if (init && i == 0 && j == 0) // Only draw the player on init
            if ( i == 0 && j == 0) // always draw the player
            {
                MapItem* cover_item = get_here(x, y);
                if (cover_item->type == BIGPLANT) {
                    draw = cover_item->draw; 
                    if (draw) draw(u, v);
                } else {
                draw_player(u, v, Player.has_key, Player.run);
                }
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                MapItem* prev2_item = get_here(px, py);
                if (init || curr_item != prev_item || curr_item != prev2_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                else if (curr_item && curr_item->type == CLEAR)
                {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    if (Player.lives != Player.plives || Player.x != Player.px || Player.y != Player.py) 
    draw_upper_status(Player.lives, Player.x, Player.y);
    draw_lower_status();
}








/////////////////////////
// Map Intialization
/////////////////////////

// Important locations for all maps
int cb_loc[2] = {5,20}; //Location of the center of the cave


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    //Initialize and sets current map to the first map
    Map* map = set_active_map(0);

    /////////////////////////
    //Initial Environmnet
    /////////////////////////
    
    //Adding random plants
    pc.printf("Adding Plants!\r\n");
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {   
        if ((i/39)%2) {
            if ((i/39)%3) {
            add_apple_tree(i % map_width(), i / map_width());    
            } else {
           add_plant(i % map_width(), i / map_width());
            }
        } else {
           add_big_plant(i % map_width(), i / map_width()); 
           add_big_plant(i % map_width()-1, i / map_width()); 
           add_big_plant(i % map_width(), i / map_width()-1); 
           add_big_plant(i % map_width()-1, i / map_width()-1); 
           
        }
        
    }

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    //Adding extra chamber borders 
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    add_door(33, 10, HORIZONTAL, 4);

    //Adding extra cave to Buzz's evil lair
    pc.printf("Add cave\r\n");
    add_cave(cb_loc[0],cb_loc[1],1,1,5,5);      //Cave is set as a 4x4 block to be bigger
    add_cave(cb_loc[0]+1,cb_loc[1],2,1,5,5);
    add_cave(cb_loc[0],cb_loc[1]+1,3,1,5,5);
    add_cave(cb_loc[0]+1,cb_loc[1]+1,4,1,5,5);

    pc.printf("Initial environment completed\r\n");

    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_npc(10, 5);  //NPC is initialized to (x,y) = 10, 5. Feel free to move him around
    add_cave(10,8,2,0,10,8);
    //***********************************
    // TODO: Implement As Needed
    //***********************************

    //Add any extra characters/items here for your project
    add_skull(8, 10);
    add_skull(15, 15);
    add_skull(16, 30);


    //Prints out map
    print_map();
}







void init_small_map()
{
    //Sets current map to the second map
    set_active_map(1);
    

    //***********************************
     /////////////////////////
    //Initial Environmnet
    /////////////////////////
    
    //Adding random plants
    

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());

    add_wall(10, 0, VERTICAL, 12);
    add_mud(4, 12, VERTICAL, 6);
    add_mud(8, 12, VERTICAL, 6);
    add_mud(12, 12, VERTICAL, 6);
    
    

    pc.printf("Initial small map environment completed\r\n");

    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_buzz(12, 5);  //NPC is initialized to (x,y) = 10, 5. Feel free to move him around
    add_buzz2(12, 9);
    add_earth(2, 15);
    add_fire(5, 15);
    add_water(10, 15);
    //***********************************
    // TODO: Implement As Needed
    //***********************************

    //Add any extra characters/items here for your project




    //Prints out map
    print_map();
    //***********************************

    // 1. Add walls to the smaller map.
    //    Set the dimensions to be 16x16  <-- you may change to your liking, but must be smaller than the main map
    //    Hint: See how walls are initialized in the main map
    //
    // 2. Add your three spells at different locations
    //
    // 3. Add Evil Buzz at the center of the map


    // You may add any extra characters/items here for your project


    // Add stairs back to main (map 0)
    add_stairs(4, 6, 0, cb_loc[0], cb_loc[1]);
    
}


/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("start\r\n");

   // uLCD.filled_rectangle(64, 64, 74, 74, RED); //DELETE OR COMMENT THIS LINE  <-- It is a temporary indicator that your LCD is working before you implement your code
    //<------ DELETE THIS LINE

    // Initialize the maps
    uLCD.filled_rectangle(0, 0, 127, 127, BLACK);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.text_string( "WELCOME", 1, 0, FONT_7X8, RED);
    

    uLCD.text_width(1);
    uLCD.text_height(2);
    uLCD.text_string( "  To The Legend ", 0, 2, FONT_7X8, WHITE);
    uLCD.text_string( " Of Burdell ", 3, 4, FONT_7X8, WHITE);


    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.text_string( "   Press Button ", 0, 11, FONT_7X8, GREEN);
    uLCD.text_string( "  To Begin ", 3, 14, FONT_7X8, GREEN);
   

    while (1) {
        GameInputs exit = read_inputs();
        if (get_action(exit)) {
            break;
            
        }
    }
    uLCD.filled_rectangle(0, 0, 127, 127, BLACK);
    maps_init();
    init_main_map();
    init_small_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;
    Player.has_key = false;
    Player.game_solved1 = false;
    Player.game_solved2 = false;
    Player.talked_to_npc = false;
    Player.ramblin = false;
    Player.run = false;
    Player.lives =3;
    Player.water =false;
    Player.fire = false;
    Player.earth = false;
    bool lost = false;
    bool game_over = true;
    Player.speed = 200;
    int lose = 0;
    
    // Initial drawing
    
    
    draw_game(true);
    // Main game loop
    while(1)
    {

        speaker.period(1.0/293.66);
        
        ////////////////////////////////
        // Timer to measure game update speed
        Timer t; t.start();

        // Actually do the game update:
        // 1. Read inputs        

        // 2. Determine action (get_action)       

        // 3. Update game (update_game)

        GameInputs input = read_inputs();
        int main_action = get_action(input);
        int result =  update_game(main_action); // Set this variable "result" for the resulting state after update game

        // 3b. Check for game over based on update game result
        
        if (Player.win_game == true ) {
            game_over =true;
            break;
        }


        if (Player.lives == 0 ) {
            lose++; 
            main_action = get_action(input);
            if (lose == 1){
                uLCD.filled_rectangle(0, 0, 127, 127, BLACK);
                uLCD.text_width(1);
                uLCD.text_height(2);
                uLCD.text_string( "Action button", 2, 1, FONT_7X8, GREEN);
                 uLCD.text_string( "to respawn ", 4, 3, FONT_7X8, GREEN);
                uLCD.text_string( "Next button ", 2, 5, FONT_7X8, GREEN); 
                uLCD.text_string( "to end game", 4, 7, FONT_7X8, GREEN); 
                int hold = 1;
                while (hold == 1 || (main_action!= ACTION_BUTTON && main_action != RUN)) {
                hold--;
                input = read_inputs();
                main_action = get_action(input);
                }
            }
            if (main_action == RUN || lose > 1) {
            game_over = false;
            lost = true;
            break;
            }
            if (main_action == ACTION_BUTTON) {
                uLCD.filled_rectangle(0, 0, 127, 127, BLACK);

    
         // Initialize game state
            set_active_map(0);
            Player.x = Player.y = 5;
            Player.has_key = false;
            Player.talked_to_npc = false;
            Player.ramblin = false;
            Player.run = false;
            Player.game_solved1 = false;
            Player.game_solved2 = false;
            Player.lives = 2;
            Player.water =false;
            Player.fire = false;
            Player.earth = false;
            lost = false;
            game_over = true;
            Player.speed = 200;
            lose = 1;
    
            // Initial drawing
    
    
            draw_game(true);

            }
        }
        // make gameover screen
        ////////////////////////////////

        
        
        
       

        

        // 4. Draw screen to uLCD
        bool full_draw = false;
        if (result == FULL_DRAW) full_draw = true;
        draw_game(full_draw);
        

        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < Player.speed) wait_ms(Player.speed - dt);
    }
    if (game_over) {
    uLCD.filled_rectangle(0, 0, 127, 127, BLACK);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.text_string( "YOU WIN!!!", 1, 3, FONT_7X8, GREEN);
    uLCD.text_width(1);
    uLCD.text_string( "Quest completed :)", 0, 5, FONT_7X8, GREEN);
    } else if (lost) {
       uLCD.filled_rectangle(0, 0, 127, 127, BLACK);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.text_string( "GAME OVER", 0, 3, FONT_7X8, GREEN);
    uLCD.text_width(1);
    uLCD.text_string( " ALL LIVES LOST", 0, 5, FONT_7X8, GREEN); 
    }
    //DELETE THIS LINE  -----> 


}




/////////////////////////////
//Advanced Features
/////////////////////////////

// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
    return;
}

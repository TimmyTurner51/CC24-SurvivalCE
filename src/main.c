////////////////////////////////////////
// SurvivalCE Version DEV_0.00
// Author: Michael0x18 and TimmyTurner62
// License: Gnu GPLv2?
// Description: Cemetech CC24 submission.
////////////////////////////////////////

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

//Include the graphics routines from the
// graphx c lib. These are the same as in ICE.
#include <graphx.h>

#include <keypadc.h>
#include <keypadc.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "gfx/gfx.h"

    int8_t x;
    int8_t y;

struct playerdata{
    int24_t score;//The player's score
    int8_t health;//The player's health on a scale from 1-6.
    int16_t coins;//The player's cash.
    int8_t inventory[7][5];//The player's inventory, used for storing items.
} player;
//This means you can type player.score=5
//or player.health--

/* Other available headers: stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h */

/* uint8_t is an unsigned integer that can range from 0-255. */
/* It performs faster than just an int, so try to use it (or int8_t) when possible */

/* Put function prototypes here */
void printText(const char *text, uint8_t x, uint8_t y);

//  Runs the introduction
//  void        run_intro       (void)
//  ^the return type. It doesn't return anything.
//  void        run_intro       (void)
//               ^ The function name
//  void        run_intro       (void)
//                               ^ no arguments,
// which is the same as empty parentheses: ()
//
// Prototypes are not strictly needed, but they're a good
// idea. The c compiler scans from the top to the bottom,
// so if it runs into your function before your prototype,
// it's like this:
// my_function(1,2,"hi");
// What does my_function return? What arguments does it take?
// It can make a guess, but it likely won't be correct.
// Here, you tell it with the prototype, "my_function doesn't return anything",
// it takes two integers and a string as arguments.
// If you don't make prototypes, you definition must be before where you use it.
void run_intro(void);

void draw_splash(void);

void text_box(void);

void mainloop(void);

/* Put all your code here */
void main(void){
    //Put the screen in 256 color mode instead of 16 color.
    //Same as ICE's begin. (det(0), I think).
    gfx_Begin();
    //Run the introduction
    run_intro();
    //Display Splash screen.
    draw_splash();

    mainloop();
    //Restore the screen.
    gfx_End();
}

void mainloop() {
    //ALL CODE FOR ACTUAL GAME HERE
/*
BTW this is a multiline comment
1) Check for saved state appvar
2) If not present, initialize it
3) Otherwise, load state and continue

Mechanics:
store rooms in appvar:
1:
    1:
    binary representation
    2:
2: etc

Compress? Keep a working state?
I need to find more time to work on this...





*/



  

	
}

void draw_splash(void){
  


    while(!kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyDel)){
        

        for (x = 0; x < 20; x++) {
            for (y = 0; y < 15; y++) {

                /* green colored rectangle */
                gfx_Sprite_NoClip(grass, x * 16, y * 16);


            }

        }


    }
}



//Here's the actual code for run_intro;
void run_intro(void) {

    //set transparent color to white so that we can draw the maps...

    gfx_SetTransparentColor(255);
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 15; y++) {

            /* green colored rectangle */
            gfx_Sprite_NoClip(grass, x * 16, y * 16);


        }

    }

    gfx_SetTextFGColor(253);

    //Check for all required appvars...
    ti_CloseAll();
    //Open SurvivalCE savestate appvar if it exists. If it doesn't, it'll make it
    ti_Open("SrvCEss", "w");


    gfx_SetColor(115);
 
    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("Your father was a senior member of the", 24, 195);
    gfx_PrintStringXY("highly exclusive and extremely", 24, 210);
 /* Need to change later to wait for the [2nd] key to be pressed */
    while (!os_GetCSC()); 

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("prestigious Hunter's Club.", 24, 195);
    gfx_PrintStringXY("His collection of rare pelts and trophies", 24, 210);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("was the envy of everyone, especially", 24, 195);
    gfx_PrintStringXY("your uncle Fred.", 24, 210);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("One day, your father went hunting with", 24, 195);
    gfx_PrintStringXY("Fred and vanished. Fred said that he", 24, 210);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("was finally killed by one of the beasts", 24, 195);
    gfx_PrintStringXY("he pursued, and everyone believed", 24, 210);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("him. However, you think your uncle", 24, 195);
    gfx_PrintStringXY("actually killed your father so that he", 24, 210);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("could hold the title of Greatest Hunter.", 24, 195);
    gfx_PrintStringXY("To get revenge, you decide to pursue the", 24, 210);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("title yourself...", 24, 195);
    while (!os_GetCSC());

    gfx_FillRectangle(20, 190, 280, 40);
    gfx_PrintStringXY("And so the saga begins...", 24, 195);
    while (!os_GetCSC());


    return;
    
}


/* Draw text on the homescreen at the given X/Y cursor location */
void printText(const char *text, uint8_t xpos, uint8_t ypos){
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}




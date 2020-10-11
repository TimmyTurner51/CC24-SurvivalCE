////////////////////////////////////////
// SurvivalCE Version DEV_0.00
// Author: Michael0x18 and TimmyTurner62
// License: Gnu GPLv2?
// Description: Cemetech CC24 submission.
////////////////////////////////////////

//Note: If you want, you can put the code from player.txt into here, replacing the player struct.

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



/* Put all your code here */
void main(void){
    //Put the screen in 256 color mode instead of 16 color.
    //Same as ICE's begin. (det(0), I think).
    gfx_Begin();
    //Run the introduction
    run_intro();
    //Display Splash screen.
    draw_splash();
    //Restore the screen.
    gfx_End();
}

void draw_splash(void){
    //int i=0;
    //This is actually a green color
    gfx_FillScreen(OS_COLOR_BLACK);
    while(!kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyDel)){
        //Draw whatever animations go here.
    }
}

//Here's the actual code for run_intro;
void run_intro(void){
    //Make screen black
    gfx_FillScreen(00);
    gfx_SetTextFGColor(253);
    //Wait for a moment
    delay(1000);

    
    //I have removed your code momentarialy to test my version. I will post the original code that was here before this in the code notes txt file...
    
    //I always backup the files. Your code is backed up btw. :P
    
    //Make a Pokemon-style text box... still messy-looking. Let's hope it works...
    gfx_SetColor(227);
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("Your father was a senior member of the", 20, 122);
    gfx_PrintStringXY("highly exclusive and extremely", 20, 132);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("prestigious Hunter's Club.", 20, 122);
    gfx_PrintStringXY("His collection of rare pelts and trophies", 20, 132);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("was the envy of everyone, especially your", 20, 122);
    gfx_PrintStringXY("uncle Fred.", 20, 132);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("One day, your father went hunting with Fred", 20, 122);
    gfx_PrintStringXY("and vanished. Fred said that he was finally", 20, 132);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("killed by one of the beasts he pursued,", 20, 122);
    gfx_PrintStringXY("and everyone believed him.", 20, 132);
       while (!os_GetCSC());
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("However, you think your uncle actually", 20, 122);
    gfx_PrintStringXY("killed your father so that he could hold", 20, 132);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("the title of Greatest Hunter.", 20, 122);
    gfx_PrintStringXY("To get revenge, you decide to pursue the", 20, 132);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("title yourself...", 20, 122);
       while (!os_GetCSC());
    gfx_FillRectangle(0, 120, 280, 20);
    gfx_PrintStringXY("And so the saga begins...",20,122);
       while (!os_GetCSC());
 
    return;
    
}


/* Draw text on the homescreen at the given X/Y cursor location */
void printText(const char *text, uint8_t xpos, uint8_t ypos){
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}



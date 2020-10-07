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



/* Put all your code here */
void main(void){
    //Put the screen in 256 color mode instead of 16 color.
    //Same as ICE's begin. (det(0), I think).
    gfx_Begin();
    //Run the introduction
    run_intro();
    //Restore the screen.
    gfx_End();
}

//Here's the actual code for run_intro;
//run_intro prints messages to the screen with a 1 second delay between each one.
//The user can press a key at any time to skip to the end.
void run_intro(void){
    //Make screen black
    gfx_FillScreen(00);
    gfx_SetTextFGColor(253);
    //Wait for a moment
    delay(1000);
    //The number of messages to print during the intro.
    const int8_t numMessages=15;
    //Array (fixed length list) stores messages to print.
    //Each message has a maximum length of 150 characters
    //You can think of a string as just a list of characters.
    const char messages[numMessages][150]={
     "Your father was a senior member of the",
     "highly exclusive and extremely",
     "prestigious Hunter's Club.",
     "His collection of rare pelts and trophies",
     "was the envy of everyone, especially your",
     "uncle Fred.",
     "One day, your father went hunting with Fred",
     "and vanished. Fred said that he was finally",
     "killed by one of the beasts he pursued,",
     "and everyone believed him.",
     "However, you think your uncle actually",
     "killed your father so that he could hold",
     "the title of Greatest Hunter.",
     "To get revenge, you decide to pursue the",
     "title yourself..."
    };
    //Print the messages one by one
    for(int8_t i =0; i<numMessages;i++){
        gfx_PrintStringXY(messages[i],0,10*i);
        //Make a delay so the text can be read.
        //It's broken up so that it feels responsive.
        //If I just said, delay(1000) and then checked for the keypress,
        //it might not pick it up. If it did, it could be up to a second of delay 
        //before the intro gets skipped.
        for(int8_t j = 0; j < 10; j++){
           if(os_GetCSC())return;
           delay(100);
        }

    }
    gfx_PrintStringXY("And so the saga begins...",20,180);
    for(int8_t j = 0; j < 10; j++){
           if(os_GetCSC())return;
           delay(100);
    }
    return;
}


/* Draw text on the homescreen at the given X/Y cursor location */
void printText(const char *text, uint8_t xpos, uint8_t ypos){
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}



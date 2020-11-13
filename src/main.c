////////////////////////////////////////
// SurvivalCE Version DEV_0.22
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

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "gfx/gfx.h"

#define DIR_DOWN 1
#define DIR_UP 2
#define DIR_LEFT 3
#define DIR_RIGHT 4

    //I know, so many static vars... truth is, they're used sometimes A LOT by pretty much every function here!...
    static uint24_t x;
    static uint24_t y;
    static uint24_t OldX;
    static uint24_t OldY;
    static uint24_t health;
    static uint24_t startX;
    static uint24_t dir;
    static uint24_t redraw;
    static uint24_t i;
    static uint16_t option;
    static uint24_t playerX;
    static uint24_t playerY;
    static uint24_t movable;
    static uint24_t xa;
    static uint24_t xb;
    static uint24_t roomX;
    static uint24_t roomY;
    static uint24_t room;
    //buildings[0] = count on screen, buildings[1] = building 1 pos in map data, building[2] = building 2 pos in map data, and so on...
    static uint24_t buildings[21] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    static uint24_t objectiveNum;
    static uint24_t chapterNum;
    static ti_var_t appvar;
    static char wholeMap[(20 * 14) * (15 * 14)];
    static gfx_sprite_t* sprites[16] = { dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth, door, wall_brick, roof, sword };
    //gamedata = {player health, current room player is in, roomX, roomY, playerX, playerY, player dir, inventory slot 1, inv. 2, inv. 3, inv 4, inv5, objective #, player pos in map, chicken count, deer count, elephant count, lion count, tiger count, hippo count, gorilla count, monkey count, rhino count, scorpion count, python count, lion king hp, scorpion queen hp, emperor kong hp, Fred’s hp};
    //gamedata size is 29. There are 11 animals (4 bosses).
    static uint24_t gamedata[29] = { 9, 1, 1, 1, 160, 144, 2, 1, 1, 1, 1, 1, 1, 2530, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    //each non-player mob has a max limit of 60 positions in the list
    //20 is max count allowed for mobs, with hp, posX, posY, and dir (left or right). Left dir is 0, right dir is 1.
    static uint24_t animals[180] = { 0 };
    static char* objectiveTitles[3] = { "Go to the Weapons Center", "Purchase a knife","Go stab a duck" };
    static char* chapterTitles[3] = { "Hunt Training", "The adventure","Return of Fred" };

    //CREDITS: (required for CC24, it's the right thing to do)
    //Map Engine by TimmyTurner62 at cemetech.net. Thanks to Michael0x18 for constant help with code.
    //Credits to pretty much everyone on cemetech.net, since there's too many helpful people who've helped all throughout!


/* Other available headers: stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h */

    void printText(const char *text, uint8_t x, uint8_t y);


    void run_intro(void);
    void draw_splash(void);
    void text_box(void);
    void play(void);
    void help(void);
    void quit(void);
    void drawRoom(void);
    void DrawPlayer(void);
    void dispChaptAndObj(void);
    void enterBuilding(uint24_t buildingnum);
       
    gfx_TempSprite(background, 16, 16);

void main(void){
    gfx_Begin();
    //set the palette...
    gfx_SetPalette(xlibc, sizeof_xlibc, 0);
    // Always have to change transparent value any time a new sprite is added and converted :/
    gfx_SetTransparentColor(148);
    //Go to the main menu    
    run_intro();
    //Display Splash screen.
    //draw_splash();
    //Restore the screen.
    gfx_End();
}


void run_intro(void) {

    gfx_SetDrawBuffer();
    /* main menu */
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 15; y++) {
            gfx_Sprite(grass, x * 16, y * 16);
        }
    }
    /* buttons */
    for (OldY = 140; OldY < 200; OldY += 20) {
        for (OldX = 60; OldX < 244; OldX += 16) {
            gfx_Sprite(wood, OldX, OldY);
        }
    }
    gfx_SetTextFGColor(254);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("SurvivalCE", 20, 20);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY("For Cemetech Contest #24", 2, 230);
    gfx_PrintStringXY("v1.3.0", 280, 230);
    gfx_BlitBuffer();
    gfx_SetTextFGColor(80);
    redraw = 1;
    y = 140;
    i = y;
    option = 0;
    while (option == 0) {
        gfx_SetColor(140);
        kb_Scan();
        if (redraw == 1) {
            redraw = 0;
            /* redraw only the one button that needs it */
            for (OldX = 60; OldX < 244; OldX += 16) {
                gfx_Sprite(wood, OldX, i);
            }
            /* button text */
            gfx_PrintStringXY("Play", 148, 142);
            gfx_PrintStringXY("Help  & Options", 112, 162);
            gfx_PrintStringXY("Quit", 148, 182);
            gfx_Rectangle(60, y, 192, 16);
            gfx_Rectangle(61, y + 1, 190, 14);
            gfx_BlitBuffer();
        }
        i = y;
        if (kb_IsDown(kb_KeyUp) && y > 140) {
            delay(150);
            y -= 20;
        }
        if (kb_IsDown(kb_KeyDown) && y < 180) {
            delay(150);
            y += 20;
        }
        if (i != y)                                 redraw = 1;
        if (kb_IsDown(kb_Key2nd))                   option = 1;
    }
    if (y == 140) play();
    if (y == 160) help();
    return;
}

void play(void) {
        
        char * msgs_1[9]={"Your father was a senior member of the","prestigious Hunter's Club.","was the envy of everyone, especially","One day, your father went hunting with","was finally killed by one of the","...I think my uncle actually","could hold the title of Greatest Hunter.","the title myself...","And so the saga begins..."};
		char * msgs_2[9]={"highly exclusive and extremely","His collection of rare pelts and trophies","me, your uncle Fred.","me and vanished. I think that he","beasts he pursued...","killed my father so that he","To get revenge, I've decided to pursue"," "," "};

        gfx_SetDrawBuffer();

        //Check for all required appvars...
        ti_CloseAll();
        appvar = ti_Open("SrvMap00", "r");

        if (!appvar) {
           
            gfx_SetTextFGColor(254);
            gfx_FillScreen(200);
            gfx_SetTextScale(2, 2);
            gfx_PrintStringXY("ERROR!", 10, 10);
            gfx_PrintStringXY("The Map File has been renamed or is", 10, 30);
            gfx_PrintStringXY("missing!", 10, 45);
            gfx_SetTextScale(1, 1);
            gfx_PrintStringXY("The map file is required to play this game!", 10, 100);
            gfx_PrintStringXY("To get the map file, visit www.cemetech.net,", 10, 110);
            gfx_PrintStringXY("or get the SrvMap00.8xp file here:", 10, 120);
            gfx_PrintStringXY("https://github.com/TimmyTurner51/CC24-SurvivalCE/tree/main/bin", 10, 130);
            gfx_SetTextFGColor(80);
            ti_CloseAll();
            gfx_BlitBuffer();
            while (!os_GetCSC());
            return;

        }else{
            ti_CloseAll();
            appvar = ti_Open("SrvMap00", "r");
            ti_Read(wholeMap, ti_GetSize(appvar), 1, appvar);

            ti_CloseAll();
            /* don't try this, it's too buggy
            for (i = 0; i < sizeof(wholeMap); i++)
            
                if (wholeMap[i] == 12) {
                    buildings[0] = buildings[0] + 1;
                    test = buildings[0];
                    buildings[test] = i;
                }
            }
            */
            
            drawRoom();
        }


            ti_CloseAll();
            appvar = ti_Open("SrvCEss", "r");


            if (!appvar) {

            ti_CloseAll();
            appvar = ti_Open("SrvCEss", "w");
            ti_Write(gamedata, sizeof(gamedata), 1, appvar);
            ti_SetArchiveStatus(1, appvar);
            ti_CloseAll();
            gfx_SetColor(80);
            gfx_SetDrawBuffer();
            for (xa = 32; xa < 180; xa += 2) {
                for (x = 0; x < 20; x++) {
                    for (y = 0; y < 15; y++) {
                        gfx_Sprite_NoClip(wood, x * 16, y * 16);
                    }
                }
                gfx_TransparentSprite_NoClip(f, 320-xa, 120);
                gfx_BlitBuffer();
            }

			delay(300);
			xa = 0;
            xb = 0;
		 for(y = 0; y < 5; y++){
		  	    gfx_FillRectangle(20, 190, 280, 40);
        		gfx_PrintStringXY(msgs_1[y], 24, 195);
        		gfx_PrintStringXY(msgs_2[y], 24, 210);
                gfx_BlitBuffer();
        		    /* Need to change later to wait for the [2nd] key to be pressed */
           	    while (!os_GetCSC());
		  }
          //Make a cool animation...for the next intro scene
			delay(300);
          for (x = 0; x < 10; x++) {
                    for (y = 0; y < 15; y++) {
                        gfx_Sprite_NoClip(wall_brick, x * 16, y * 16);
                        gfx_Sprite_NoClip(wall_brick, 304 - (x * 16), 224 - (y * 16));
                        gfx_BlitBuffer();
                        delay(10);
                    }
                }
            gfx_ScaledTransparentSprite_NoClip(player_dirF_1, 144, 98, 2, 2);
		 for(y = 5; y < 9; y++){
		  	    gfx_FillRectangle(20, 190, 280, 40);
        		gfx_PrintStringXY(msgs_1[y], 24, 195);
        		gfx_PrintStringXY(msgs_2[y], 24, 210);
                gfx_BlitBuffer();
           	    while (!os_GetCSC());
		  }
          
            gfx_SetColor(0);
                for (y = 0; y < 15; y++) {
                    for (x = 0; x < 10; x++) {
                        gfx_FillRectangle(x * 16, y * 16, 16, 16);
                        gfx_FillRectangle(304 - (x * 16), 224 - (y * 16), 16, 16);
                        gfx_BlitBuffer();
                        delay(10);
                    }
                }

            health = gamedata[0];
            room = gamedata[1];
            roomX = gamedata[2];
            roomY = gamedata[3];
            playerX = gamedata[4];
            playerY = gamedata[5];
            dir = gamedata[6];
            objectiveNum = gamedata[12];

            if (!(objectiveNum % 5)) {
                dispChaptAndObj();
            }
            draw_splash();

            } else {

                ti_Read(gamedata, ti_GetSize(appvar), 1, appvar);
                health = gamedata[0];
                room = gamedata[1];
                roomX = gamedata[2];
                roomY = gamedata[3];
                playerX = gamedata[4];
                playerY = gamedata[5];
                dir = gamedata[6];
                objectiveNum = gamedata[12];

                ti_CloseAll();
                dispChaptAndObj();
                draw_splash();

            }



}

void dispChaptAndObj(void) {
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 15; y++) {
            gfx_Sprite_NoClip(grass, x * 16, y * 16);
        }
    }
    delay(100);
    gfx_SetColor(100);
    gfx_FillRectangle(50, 100, 220, 50);
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Chapter ", 94, 112);
    gfx_SetTextXY(214, 112);
    chapterNum = (objectiveNum % 5) + 1;
    gfx_PrintInt(chapterNum - 1, 1);
    gfx_SetTextScale(1, 1);
    gfx_FillRectangle(50, 180, 220, 40);
    gfx_PrintStringXY(chapterTitles[chapterNum - 1], 160 - ((strlen(chapterTitles[chapterNum - 1]) / 2) * 7), 138);
    gfx_PrintStringXY("Objective:", 54, 184);
    gfx_PrintStringXY(objectiveTitles[objectiveNum], 54, 194);
    gfx_BlitBuffer();
    while (!os_GetCSC());
}

void drawRoom(void) {
    int test;
    redraw = 0;
    i = room - 1;
    for (y = 0; y < 15; y++) {
        for (x = 0; x < 20; x++) {
            gfx_Sprite(sprites[wholeMap[i]], x * 16, y * 16);
            /* don't try this, it's too buggy...
            if (wholeMap[i] == 12) {
                buildings[0] = buildings[0] + 1;
                test = buildings[0];
                buildings[test] = i;
            }
            */
            
            i++;
        }
        i += 20 * 13;
    }
}

void enterBuilding(uint24_t buildingNum) {

    redraw = 0;
    i = room - 1;
    for (y = 0; y < 15; y++) {
        for (x = 0; x < 20; x++) {
            gfx_Sprite(sprites[wholeMap[i]], x * 16, y * 16);
            
            i++;
        }
        i += 20 * 13;
    }
        

}

void draw_splash(void) {
    OldX = playerX;
    OldY = playerY;

    gfx_SetDrawBuffer();
    gfx_SetColor(0);
    drawRoom();

    gfx_GetSprite(background, playerX, playerY);
    DrawPlayer();

    gfx_BlitBuffer();
    
    while (!kb_IsDown(kb_KeyClear)) {
        kb_Scan();


            gfx_FillRectangle(18, 18, 100, 14);
            gfx_SetTextXY(20, 20);
            gfx_PrintInt(gamedata[13],1);


        movable = 1;
        
        
        if (kb_IsDown(kb_KeyUp) && (dir != DIR_UP)) {
            movable = 0;
            dir = DIR_UP;
        }
        if (kb_IsDown(kb_KeyDown) && (dir != DIR_DOWN)) {
            movable = 0;
            dir = DIR_DOWN;
        }
        if (kb_IsDown(kb_KeyLeft) && (dir != DIR_LEFT)) {
            movable = 0;
            dir = DIR_LEFT;
        }
        if (kb_IsDown(kb_KeyRight) && (dir != DIR_RIGHT)) {
            movable = 0;
            dir = DIR_RIGHT;
        }
        
        
        if (movable > 0) {
            if (kb_IsDown(kb_KeyUp) && (playerY > 0) && (wholeMap[gamedata[13] - 280] != 7) && (wholeMap[gamedata[13] - 280] != 13)) {
                dir = DIR_UP;
                DrawPlayer();
                    if (wholeMap[gamedata[13] - 280] == 12) {
                        /* don't try this, it's too buggy.
                        for (xa = 1; xa < 20; xa++) {
                            if (buildings[xa] == gamedata[13])
                            xb = xa;
                        }
                        enterBuilding(xb);
                        */
                        gfx_FillRectangle(20, 190, 280, 40);
                        gfx_PrintStringXY("Hmm, I can't go in here...", 22, 192);
                        gfx_BlitBuffer();
                        delay(1000);
                        drawRoom();
                        DrawPlayer();
                        gfx_BlitBuffer();
                    }else{
                        if ((playerY % 16 == 0) && (playerY != 0) && (playerY == OldY)) gamedata[13] -= 280;
                        playerY--;
                    }

            }
            if (kb_IsDown(kb_KeyDown) && (wholeMap[gamedata[13] + 280] != 7) && (wholeMap[gamedata[13] + 280] != 13)) {
                dir = DIR_DOWN;
                if ((playerY % 16 == 0) && (playerY == OldY)) gamedata[13] += 280;
                playerY++;
                DrawPlayer();
            }
            if (kb_IsDown(kb_KeyLeft) && (playerX > 0) && (wholeMap[gamedata[13] - 1] != 7) && (wholeMap[gamedata[13] - 1] != 13)) {
                dir = DIR_LEFT;
                if ((playerX % 16 == 0) && (playerX != 0) && (playerX == OldX)) gamedata[13]--;
                playerX--;
                DrawPlayer();
            }
            if (kb_IsDown(kb_KeyRight) && (wholeMap[gamedata[13]] != 7) && (wholeMap[gamedata[13]] != 13)) {
                dir = DIR_RIGHT;
                if ((playerX % 16 == 0) && (playerX == OldX)) gamedata[13]++;
                playerX++;
                DrawPlayer();
            }


            if ((playerX < 1) && (roomX > 1)) {
            redraw = 1;
                for (playerX = 0; playerX < 304; playerX++) {
                    if (!(playerX % 16)) {
                        drawRoom();
                        DrawPlayer();
                        room--;
                        xa--;
                        gfx_BlitBuffer();
                    }
                }
                room--;
                //xa--;
                gamedata[13] = gamedata[13] - 1;
                drawRoom();
                DrawPlayer();
                gfx_BlitBuffer();
                roomX--;
            }
            if ((playerX > 304) && (roomX < 14)) {
                redraw = 1;
                for (playerX = 304; playerX > 1; playerX--) {
                    if (!(playerX % 16)) {
                        drawRoom();
                        DrawPlayer();
                        room++;
                        xa++;
                        gfx_BlitBuffer();
                    }
                }
                room++;
                //xa++;
                gamedata[13] = gamedata[13] + 1;
                drawRoom();
                DrawPlayer();
                gfx_BlitBuffer();
                roomX++;
            }
            if ((playerY < 1) && (roomY > 1)) {
                redraw = 1;
                for (playerY = 0; playerY < 224; playerY++) {
                    if (!(playerY % 16)) {
                        drawRoom();
                        DrawPlayer();
                        room -= 20*14;
                        xa -= 20*14;
                        gfx_BlitBuffer();
                    }
                }
                room -= 280;
                //xa -= 280;
                drawRoom();
                DrawPlayer();
                gfx_BlitBuffer();
                roomY--;
            }
            if ((playerY > 224) && (roomY < 14)) {
                redraw = 1;
                for (playerY = 224; playerY > 1; playerY--) {
                    if (!(playerY % 16)) {
                        drawRoom();
                        DrawPlayer();
                        room += 280;
                        xa += 280;
                        gfx_BlitBuffer();
                    }
                }
                room += 280;
                //xa += 280;
                drawRoom();
                DrawPlayer();
                gfx_BlitBuffer();
                roomY++;
            }
        }

        for (x = 0; x < health; x++) {
            gfx_ScaledTransparentSprite_NoClip(heart, 200 + (x * 13), 222, 2, 2);
        }

        if kb_IsDown(kb_KeyStat) {
   
                gfx_SetColor(40);
                for (xa = 1; xa < 30; xa++) {
                    drawRoom();
                    DrawPlayer();
                    if (xa < 18) gfx_FillRectangle(0, 0, 320, xa);
                    if (xa > 17) gfx_FillRectangle(0, 0, 320, 18);          //Need this line! Otherwise, the rectangle won't show when we redraw the room (that makes it smooth)!!!
                    gfx_FillRectangle(0, 241-xa, 320, xa);
                    for (xb = 0; xb < 30; xb++) {
                        if (!kb_IsDown(kb_KeyStat)) drawRoom();
                    } 
                    for (x = 0; x < health; x++) {
                        gfx_ScaledTransparentSprite_NoClip(heart, 200 + (x * 13), 222 - xa, 2, 2);
                    }
                    gfx_BlitBuffer();
                }
                gfx_PrintStringXY("Objective:", 4, 4);
                gfx_PrintStringXY(objectiveTitles[objectiveNum], 82, 4);
                
                //inventory hotbar
                gfx_Sprite_NoClip(inventory_box, 117 - 25, 213);
                gfx_Sprite_NoClip(inventory_box, 117, 213);
                gfx_Sprite_NoClip(inventory_box, 117 + 25, 213);
                gfx_Sprite_NoClip(inventory_box, 117 + 50, 213);
                gfx_Sprite_NoClip(inventory_box, 117 + 75, 213);
                for (x = 0; x < health; x++) {
                    gfx_ScaledTransparentSprite_NoClip(heart, 200 + (x * 13), 194, 2, 2);
                }
                gfx_BlitBuffer();
                DrawPlayer();
                while (kb_IsDown(kb_KeyStat)){
                    kb_Scan();
                };
                for (xa = 1; xa < 30; xa++) {
                    drawRoom();
                    kb_Scan();
                    if kb_IsDown(kb_KeyUp) {
                        dir = DIR_UP;
                        playerY -= 2;
                        DrawPlayer();
                    }
                    if kb_IsDown(kb_KeyDown) {
                        dir = DIR_DOWN;
                        playerY += 2;
                        DrawPlayer();
                    }
                    if kb_IsDown(kb_KeyLeft) {
                        dir = DIR_LEFT;
                        playerX -= 2;
                        DrawPlayer();
                    }
                    if kb_IsDown(kb_KeyRight) {
                        dir = DIR_RIGHT;
                        playerX += 2;
                        DrawPlayer();
                    }
                    DrawPlayer();
                    if (xa < 18) gfx_FillRectangle(0, 0, 320, 19 - xa);
                    gfx_FillRectangle(0, 210 + xa, 320, 30 - xa);
                    for (x = 0; x < health; x++) {
                        gfx_ScaledTransparentSprite_NoClip(heart, 200 + x*13, 193 + xa, 2, 2);
                    }
                    gfx_BlitBuffer();
                }
                drawRoom();
                DrawPlayer();
        }


             gfx_BlitBuffer();

        }

        gamedata[0] = health;
        gamedata[1] = room;
        gamedata[2] = roomX;
        gamedata[3] = roomY;
        gamedata[4] = playerX;
        gamedata[5] = playerY;
        gamedata[6] = dir;
        gamedata[12] = objectiveNum;
        ti_CloseAll();
        appvar = ti_Open("SrvCEss", "w");
        ti_Write(gamedata, sizeof(gamedata), 1, appvar);
        ti_CloseAll();
        

    }


void DrawPlayer(void) {

    gfx_Sprite(background, OldX, OldY);
    gfx_GetSprite(background, playerX, playerY);
    if (dir == 1) gfx_TransparentSprite_NoClip(player_dirF_1, playerX, playerY);
    if (dir == 2) gfx_TransparentSprite_NoClip(player_dirB_1, playerX, playerY);
    if (dir == 3) gfx_TransparentSprite_NoClip(player_dirL_1, playerX, playerY);
    if (dir == 4) gfx_TransparentSprite_NoClip(player_dirR_1, playerX, playerY);

    OldX = playerX;
    OldY = playerY;

}

/* Draw text on the homescreen at the given X/Y cursor location */
void printText(const char *text, uint8_t xpos, uint8_t ypos){
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}


void help(void) {
    
    /* help and options menu */
    delay(200);
    gfx_SetDrawBuffer();
    gfx_SetTextFGColor(80);
    for (x = 0; x < 20; x++) {
        for (y = 0; y < 15; y++) {
            gfx_Sprite(grass, x * 16, y * 16);
        }
    }
    /* buttons */
    for (OldY = 140; OldY < 200; OldY += 20) {
        for (OldX = 60; OldX < 244; OldX += 16) {
            gfx_Sprite(wood, OldX, OldY);
        }
    }
    gfx_SetTextScale(2, 2);
    gfx_PrintStringXY("Help & Options:", 30, 20);
    gfx_SetTextScale(1, 1);
    gfx_BlitBuffer();
    redraw = 1;
    y = 140;
    i = y;
    option = 0;
    while (option == 0) {
        gfx_SetColor(140);
        kb_Scan();
        if (redraw == 1) {
            redraw = 0;
            /* redraw only the one button that needs it */
            for (OldX = 60; OldX < 244; OldX += 16) {
                gfx_Sprite(wood, OldX, i);
            }
            /* button text */
            gfx_PrintStringXY("Controls", 138, 142);
            gfx_PrintStringXY("Support", 138, 162);
            gfx_PrintStringXY("Back", 148, 182);
            gfx_Rectangle(60, y, 192, 16);
            gfx_Rectangle(61, y + 1, 190, 14);
            gfx_BlitBuffer();
        }
        i = y;
        if (kb_IsDown(kb_KeyUp) && y > 140) {
            delay(150);
            y -= 20;
        }
        if (kb_IsDown(kb_KeyDown) && y < 180) {
            delay(150);
            y += 20;
        }
        if (i != y)                                 redraw = 1;
        if (kb_IsDown(kb_Key2nd))                   option = 1;
    }
    if (y == 140) {
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 15; y++) {
                gfx_Sprite(dirt, x * 16, y * 16);
            }
        }
        gfx_PrintStringXY("Controls:", 10, 10);
        gfx_PrintStringXY("Arrow Keys = Move around", 10, 30);
        gfx_PrintStringXY("[2nd] = A", 10, 40);
        gfx_PrintStringXY("[alpha] = B", 10, 50);
        gfx_PrintStringXY("[mode] = Start", 10, 60);
        gfx_PrintStringXY("[X,T,0,n] = Select", 10, 70);
        gfx_PrintStringXY("Press any Key...", 10, 100);
        gfx_BlitBuffer();
        while (!os_GetCSC());
        delay(200);
        help();
    }
    if (y == 160) {
        for (x = 0; x < 20; x++) {
            for (y = 0; y < 15; y++) {
                gfx_Sprite(stone, x * 16, y * 16);
            }
        }
        gfx_PrintStringXY("Contact Support:", 10, 10);
        gfx_PrintStringXY("If you have any questions or suggestions,", 10, 30);
        gfx_PrintStringXY("please go to https://github.com/TimmyTurner51/CC24-SurvivalCE.", 10, 40);
        gfx_PrintStringXY("Press any Key...", 10, 100);
        gfx_BlitBuffer();
        while (!os_GetCSC());
        delay(200);
        help();
    }
    delay(200);
    main();
}

/* for future use, sometime after CC24... */
void input(void) {
    const char* chars = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
    uint24_t key, i = 0;
    char buffer[50];
    gfx_Begin();
    while ((key = os_GetCSC()) != sk_Enter) {
        if (chars[key]) {
            buffer[i++] = chars[key];
            gfx_PrintStringXY(buffer, 1, 1);
        }
    }

    delay(100);
    return;
}

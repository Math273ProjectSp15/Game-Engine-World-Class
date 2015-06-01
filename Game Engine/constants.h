// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine constants.h v2.8
// Last modification: Aug-3-2014

#pragma once
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
//                  Constants
//=============================================================================
// graphic images
const char BACKGROUND_IMAGE[] = "pictures\\background.png";
const char BACKGROUND_LAYER1[] = "pictures\\layer-1-sky.png";
const char BACKGROUND_LAYER2[] = "pictures\\layer-2-ghosts.png";
//const char GROUND_IMAGE[] = "pictures\\layer-3-ground_125X509.png";
const char DARK_MARIO_IMAGE[] = "pictures\\DarkMario_2048x2048.png";
const char MARIO_ATTACK_IMAGE[] = "pictures\\Attacks_1024x2048.png";
const char PLATFORM_IMAGE[] = "pictures\\Platform.png";
const char VILLAINS_IMAGE[] = "pictures\\Villains.png";
const char GROUND_IMAGE[] = "pictures\\ground.png";
const char GROUND1_IMAGE[] = "pictures\\ground1.png";
const char LAVA_IMAGE[] = "pictures\\lava.png";
const char SPIKE_IMAGE[] = "pictures\\spike.png";
const char AIR_GROUND1_IMAGE[] = "pictures\\airground1.png";
const char AIR_GROUND2_IMAGE[] = "pictures\\airground2.png";
const char AIR_GROUND3_IMAGE[] = "pictures\\airground3.png";
const char VILLAINS_AND_GROUND_IMAGE[] = "pictures\\VillainsAndGround.png";


// window
const char CLASS_NAME[] = "MarioGame";
const char GAME_TITLE[] = "MarioGame";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1200;               // width of game in pixels
const UINT GAME_HEIGHT = 800;               // height of game in pixels
 
// game
const bool VSYNC = true;                    // true locks display to vertical sync rate
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;             // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;         // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 500.0f;                   // acceleration of gravity pixels/sec
const int MAP_WIDTH = 3072;
const int MAP_HEIGHT = 1536;

//platform
const int PLATFORM_WIDTH = 256;
const int PLATFORM_HEIGHT = 128;
const int PLATFORM_COLUMNS = 6;
const int PLATFORM_START_FRAME = 5;
const int PLATFORM_END_FRAME = 5;

//ground
const int GROUND_ENTITY_WIDTH = 512;
const int GROUND_ENTITY_HEIGHT = 128;
const int GROUND_ENTITY_COLUMNS = 4;
const int GROUND_ENTITY_START_FRAME = 3;
const int GROUND_ENTITY_END_FRAME = 3;

const float GROUND_Y_POSITION = GAME_HEIGHT - GROUND_ENTITY_HEIGHT;

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "";

// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = '`';         // ` key
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR LEFT_KEY    = VK_LEFT;      // left arrow
const UCHAR RIGHT_KEY   = VK_RIGHT;     // right arrow
const UCHAR DOWN_KEY	= VK_DOWN;		// down arrow
const UCHAR UP_KEY = VK_UP;		        // up arrow
const UCHAR F_KEY = 0x46;
const UCHAR D_KEY = 0x44;
const UCHAR S_KEY = 0x53;

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

#endif

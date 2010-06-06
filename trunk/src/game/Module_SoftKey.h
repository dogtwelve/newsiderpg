#ifndef _MODULE_SOFTKEY_
#define _MODULE_SOFTKEY_

#define COMMON_SPRITE_SOFTKEY                   load_commonSpriteArray[1]
#define COMMON_SPRITE_NUMBER					load_commonSpriteArray[2]
#define COMMON_SPRITE_MAINUI					load_commonSpriteArray[3]
// Softkey types

#define SOFTKEY_NONE                            0
#define SOFTKEY_LEFT                            1
#define SOFTKEY_RIGHT                           2

// Softkey symbols

#define SOFTKEY_SYMBOL_MENU                     -1
#define SOFTKEY_SYMBOL_BACK                     -2
#define SOFTKEY_SYMBOL_OK                       -3
#define SOFTKEY_SYMBOL_CANCEL                   -4
#define SOFTKEY_SYMBOL_EMPTY                    -5
#define SOFTKEY_SYMBOL_YES                      -6
#define SOFTKEY_SYMBOL_NO                       -7
#define SOFTKEY_SYMBOL_EZI                      -8


#ifndef __COMMAND_DEF_H__

    // Softkey variables
   
    //public static int		               softkey_leftText;
    //public static int                      softkey_rightText;
    //public static int                      softkey_centerText;
    //public static boolean                  softkey_drawBar;
    //public static int                      softkey_currentSelection;
#endif //#ifndef __STATE_DEFINE__

// Softkey distance from screen corners

#define SOFTKEY_BACK_FRM_HEIGHT 10
#define SOFTKEY_BACK_FRM_WIDTH 10

#define SOFTKEY_DISTANCE_FROM_CORNER            0

#define SOFTKEY_LEFT_POS_Y  SCREEN_HEIGHT - SOFTKEY_BACK_FRM_HEIGHT
#define SOFTKEY_RIGHT_POS_Y  SCREEN_HEIGHT - SOFTKEY_BACK_FRM_HEIGHT


#define SOFTKEY_RIGHT_POS_X  SCREEN_WIDTH - 1 - SOFTKEY_DISTANCE_FROM_CORNER - SOFTKEY_BACK_FRM_WIDTH




#endif //#ifndef _MODULE_SOFTKEY_

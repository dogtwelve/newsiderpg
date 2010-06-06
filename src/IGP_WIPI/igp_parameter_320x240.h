
#define IGPITEM_DY 14
#define IGP_FIRST_ITEM_POS_Y 50
#define IGP_LOGO_HEIGHT 5

#define SCREEN_SHOOT_X (SCREEN_WIDTH >> 1)
#define SCREEN_SHOOT_Y (0)

#define IGP_STR_PLAY_FOR_FREE_X (SCREEN_WIDTH>>1)
#define IGP_STR_PLAY_FOR_FREE_Y (SCREEN_HEIGHT>>1)
#define IGP_STR_PLAY_FOR_FREE_WIDTH (_sprIGPYellowPromotion->GetWidth() >> 1)
#define IGP_STR_PLAY_FOR_FREE_HEIGHT (30)

#define IGP_WH_TITLE_X (SCREEN_WIDTH >> 1)
#define IGP_WH_TITLE_Y (_sprIGPCataLogo->GetHeight() + IGP_LOGO_HEIGHT + 20)
#define IGP_WH_ICON_X (30)
#define IGP_WH_ICON_Y (IGP_WH_TITLE_Y+35)
#define IGP_WH_ICON_GAP_Y 25
#define IGP_WH_TEXT_X (IGP_WH_ICON_X+_sprWHImages[0]->GetWidth()+5)
#define IGP_WH_TEXT_WIDTH (150)

#define IGP_SELECT_REC_WIDTH (270)
#define IGP_SELECT_REC_X ((SCREEN_WIDTH-IGP_SELECT_REC_WIDTH)/2)


#define IGP_RIGHT_ARROW_X (SCREEN_WIDTH)
#define IGP_LEFT_ARROW_X (0)

#define IGP_GAME_INTRO_Y SCREEN_SHOOT_Y+_sprIGPGame[0]->GetHeight()+2
#include "WorldmapUI.h"

WorldmapUI::WorldmapUI(int TOWN_id){

	b_ViewWorldMap = true;


	_spr_Worldmap_WEST = SUTIL_LoadSprite(PACK_SPRITE_WORLDMAP, SPRITE_WORLDMAP_WORLDMAP_WEST_UI);
	_spr_Worldmap_EAST = SUTIL_LoadSprite(PACK_SPRITE_WORLDMAP, SPRITE_WORLDMAP_WORLDMAP_EAST_UI);
	_spr_Worldmap_SEA  = SUTIL_LoadSprite(PACK_SPRITE_WORLDMAP, SPRITE_WORLDMAP_WORLDMAP_SEA_UI);
	_spr_Worldmap_SEA->SetBlendFrame(FRAME_WORLDMAP_SEA_BLEND);
	

	_txt_AreaName = _SUTIL->LoadTextPack(PACK_DATA_TEXT, DATA_TEXT_AREANAME); 

	initSpot = 0;
	switch(TOWN_id){//포탈 포지션
		case 0:
			TOWN_Num = 0;
			spot_Num = ARRAY_SIZE(Town_1_Spot);
			for(int xx = 0;xx<spot_Num;xx++){for(int yy = 0;yy<6;yy++){
					Town_Buffer[xx][yy] = Town_1_Spot[xx][yy];
			}}
			break;

		case 1:
			TOWN_Num = 1;
			spot_Num = ARRAY_SIZE(Town_2_Spot);
			for(int xx = 0;xx<spot_Num;xx++){for(int yy = 0;yy<6;yy++){
				Town_Buffer[xx][yy] = Town_2_Spot[xx][yy];
			}}
			break;

	}
	Target_Num = Town_Buffer[initSpot][Sp_ID];
	Target_X = Focus_X = Town_Buffer[initSpot][Sp_X];
	Target_Y = Focus_Y = Town_Buffer[initSpot][Sp_Y];


}



WorldmapUI::~WorldmapUI(){
	SUTIL_FreeSprite(_spr_Worldmap_WEST);
	SUTIL_FreeSprite(_spr_Worldmap_EAST);
	SUTIL_FreeSprite(_spr_Worldmap_SEA );

	SUTIL_FreeTextPack(_txt_AreaName);
}



#define		MAX_MOVE		(10)
#define		MAX_RETURN		(20)
void WorldmapUI::KeyEvent(int m_keyCode, int m_keyRepeat){
	if(Ani_Num<13){return;}

	if(m_keyCode == MH_KEY_4)m_keyCode=MH_KEY_LEFT;		//값대치
	if(m_keyCode == MH_KEY_6)m_keyCode=MH_KEY_RIGHT;	//값대치
	if(m_keyCode == MH_KEY_2)m_keyCode=MH_KEY_UP;		//값대치
	if(m_keyCode == MH_KEY_8)m_keyCode=MH_KEY_DOWN;		//값대치
	if(m_keyCode == MH_KEY_5)m_keyCode=MH_KEY_SELECT;	//값대치

	switch(m_keyCode)
	{
	case MH_KEY_RIGHT:	{AccelerationX=+MAX_MOVE;AccelerationY*=2;AccelerationY/=3; break;}
	case MH_KEY_LEFT:	{AccelerationX=-MAX_MOVE;AccelerationY*=2;AccelerationY/=3; break;}
	case MH_KEY_DOWN:	{AccelerationY=+MAX_MOVE;AccelerationX*=2;AccelerationX/=3; break;}
	case MH_KEY_UP:		{AccelerationY=-MAX_MOVE;AccelerationX*=2;AccelerationX/=3; break;}

		case MH_KEY_CLEAR:	
			{
				b_ViewWorldMap = false;
				ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
				ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, Town_Buffer[initSpot][Sp_ID], 0);
				PopupUi::AddAreaMessage((char*)_txt_AreaName->nText[Town_Buffer[initSpot][Sp_NAME]]);
				Field::m_nWayMoveCharx = MC_posX;
				Field::m_nWayMoveChary = 240;

				break;
			}
		case MH_KEY_SELECT: 
			{
				b_ViewWorldMap = false;
				ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
				ADD_EVENT_MSG(EVT_CHANGE_STAGE, 10, Target_Num, 0);
				PopupUi::AddAreaMessage((char*)_txt_AreaName->nText[Target_Name]);
				Field::m_nWayMoveCharx = MC_posX;
				Field::m_nWayMoveChary = 240;

				break;
			}
		case 0://키를떼면 가장 가까운 포인트를 찾는다
			{
				AccelerationX*=2; 
				AccelerationY*=2;
				AccelerationX/=3; 
				AccelerationY/=3;
				if(AccelerationX||AccelerationY)break;

				for(int xx = 0,length_MAX =1000000;xx<spot_Num;xx++){
					int length_NOW = 
						((Town_Buffer[xx][Sp_X] - Focus_X)*(Town_Buffer[xx][Sp_X] - Focus_X)) + 
						((Town_Buffer[xx][Sp_Y] - Focus_Y)*(Town_Buffer[xx][Sp_Y] - Focus_Y));

					if(length_NOW < length_MAX){
						length_MAX = length_NOW;
						Target_Name = Town_Buffer[xx][Sp_NAME];
						Target_Num = Town_Buffer[xx][Sp_ID];
						Target_X = Town_Buffer[xx][Sp_X];
						Target_Y = Town_Buffer[xx][Sp_Y];
						MC_posX = Town_Buffer[xx][Set_PosX];
						MC_derection = Town_Buffer[xx][Set_Dir];
					}
					
				}
				if((Focus_X-Target_X)>(MAX_RETURN*2)){ 
					Focus_X -= MAX_RETURN; 
				}else if((Focus_X-Target_X)<-(MAX_RETURN*2)){
					Focus_X -= -MAX_RETURN; 
				}else{
					int xx = Focus_X-Target_X;
					if(ABS(xx) == 1){
						Focus_X = Target_X; 
					}else{
						Focus_X -= (xx)/2; 
					}
				}
				if((Focus_Y-Target_Y)>(MAX_RETURN*2)){
					Focus_Y -= MAX_RETURN; 
				}else if((Focus_Y-Target_Y)<-(MAX_RETURN*2)){
					Focus_Y -= -MAX_RETURN; 
				}else{
					int yy = Focus_Y-Target_Y;
					if(ABS(yy) == 1){
						Focus_Y = Target_Y; 
					}else{
						Focus_Y -= (yy)/2; 
					}
				}


			break;
			}

			

	}

	Focus_X += AccelerationX;
	Focus_Y += AccelerationY;

	if(Focus_X > 270)Focus_X =  270;
	if(Focus_X <-270)Focus_X = -270;
	if(Focus_Y > 200)Focus_Y =  200;
	if(Focus_Y <-200)Focus_Y = -200;

	
}


void WorldmapUI::Process(){

}

void WorldmapUI::Paint(){
	Ani_Num++;
	if(Ani_Num<10){ 
		_SUTIL->g->blandBlur(); 
		return;
	}



	SUTIL_SetColor(0x1d85b1);
	SUTIL_FillRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

	if(-100 -Focus_Y > 0){
		SUTIL_SetColor(0x024363);
		SUTIL_FillRect(0,0,SCREEN_WIDTH,-100 -Focus_Y);
	}
	
	SUTIL_Paint_Frame(_spr_Worldmap_SEA ,FRAME_WORLDMAP_SEA_WATER,XPOS,-100 -Focus_Y,0);//수평선
	

	int Wave_ani = Ani_Num%60; 
	if(Wave_ani < 30){
		_spr_Worldmap_SEA->SetBlendCustom(true,true,1,2+Wave_ani);
	}else{
		_spr_Worldmap_SEA->SetBlendCustom(true,true,1,61 - Wave_ani);
	}

	SUTIL_Paint_Frame(_spr_Worldmap_SEA ,FRAME_WORLDMAP_SEA_BOTTOM,XPOS - Focus_X,YPOS - Focus_Y,0);//배경
	_spr_Worldmap_SEA->SetBlendCustom(false,false,0,0);

	SUTIL_Paint_Frame(_spr_Worldmap_SEA ,FRAME_WORLDMAP_SEA_ISLAND,XPOS - Focus_X,YPOS - Focus_Y,0);//공중섬 그림자
	
	
	
	SUTIL_Paint_Frame(_spr_Worldmap_WEST ,FRAME_WORLDMAP_WEST__1ST,XPOS - Focus_X+LAND1_X	,YPOS - Focus_Y+LAND1_Y,0);//배경
	if(INIT_SAVELOAD()->HaveBeenVillage[2]){_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);}else{_spr_Worldmap_WEST->SetBlendCustom(true,true,8,0);}
	SUTIL_Paint_Frame(_spr_Worldmap_WEST ,FRAME_WORLDMAP_WEST__2ST,XPOS - Focus_X+LAND2_X	,YPOS - Focus_Y+LAND2_Y,0);//배경
	if(INIT_SAVELOAD()->HaveBeenVillage[3]){_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);}else{_spr_Worldmap_WEST->SetBlendCustom(true,true,8,0);}
	SUTIL_Paint_Frame(_spr_Worldmap_WEST ,FRAME_WORLDMAP_WEST__4ST,XPOS - Focus_X+LAND4_X	,YPOS - Focus_Y+LAND4_Y,0);//배경
	_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);	

	if(INIT_SAVELOAD()->HaveBeenVillage[4]){_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);}else{_spr_Worldmap_EAST->SetBlendCustom(true,true,8,0);}
	SUTIL_Paint_Frame(_spr_Worldmap_EAST ,FRAME_WORLDMAP_EAST__3ST,XPOS - Focus_X+LAND3_X	,YPOS - Focus_Y+LAND3_Y,0);//배경
	if(INIT_SAVELOAD()->HaveBeenVillage[5]){_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);}else{_spr_Worldmap_EAST->SetBlendCustom(true,true,8,0);}
	SUTIL_Paint_Frame(_spr_Worldmap_EAST ,FRAME_WORLDMAP_EAST__5ST,XPOS - Focus_X+LAND5_X	,YPOS - Focus_Y+LAND5_Y,0);//배경
	if(INIT_SAVELOAD()->HaveBeenVillage[6]){_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);}else{_spr_Worldmap_EAST->SetBlendCustom(true,true,8,0);}
	SUTIL_Paint_Frame(_spr_Worldmap_EAST ,FRAME_WORLDMAP_EAST__6ST,XPOS - Focus_X+LAND6_X	,YPOS - Focus_Y+LAND6_Y,0);//배경
	if(INIT_SAVELOAD()->HaveBeenVillage[7]){_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);}else{_spr_Worldmap_EAST->SetBlendCustom(true,true,8,0);}
	SUTIL_Paint_Frame(_spr_Worldmap_EAST ,FRAME_WORLDMAP_EAST__7ST,XPOS - Focus_X+LAND7_X	,YPOS - Focus_Y+LAND7_Y,0);//배경
	_spr_Worldmap_EAST->SetBlendCustom(false,false,0,0);	


	_spr_Worldmap_WEST->SetBlendCustom(true,true,8,0);
	for(int xx = 0;xx<12;xx++){
		if(INIT_SAVELOAD()->HaveBeenVillage[xx]){
			SUTIL_Paint_Frame(_spr_Worldmap_WEST ,FRAME_WORLDMAP_WEST_HOUSE,XPOS - Focus_X+Town_All_Spot[xx][House_X],YPOS - Focus_Y+Town_All_Spot[xx][House_Y],0);//배경
		}
		
	}
	_spr_Worldmap_WEST->SetBlendCustom(false,false,0,0);

	switch(TOWN_Num){//포탈 포지션
		case 0:
			SUTIL_Paint_Frame(_spr_Worldmap_WEST ,FRAME_WORLDMAP_WEST__1ST_TOWN1,XPOS - Focus_X+LAND1_X	,YPOS - Focus_Y+LAND1_Y,0);//배경
			break;
		case 1:
			SUTIL_Paint_Frame(_spr_Worldmap_WEST ,FRAME_WORLDMAP_WEST__1ST_TOWN2,XPOS - Focus_X+LAND1_X	,YPOS - Focus_Y+LAND1_Y,0);//배경
			break;


	}

	SUTIL_Paint_Ani(_spr_Worldmap_SEA ,ANIM_WORLDMAP_SEA_SELECT, XPOS,YPOS,0);//배경


	if((Focus_X==Target_X)&&(Focus_Y==Target_Y)){//이동이 끝난 정지상태라면

		_SUTIL->pFont->setColor(0xFFFFFF);
		_SUTIL->pFont->setOutline(false);
		SUTIL_Paint_Frame(_spr_Worldmap_SEA ,FRAME_WORLDMAP_SEA_POP_NAME,XPOS,YPOS,0);//배경
		_SUTIL->pFont->DrawText(_SUTIL->g, (char*)_txt_AreaName->nText[Target_Name],XPOS,YPOS+21, CGraphics::HCENTER);
	}


	if(Ani_Num<13){
		for(int xx = 0;xx<13-Ani_Num;xx++){ 
			_SUTIL->g->blandBlur();
		}
	}

}


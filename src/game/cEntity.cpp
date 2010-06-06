#include "Macro.h"
#include "Defines.h"

#include "../common/Engine.h"
#include "../common/Image.h"
#include "../common/Stream.h"
#include "../common/Graphics.h"

#include "ASprite.h"

#include "GAME.h"
#include "../wipi/Small_Font.h"

#include "cEntity.h"
#include "ENTITY.h"
#include "ASpriteInstance.h"

#include "Command_Def.h"


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY DRAW ENTITY DRAW ENTITY DRAW ENTITY DRAW ENTITY DRAW ENTITY DRAW
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//--------------------------------------------------------------------------
/// draw method.
///
/// @param x x viewport to screen translation.
/// @param y y viewport to screen translation.
/// @param ox x world to viewport translation.
/// @param oy y world to viewport translation.
//--------------------------------------------------------------------------

short* cEntity::s_zones; 

cEntity::~cEntity()
{
	SAFE_DEL_ARRAY(m_params);
	//SAFE_DEL_ARRAY(m_stateArry);
	//SAFE_DEL_ARRAY(m_aniArry);
	SAFE_DEL_ARRAY_OBJ(m_renderer, m_renderer_length);
}

void cEntity::draw (int x, int y, int ox, int oy)
{

//	if ((m_flags & DFLAGS::HIDE_LAYER) != 0)
//	{
//		return;
//	}
#ifdef hasShine
	if(m_type == ENTITY::K_SHINE)
	{
		PaintShine(x, y ,ox, oy);
	}
#endif
	ASpriteInstance* si;

	//int offY = 0;
/*	if(m_type == GAMESPRITE_MAIN_CHAR)
	{
		if( (g_pGame->m_CharAbility & CHAR_RAPID_FOOD) != 0)
		{
			if(game_counter % 3 == 0)
			{
				g->SetChannel(CHANNEL_COLORALPHA);				
				g->SetARGBColor(0x7fff0000);

			}
		}
	//	
	////	offY = m_renderer[CHARSLOT::k_slot_boby]->getAniFrameOffY(); 	
	////	//DBG("m_renderer[CHARSLOT::k_slot_body].m_posOffY"+m_renderer[CHARSLOT::k_slot_boby].getAniFrameOffY());
	}	*/


	for (int i = 0; i < m_renderer_length; i++)
	{
		si = m_renderer[i];

		if (si == NULL)
		{
			continue;
		}

		if (si->m_nCrtModule == ANIM_EMPTY)
		{
			continue;
			//return;
		}

		si->m_posX = (m_posX - ox) + x;
		si->m_posY = (m_posY - oy) + y;

		m_OFFposX = si->m_posX;
		m_OFFposY = si->m_posY;

		if ((si->m_flags & FLAG_ADD_Z) != 0)
		{
			si->m_posY -= m_posZ;
		}

		//if(m_type == ENTITY::k_main_character && i == CHARSLOT::k_slot_etc)
		//{
		//	si->m_posY += offY;
		//}

		//si->PaintSprite(g);

		//pause
		si->UpdateSpriteAnim();


		//if(m_type == GAMESPRITE_ARROW && arrow_str != NULL)
		//{
		////	//#define DRAW_KORSTR_LINE( g, str , x, y, anchor , color ,color1)					g_pGame->jFont.setOutline(true);g_pGame->jFont.setOutlineColor(color);g_pGame->jFont.DrawString(g, str , x, y, anchor, color1);
		//	DRAW_KORSTR_LINE( g, arrow_str , si->m_posX, si->m_posY, Graphics::HCENTER | Graphics::TOP , 0x000000 ,0xffffff);		
		//}		
		//else if(i == 0 )
		//{
		//	//talk emotion
		//	for(int _em = 0 ; _em < 15 ; _em++)
		//	{
		//		if(m_type == g_pGame->emotion_m_type[_em])
		//		{
		//			if(m_type == ENTITY::k_dog || m_type == ENTITY::k_dogtutorial)
		//		{	
		//				g_pGame->load_commonSpriteArray[4]->PaintAndUpdateCurrentAnimation(g, _em, si->m_posX, si->m_posY + 20, 0, 0, 0);
		//			}else
		//			{
		//				g_pGame->load_commonSpriteArray[4]->PaintAndUpdateCurrentAnimation(g, _em, si->m_posX, si->m_posY, 0, 0, 0);
		//			}
		//		}
		//	}
		//}

	}
	g->UnSetChannel(CHANNEL_COLORALPHA); 
	g->SetARGBColor(0xffffffff);
	
}


//cEntity_init.h

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY INIT ENTITY INIT ENTITY INIT ENTITY INIT ENTITY INIT ENTITY INIT
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//--------------------------------------------------------------------------
/// constructor.
///
/// @param type type of the ENTITY::
/// @param sprite_amount amount of ASpriteInstance to allocate.
//--------------------------------------------------------------------------

cEntity::cEntity (int type, int sprite_amount)
{

	// get entity's type.
	m_type = type;

	// allocate sprite instance array.
	if (sprite_amount > 0)
	{
		m_renderer = GL_NEW ASpriteInstance*[sprite_amount];
		m_renderer_length = sprite_amount;
	}
	else
	{
		m_renderer = NULL;
	}
}
//--------------------------------------------------------------------------
/// init method.
///
/// @param flags entity's properties.
/// @param pos_x entity's world x position.
/// @param pos_y entity's world y position.
//--------------------------------------------------------------------------
// TODO_LOLO => handle param array
void cEntity::init (int flags, int pos_x, int pos_y, short* params , int actor_max)
{
	bool new_params = true;
	// get entity's flags.
	m_flags = flags;

	// set entity's world position.
	m_posX = pos_x;//I2F(pos_x);
	m_posY = pos_y;//I2F(pos_y);

	// init entity's velocity.
	m_velX = 0;
	m_velY = 0;

	// init entity's acceleration.
	m_accX = 0;
	m_accY = 0;

	// init entity's direction.
	m_dir		= -1;
	m_dirNext	= -1;
	
	m_dirCount  = 0;
	m_dirNotCollCnt = 0;
	
	m_gameId = params[ACTOR_GAMEID];
/*
	switch (m_type)
	{

		case GAMESPRITE_MAIN_CHAR:
		{
			initSprite(CHARSLOT::k_slot_boby,  m_type);		
			initSprite(CHARSLOT::k_slot_shadow,  m_type);
		//	initSprite(CHARSLOT::k_slot_effect,  m_type);
			initSprite(CHARSLOT::k_slot_etc,  m_type);

			setSpriteLayer(CHARSLOT::k_slot_etc,   LAYER::k_hide);
		//	setSpriteLayer(CHARSLOT::k_slot_shadow,   LAYER::k_shadow);
			

			setAnim(CHARSLOT::k_slot_boby, params[ACTOR_ANIID]);
			setAnim(CHARSLOT::k_slot_shadow, ANIM_MAINCHARACTER_SHADOW);
		//	setAnim(CHARSLOT::k_slot_effect, ANIM_MAINCHARACTER_FISHINGEFFECT_BASIC_2);		
			setAnim(CHARSLOT::k_slot_etc, ANIM_MAINCHARACTER_FISHINGEFFECT_BASIC_2);

		//	////setFlag(ENTITY::k_flag_display_list);
			break;
		}

		case GAMESPRITE_CHICK:
		{
			initSprite(CHARSLOT::k_slot_boby,  m_type);
			initSprite(CHARSLOT::k_slot_shadow, m_type );

			setAnim(CHARSLOT::k_slot_boby, params[ACTOR_ANIID]);			
			setAnim(CHARSLOT::k_slot_shadow, ANIM_CHICK_SHADOW );	
			break;
		}

		case GAMESPRITE_E_INTRO_ANI:
		case GAMESPRITE_E_IMOTICON:
		case GAMESPRITE_CHIEF:
		case GAMESPRITE_FAMILY:	
		case GAMESPRITE_GORILLA:
		case GAMESPRITE_SPIDER_NET:
		case GAMESPRITE_BUILDING:		
		{
			initSprite(ETCSLOT::k_slot_boby,  m_type);
			setAnim(ETCSLOT::k_slot_boby, params[ACTOR_ANIID]);
			break;
		}


		case GAMESPRITE_BUG: 
		case GAMESPRITE_MOUSE:
		case GAMESPRITE_CLOUD:
		{

			initSprite(ETCSLOT::k_slot_boby,  m_type);

			setAnim(ETCSLOT::k_slot_boby, params[ACTOR_ANIID]);
			
			m_velMax =  params[ACTOR_VELOCITY];

			if ( m_velMax > 0 )
			{
				m_velX = g_pGame->random(m_velMax-1,m_velMax);
				m_velY = 0;

				m_posX = g_pGame->random(params[ACTOR_PATROL_X1],params[ACTOR_PATROL_X2]);
				m_posY = g_pGame->random(params[ACTOR_PATROL_Y1],params[ACTOR_PATROL_Y2]);
			}

			if ( m_type == GAMESPRITE_CLOUD )
			{
				if ( m_velMax > 0 )
				{
					m_dir = DIRECT_LEFT;//g_pGame->random(0,2);
				}				
			}
			else 
			{
				m_velX = g_pGame->random(1,2);

				if ( m_velMax > 0 )
				{
					m_velX = g_pGame->random(m_velMax-1,m_velMax);
				}

				if( m_type == GAMESPRITE_MOUSE )
				{
					m_velX += 2;
				}

				m_dir = params[ACTOR_ANIID]+1;
			//	unsetFlag(DFLAGS::HIDE_LAYER);				

			}
			break;

		}

	case GAMESPRITE_FISH:
		{
			initSprite(ETCSLOT::k_slot_boby,  m_type);			

			setAnim(ETCSLOT::k_slot_boby, params[ACTOR_ANIID]);
			
			setSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);			
			
			m_dir = DIRECT_LEFT;
			m_supportTime = 1;
			m_velX = 3;
			break;
		}

	case GAMESPRITE_ARROW:
		{
			initSprite(ETCSLOT::k_slot_boby,  m_type);
			setAnim(ETCSLOT::k_slot_boby, params[ACTOR_ANIID]);
			

			if(params[ACTOR_ARROW_ACTIVE] != -1 ) // -1 (ALWAYS SHOW ARROW)
			{
				setFlag(DFLAGS::HIDE_LAYER);
			}

			if(params[ACTOR_ARROW_STRINGTYPE] == 0)
			{
				arrow_str = NULL;
			}
			else
			{
				SPRINTF(arrow_str_array ,"%s", GET_STRING((COMMON_MAPNAME_01+params[ACTOR_ARROW_STRINGTYPE]-1), TEXT_INDEX_COMMON));
				arrow_str = arrow_str_array;
			}			
			break;
		}
	case GAMESPRITE_EFFECT_LAMP:
		{
			initSprite(ETCSLOT::k_slot_boby,  m_type);			

			setAnim(ETCSLOT::k_slot_boby, params[ACTOR_ANIID]);

			g_pGame->ModifyPalette(g_pGame->m_bSprite[m_type],0,0);
			
			break;
		}
#ifdef hasShine		
	case ENTITY::K_SHINE:
		{
			new_params = false;
			
			

			m_params = GL_NEW short[20];
			for(int _g = 0 ; _g < 2 ; _g++)
			{
				m_params[_g] = params[ACTOR_PATROL_X1+_g];
			}


			m_params[SHINE::m_type] = params[ACTOR_ANIID];			

			m_params[SHINE::m_paramX3] = (m_params[SHINE::m_type] % 9) / 3;//0:small 1:middle 2:big
			m_params[SHINE::m_paramX2] = m_params[SHINE::m_type] % 3;
			m_params[SHINE::m_paramX1] = (m_params[SHINE::m_type] > 8)? ((7 * TILE_H) >> 1): 3 * TILE_H; //window width
			m_params[SHINE::m_minHeight] = (m_params[SHINE::m_type] > 8)?1:3;	//small shine
			m_params[SHINE::m_maxHeight] = (m_params[SHINE::m_type] > 8)?0:2;	//big shine
			m_params[SHINE::m_z_order] = 0;		//STATE::Z_FIRST;
			m_params[SHINE::m_paramY] = params[SHINE::PARAM_INDEX_SHINE_COUNT]; // y is count of 
			m_params[SHINE::m_paramY2] = params[SHINE::PARAM_INDEX_SHINE_LENGTH];
			if (m_params[SHINE::m_type]!= ENTITY::VALUE_SHINE_TYPE_SMAL_CYCLE)
			{  
				switch (m_params[SHINE::m_paramX3]) {
					case 0://small
						// small-small-small	
						m_params[SHINE::_rectIce_length] = 6;
						m_params[SHINE::_rectIce_array] = m_posY + g_pGame->random(TILE_H >> 1,TILE_H);
						m_params[SHINE::_rectIce_array + 1] = m_params[SHINE::m_minHeight];	//small
						m_params[SHINE::_rectIce_array + 2] = m_params[SHINE::_rectIce_array] + SHINE::SHINE_SMALL_LINE_WIDTH + g_pGame->random(-TILE_H >> 2,TILE_H >> 2);
						m_params[SHINE::_rectIce_array + 3] = m_params[SHINE::m_minHeight];	//small
						m_params[SHINE::_rectIce_array + 4] = m_params[SHINE::_rectIce_array + 2] + SHINE::SHINE_SMALL_LINE_WIDTH + g_pGame->random(-TILE_H >> 2,TILE_H >> 2);
						if (m_params[SHINE::_rectIce_array + 4] > m_posY + 4 * TILE_H - SHINE::SHINE_SMALL_LINE_WIDTH) {
							m_params[SHINE::_rectIce_array + 4] = m_posY + 4 * TILE_H - SHINE::SHINE_SMALL_LINE_WIDTH;
						}
						m_params[SHINE::_rectIce_array + 5] = m_params[SHINE::m_minHeight];	//small
						break;
					case 1://middle
						//small-small-big-small
						m_params[SHINE::_rectIce_length] = 8;						
						m_params[SHINE::_rectIce_array] = m_posY + g_pGame->random(TILE_H >> 1,TILE_H);
						m_params[SHINE::_rectIce_array + 1] = m_params[SHINE::m_minHeight];	//small
						m_params[SHINE::_rectIce_array + 2] = m_params[SHINE::_rectIce_array] + SHINE::SHINE_SMALL_LINE_WIDTH - g_pGame->random(TILE_H >> 2,TILE_H >> 1) - (TILE_H >> 3);
						m_params[SHINE::_rectIce_array + 3] = m_params[SHINE::m_maxHeight];	//big
						m_params[SHINE::_rectIce_array + 4] = m_params[SHINE::_rectIce_array + 2] + SHINE::SHINE_BIG_LINE_WIDTH - g_pGame->random(TILE_H >> 2,TILE_H >> 1) - (TILE_H >> 3);
						m_params[SHINE::_rectIce_array + 5] = m_params[SHINE::m_minHeight];	//small
						m_params[SHINE::_rectIce_array + 6] = m_params[SHINE::_rectIce_array + 4] + SHINE::SHINE_SMALL_LINE_WIDTH + g_pGame->random(TILE_H >> 2,TILE_H >> 1);
						if (m_params[SHINE::_rectIce_array + 6] > m_posY + 6 * TILE_H - SHINE::SHINE_SMALL_LINE_WIDTH) {
							m_params[SHINE::_rectIce_array + 6] = m_posY + 6 * TILE_H - SHINE::SHINE_SMALL_LINE_WIDTH;
						}
					m_params[SHINE::_rectIce_array + 7] = m_params[SHINE::m_minHeight];	//small
						break;
					case 2://big
						//big-big small big-small		
						m_params[SHINE::_rectIce_length] = 10;
						m_params[SHINE::_rectIce_array] = m_posY + g_pGame->random(TILE_H >> 1,TILE_H);
						m_params[SHINE::_rectIce_array+1] = m_params[SHINE::m_maxHeight];	//big
						m_params[SHINE::_rectIce_array+2] = m_params[SHINE::_rectIce_array] + SHINE::SHINE_BIG_LINE_WIDTH - g_pGame->random(TILE_H >> 2,TILE_H >> 1);
						m_params[SHINE::_rectIce_array+3] = m_params[SHINE::m_maxHeight];	//big
						m_params[SHINE::_rectIce_array+4] = m_params[SHINE::_rectIce_array+2] + SHINE::SHINE_BIG_LINE_WIDTH + g_pGame->random(TILE_H >> 2,TILE_H >> 1);
						m_params[SHINE::_rectIce_array+5] = m_params[SHINE::m_minHeight];	//small
						m_params[SHINE::_rectIce_array+6] = m_params[SHINE::_rectIce_array+4] + SHINE::SHINE_SMALL_LINE_WIDTH + g_pGame->random(TILE_H >> 2,TILE_H >> 1);
						if (m_params[SHINE::_rectIce_array+6] > m_posY + 8 * TILE_H - SHINE::SHINE_BIG_LINE_WIDTH - SHINE::SHINE_SMALL_LINE_WIDTH + (TILE_H >> 2)) {
							m_params[SHINE::_rectIce_array+6] = m_posY + 8 * TILE_H - SHINE::SHINE_BIG_LINE_WIDTH - SHINE::SHINE_SMALL_LINE_WIDTH + (TILE_H >> 2);
						}
						m_params[SHINE::_rectIce_array+7] = m_params[SHINE::m_maxHeight];	//big
						m_params[SHINE::_rectIce_array+8] = m_params[SHINE::_rectIce_array+6] + SHINE::SHINE_BIG_LINE_WIDTH - g_pGame->random(TILE_H >> 2,TILE_H >> 1);
						if (m_params[SHINE::_rectIce_array+8] > m_posY + 8 * TILE_H - SHINE::SHINE_SMALL_LINE_WIDTH) {
							m_params[SHINE::_rectIce_array+8] = m_posY + 8 * TILE_H - SHINE::SHINE_SMALL_LINE_WIDTH;
						}
						m_params[SHINE::_rectIce_array+9] = m_params[SHINE::m_minHeight];	//small
						break;
				}
			}
			break;
		}
#endif
	



	case -1:
		{
			// SAMPLE ( DRAW OBJECT )
			//initSprite(OBJECT.k_slot_primary, Data.SPRITE_BED);
			//setSpriteLayer(OBJECT.k_slot_primary, LAYER::k_furniture);
			//setAnim(OBJECT.k_slot_primary, ANIM_HOME_BED.BED);
			//setFlag(ENTITY_FLAG_DISPLAY_LIST);
			break;
		}
	}*/
	
	if( new_params && actor_max > 6 )
	{
		m_params = GL_NEW short[(actor_max-6)];
		for(int _g = 0 ; _g < (actor_max-6) ; _g++)
		{
			m_params[_g] = params[ACTOR_PATROL_X1+_g];
		}
	}	
	
}


//--------------------------------------------------------------------------
/// initialize sprite instance.
///
/// @param slot_idx ASpriteInstance array index.
/// @param sprite_idx index in sprite's poll.
//--------------------------------------------------------------------------

void cEntity::initSprite (int slot_idx, int sprite_idx)
{

	//sprite_amount[slot_idx] = 1;
	//m_renderer = g_pGame->m_bSprite[sprite_idx];

	// allocate sprite instance in the specified slot.
	m_renderer[slot_idx] = GL_NEW ASpriteInstance(g_pGame->m_bSprite[sprite_idx],
		m_posX,
		m_posY,
		NULL);

	ASpriteInstance* si = m_renderer[slot_idx];

	// set current anim to "NULL".
	si->m_nCrtModule = ANIM_EMPTY;

	// set layer to default value.
	//si->m_layer = LAYER::k_inactive;
	//si->m_flags = m_flags ;
}


//--------------------------------------------------------------------------
/// free method.
//--------------------------------------------------------------------------
void cEntity::set_direct( int _direct )
{
	m_dir = _direct;
}



//--------------------------------------------------------------------------
/// free method.
//--------------------------------------------------------------------------
int cEntity::get_direct(  )
{

	return m_dir;
}


//--------------------------------------------------------------------------
/// free method.
//--------------------------------------------------------------------------
void cEntity::free ()
{
	// free renderers...
	if (m_renderer != NULL)
	{
		SAFE_DEL_ARRAY_OBJ(m_renderer, m_renderer_length);
	}

	//s_nodeParent 	= NULL;
	//s_nodePrev		= NULL;
	//s_nodeNext		= NULL;
	//s_nodeG			= NULL;
	//s_nodeH			= NULL;
	//s_path			= NULL;
	// free data...
}

//cEntity_update.h

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY UPDATE ENTITY UPDATE ENTITY UPDATE ENTITY UPDATE ENTITY UPDATE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void cEntity::process_move( int _velX, int _velY, boolean _plus )
{
	if ( _plus )
	{
		if( m_dir == DIRECT_LEFT )
		{
			m_posX -= _velX;					
		}
		else if( m_dir == DIRECT_RIGHT )
		{
			m_posX += _velX;
		}
		else if( m_dir == DIRECT_UP )
		{
			m_posY -= _velY;
		}
		else if( m_dir == DIRECT_DOWN )
		{
			m_posY += _velY;
		}
	}
	else 
	{
		if( m_dir == DIRECT_LEFT )
		{
			m_posX += _velX;					
		}
		else if( m_dir == DIRECT_RIGHT )
		{
			m_posX -= _velX;
		}
		else if( m_dir == DIRECT_UP )
		{
			m_posY += _velY;
		}
		else if( m_dir == DIRECT_DOWN )
		{
			m_posY -= _velY;
		}
	}


}


//--------------------------------------------------------------------------
/// general update method.
//--------------------------------------------------------------------------
void cEntity::update ()
{

	int a = 0;
	
	/*switch (m_type)
	{

		case GAMESPRITE_CLOUD:

			process_move( m_velX, m_velY, true );

			if(m_posX < -35) //LEFT MOVE
			{
				m_posX = g_pGame->m_tileMapW*TILE_W;
				m_velX = g_pGame->random(1,2);
			}	
			else if(m_posX > g_pGame->m_tileMapW*TILE_W ) //RIGHT MOVE
			{
				m_posX = -35;
				m_velX = g_pGame->random(1,2);
			}

			break;

		case GAMESPRITE_BUG:
		case GAMESPRITE_MOUSE:
			{			

				if ( m_state != STATE_ENTITY_DEATH )
				{
						int rect[4];// = GL_NEW int[RECT::k_size];

						boolean _change_direct = false;
						boolean _area_direct = false;

						rect[RECT::k_x] = -3;
						rect[RECT::k_y] = -3;
						rect[RECT::k_w] = 3;
						rect[RECT::k_h] = 3;

						process_move( m_velX, m_velX, true );

						int _col_tile = g_pGame->canDropObject(rect,m_posX,m_posY);//check_move( this, m_posX, m_posY );

						if( _col_tile > COL_TILES::k_can_move)
						{
							_change_direct = true;
						}

						if(collisionObject_UserRect(GAMESPRITE_MAIN_CHAR,60,60))// CRASH RUN 
						{
							if ( m_supportTime == 0 )
							{
								_area_direct = true;
							}
							m_supportTime = 10;
						}

						m_supportTime--;
						if ( m_supportTime < 0 )
						{
							m_supportTime = 0;
						}

						if ( _change_direct || _area_direct ) 
						{

							process_move( m_velX, m_velX, false );

							m_velX = g_pGame->random(1,2);

							if ( _area_direct || m_supportTime > 0 )
							{
								m_velX += 4;
							}

							if( m_type == GAMESPRITE_MOUSE )
							{
								m_velX += 3;
							}

							m_dir = g_pGame->except_random( DIRECT_LEFT, DIRECT_DOWN, m_dir );

							setAnim (ETCSLOT::k_slot_boby, ANIM_BUG_WALK_LEFT+(m_dir-1) );
						}
						// CRASH DEATH 
						if(collisionObject_UserRect(GAMESPRITE_MAIN_CHAR,10,10) && g_pGame->getEntity(GAMESPRITE_MAIN_CHAR)->m_dir != DIRECT_NULL  )
						{
						//	isAnimOver (ETCSLOT::k_slot_boby)
							m_state = STATE_ENTITY_DEATH;
							setAniLoop (ETCSLOT::k_slot_boby ,false );
							setAnim (ETCSLOT::k_slot_boby, ANIM_BUG_DEATH_LEFT+(m_dir-1) );
						}

						//SAFE_DELETE_ARRAY(rect);
				}
				else // PRROCESS DEATH 
				{
					if ( isAnimOver (ETCSLOT::k_slot_boby) )
					{
						setFlag(DFLAGS::HIDE_LAYER);
					}
				}
				break;
			}

		case GAMESPRITE_FISH:
			{
				Update_Fish();

				break;
			}
	}*/

}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY UTILITIES ENTITY UTILITIES ENTITY UTILITIES ENTITY UTILITIES
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//--------------------------------------------------------------------------
/// change animation method.
///
/// @param slot_idx
/// @param anim_idx
//--------------------------------------------------------------------------
void cEntity::setFrame (int slot_idx, int afra_idx)
{

	if (afra_idx == ANIM_EMPTY)
	{
		m_renderer[slot_idx]->m_nCrtFrame = ANIM_EMPTY;
		return;
	}

	m_renderer[slot_idx]->SetFrame(afra_idx);

}

// TODO_LOLO => add some asserts in debug mode.
bool cEntity::setAnim (int slot_idx, int anim_idx)
{
	if (anim_idx == ANIM_EMPTY)
	{
		m_renderer[slot_idx]->m_nCrtModule = ANIM_EMPTY;
		return true;
	}

	// set GL_NEW animation.
	return m_renderer[slot_idx]->SetAnim(anim_idx);
}

//--------------------------------------------------------------------------
/// change animation method.
///
/// @param slot_idx
/// @param anim_idx
//--------------------------------------------------------------------------
void cEntity::setAniLoop (int slot_idx , bool _loop)
{
	m_renderer[slot_idx]->SetAniLoop(_loop);
}


void cEntity::setAnimNoReset (int slot_idx, int anim_idx)
{
	if (anim_idx == ANIM_EMPTY)
	{
		m_renderer[slot_idx]->m_nCrtModule = ANIM_EMPTY;
		return;
	}

	int aframe 	= m_renderer[slot_idx]->m_nCrtFrame;
	int time	= m_renderer[slot_idx]->m_nCrtAnimation;

	// set GL_NEW animation.
	m_renderer[slot_idx]->SetAnim(anim_idx);
	m_renderer[slot_idx]->m_nCrtFrame	= aframe;
	m_renderer[slot_idx]->m_nCrtAnimation		= time;
}


void cEntity::setSpriteLayer (int slot_idx, int layer)
{
	if (slot_idx < 0)
	{
		// loop trough all entity's renderers and apply flags.
		for (int i = 0; i < m_renderer_length/*m_renderer.length*/; i++)
		{
			if (m_renderer[i] != NULL)
			{
				//m_renderer[i]->m_savedLayer = m_renderer[i]->m_layer;
				//m_renderer[i]->m_layer = layer;
			}
		}
	}
	else
	{
		//m_renderer[slot_idx]->m_savedLayer = m_renderer[slot_idx]->m_layer;
		//m_renderer[slot_idx]->m_layer = layer;
	}
}

void cEntity::resetSpriteLayer(int slot_idx)
{
	if (slot_idx < 0)
	{
		// loop trough all entity's renderers and apply flags.
		for (int i = 0; i < m_renderer_length/*m_renderer.length*/; i++)
		{
			if ((m_renderer[i] != NULL) && (m_renderer[i]->m_savedLayer != -1))
			{
				//m_renderer[i]->m_layer = m_renderer[i]->m_savedLayer;
				//m_renderer[i]->m_savedLayer = -1;
			}
		}
	}
	else
	{
		if (m_renderer[slot_idx]->m_savedLayer != -1)
		{
			//m_renderer[slot_idx]->m_layer = m_renderer[slot_idx]->m_savedLayer;
			//m_renderer[slot_idx]->m_savedLayer = -1;
		}
	}
}
//--------------------------------------------------------------------------
/// apply sprite flags to the specified renderers.
///
/// @param slot_idx
/// @param flags
//--------------------------------------------------------------------------
// TODO_LOLO => add some asserts in debug mode.
void cEntity::setSpriteFlag (int slot_idx, int flags)
{
	if (slot_idx < 0)
	{
		// loop trough all entity's renderers and apply flags.
		for (int i = 0; i < m_renderer_length/*m_renderer.length*/; i++)
		{
			m_renderer[i]->m_flags |= flags;
		} 
	}
	else
	{
		m_renderer[slot_idx]->m_flags |= flags;
	}
}

//--------------------------------------------------------------------------
/// remove sprite flags from the specified renderers.
///
/// @param slot_idx
/// @param flags
//--------------------------------------------------------------------------
// TODO_LOLO => add some asserts in debug mode.
void cEntity::unsetSpriteFlag (int slot_idx, int flags)
{
	if (slot_idx < 0)
	{
		// loop trough all entity's renderers and remove flags.
		for (int i = 0; i < m_renderer_length/*m_renderer.length*/; i++)
		{
			m_renderer[i]->m_flags &= ~flags;
		}
	}
	else
	{
		m_renderer[slot_idx]->m_flags &= ~flags;
	}
}



int* cEntity::GetRect(int slot_idx){

	//if( m_renderer[slot_idx] == NULL ) return NULL;	
	if( m_renderer == NULL ) return NULL;

	if (m_renderer[slot_idx]->m_nCrtModule == ANIM_EMPTY)
	{			
		return NULL;
	}

	return m_renderer[slot_idx]->GetRect(true);
}

int* cEntity::GetAbsoluteRect(int slot_idx)
{
	if (m_renderer[slot_idx]->m_nCrtModule == ANIM_EMPTY)
	{			
		return NULL;
	}

	//return m_renderer[slot_idx]->GetAbsoluteRect(true);		
	return m_renderer[slot_idx]->GetAbsoluteRect(false);		

}

int* cEntity::GetFModuleRect(int slot_idx , int module)
{

	if (m_renderer[slot_idx]->m_nCrtModule == ANIM_EMPTY)
	{			
		return NULL;
	}

	return m_renderer[slot_idx]->GetFModuleRect(module,0,0,0,0,0);//int module,int posX, int posY, int flags, int hx, int hy		

}


void cEntity::setAnimStop (int slot_idx)
{
	ASpriteInstance* si = m_renderer[slot_idx];

	if (si->m_nCrtModule == ANIM_EMPTY)
		return ;

	si->setAnimStop();
}

//--------------------------------------------------------------------------
/// is the current animation over ?
///
/// @param slot_idx
//--------------------------------------------------------------------------
// TODO_LOLO => add some asserts in debug mode.
bool cEntity::isAnimOver (int slot_idx)
{
	ASpriteInstance* si = m_renderer[slot_idx];

	if (si->m_nCrtModule == ANIM_EMPTY)
		return true;

	return si->IsAnimEnded();
}

//--------------------------------------------------------------------------
/// is this the current animation ?
///
/// @param slot_idx
//--------------------------------------------------------------------------
// TODO_LOLO => add some asserts in debug mode.
// NOTE: M-O: Moved to Macro.h
int cEntity::getCurrentAnim (int slot_idx)
{
	ASpriteInstance* si = m_renderer[slot_idx];

	return si->m_nCrtModule;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ENTITY Updata,
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void cEntity::Update_Fish()
{

	//if ((m_renderer[ETCSLOT::k_slot_boby]->m_flags & FLAG_DONTDRAW) != 0)
	//{

	//	m_supportTime++;
	//	if(m_supportTime >= ( m_params[PAR_PROBABILITY]/100 )) // m_params*
	//	{
	//		if(g_pGame->random(0,100) < m_params[PAR_PROBABILITY]%100 )
	//		{
	//			set_fish();
	//		}
	//		else
	//		{
	//			m_supportTime = 0;
	//		}
	//	}
	//	return;
	//}
	//
	//m_supportTime--;
	//m_dirNotCollCnt++;
	//if( m_dir == DIRECT_LEFT )
	//{
	//	m_posX -= m_velX;
	//	m_dirCount++;			
	//	if(  (m_posX < -30 && m_supportTime > 0) || ( m_dirCount > 50 ) )
	//	{
	//		if( m_posX < -30 || g_pGame->random(0,100) < 30){
	//			m_dir = DIRECT_LEFTTORIGHT;
	//			//m_velX = g_pGame->random(1,2);
	//			setAnim (ETCSLOT::k_slot_boby, ANIM_FISH_SMALL_LEFT_RIGHT + ANIM_FISH_BIG_LEFT * m_params[PAR_PATROL_X1]);
	//		}
	//		m_dirCount = 0;
	//	}
	//	else if(m_posX < -20 && m_supportTime < 0 )
	//	{
	//		//hide
	//		setSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);
	//	}
	//}
	//else if( m_dir == DIRECT_RIGHT )
	//{
	//	m_posX += m_velX;
	//	m_dirCount++;		
	//	if( (m_posX > g_pGame->m_tileMapW*TILE_W + 30 && m_supportTime > 0 ) || ( m_dirCount > 50 ) )
	//	{
	//		if( m_posX >  g_pGame->m_tileMapW*TILE_W + 30 || g_pGame->random(0,100) < 30){
	//			m_dir = DIRECT_RIGHTTOLEFT;
	//			//m_velX = g_pGame->random(1,2);
	//			setAnim (ETCSLOT::k_slot_boby, ANIM_FISH_SMALL_RIGHT_LEFT + ANIM_FISH_BIG_LEFT* m_params[PAR_PATROL_X1]);
	//		}
	//		m_dirCount = 0;
	//	}
	//	else if(m_posX > g_pGame->m_tileMapW*TILE_W + 20 && m_supportTime < 0 )
	//	{
	//		//hide
	//		setSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);
	//	}
	//}
	//else if( m_dir == DIRECT_LEFTTORIGHT  )
	//{
	//	if(  (m_posX < -5 ) || (m_posX > g_pGame->m_tileMapW*TILE_W + 5 ) )
	//	{
	//		m_dirNotCollCnt = 50;
	//		m_renderer[ETCSLOT::k_slot_boby]->UpdateSpriteAnim();
	//	}

	//	if(isAnimOver(ETCSLOT::k_slot_boby))
	//	{
	//		m_dir = DIRECT_RIGHT;
	//		m_velX = m_params[PAR_VEL]/10 + g_pGame->random(0,(m_params[PAR_VEL]%10 - m_params[PAR_VEL]/10) );
	//		setAnim (ETCSLOT::k_slot_boby, (m_dir-1) + ANIM_FISH_BIG_LEFT* m_params[PAR_PATROL_X1] );
	//	}		

	//}
	//else if( m_dir == DIRECT_RIGHTTOLEFT  )
	//{
	//	if( (m_posX > g_pGame->m_tileMapW*TILE_W + 5 ) || (m_posX < -5 ))
	//	{
	//		m_dirNotCollCnt = 50;
	//		m_renderer[ETCSLOT::k_slot_boby]->UpdateSpriteAnim();
	//	}

	//	if(isAnimOver(ETCSLOT::k_slot_boby))
	//	{
	//		m_dir = DIRECT_LEFT;
	//		m_velX = m_params[PAR_VEL]/10 + g_pGame->random(0,(m_params[PAR_VEL]%10 - m_params[PAR_VEL]/10) );
	//		setAnim (ETCSLOT::k_slot_boby, (m_dir-1) + ANIM_FISH_BIG_LEFT * m_params[PAR_PATROL_X1]);
	//	}	
	//}

	//if( m_dirNotCollCnt > 20 && collisionObject_UserRect(0,100,70))
	//{
	//	

	//	if( m_dir == DIRECT_LEFT && g_pGame->getEntity(0)->m_posX < m_posX)
	//	{
	//		m_dir = DIRECT_LEFTTORIGHT;			
	//		setAnim (ETCSLOT::k_slot_boby, ANIM_FISH_SMALL_LEFT_RIGHT + ANIM_FISH_BIG_LEFT * m_params[PAR_PATROL_X1]);
	//	}
	//	else if( m_dir == DIRECT_RIGHT && g_pGame->getEntity(0)->m_posX > m_posX )
	//	{
	//		m_dir = DIRECT_RIGHTTOLEFT;			
	//		setAnim (ETCSLOT::k_slot_boby, ANIM_FISH_SMALL_RIGHT_LEFT + ANIM_FISH_BIG_LEFT * m_params[PAR_PATROL_X1]);
	//	}

	//	m_dirCount = 0;
	//	m_dirNotCollCnt = 0;
	//}
	//
	//
	//if((g_pGame->s_cUI->sp_BFishing == 2 && collisionObject_UserRect(0,30,20)) 
	//	|| (g_pGame->s_cUI->sp_BFishing == 5 && collisionObject_UserRect(17,40,34) && g_pGame->s_cUI->fish_Catch < 1 )  )
	//{
	//	if( m_params[PAR_PATROL_Y1] < 270)
	//	{
	//		g_pGame->s_cUI->fish_Catch = 3 + g_pGame->random(0,7 - 3 );
	//	}
	//	else if( m_params[PAR_PATROL_Y1] < 340 )
	//	{
	//		g_pGame->s_cUI->fish_Catch = 8 + g_pGame->random(0,20 - 8 );
	//	}
	//	else 
	//	{
	//		g_pGame->s_cUI->fish_Catch = 21 + g_pGame->random(0,40 - 21 );
	//	}

	//	VIBRATE(500);
	//	g_pGame->s_cUI->set_init_Ball();
	//	
	//	if(g_pGame->s_cUI->sp_BFishing == 5)
	//	{
	//		g_pGame->getEntity(17)->setAniLoop(0,true);
	//		g_pGame->getEntity(17)->setAnim(0,1);			
	//	}
	//	
	//	setSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);
	//	
	//}
	//else if(g_pGame->s_cUI->sp_BFishing == 5)
	//{
	//	if(g_pGame->s_cUI->fish_Catch < 1)
	//	{
	//		g_pGame->s_cUI->fish_Catch = -1;
	//	}
	//	
	//}
}



void cEntity::set_fish()
{
	//
	//unsetSpriteFlag(ETCSLOT::k_slot_boby , FLAG_DONTDRAW);

	//m_dir = g_pGame->random(1,2);
	//
	//setAnim(ETCSLOT::k_slot_boby, (m_dir-1) + ANIM_FISH_BIG_LEFT* m_params[PAR_PATROL_X1]);

	//m_posX = (g_pGame->m_tileMapW*TILE_W + 20) -  (g_pGame->m_tileMapW*TILE_W + 20 + 20) * (m_dir-1);  
	//m_posY = m_params[PAR_PATROL_Y1] + g_pGame->random(0,(m_params[PAR_PATROL_Y2] - m_params[PAR_PATROL_Y1]) ) ;
	//m_velX = m_params[PAR_VEL]/10 + g_pGame->random(0,(m_params[PAR_VEL]%10 - m_params[PAR_VEL]/10) ); //m_params[PAR_VEL]
	////m_supportTime = 100 ; 
	//m_supportTime = m_supportTime * 4;

	////m_renderer[slot_idx]->m_flags |= FLAG_DONTDRAW;

	////if ((m_flags & FLAG_DONTDRAW) != 0)
}



#ifdef hasShine
void cEntity::PaintShine(int x, int y , int ox, int oy) 
{
	for (int k = 0; k<m_params[SHINE::m_paramY];k++)
	{  
		int _px = m_posX+k*m_params[SHINE::m_paramY2];

		if ((_px-ox) + x < -SCREEN_WIDTH/3 || (_px-ox) + x > SCREEN_WIDTH*4/3)
			continue;
		if (m_params[SHINE::m_type] != ENTITY::VALUE_SHINE_TYPE_SMAL_CYCLE)
		{  
			int i;
			//count = _rectIce->length >> 1;
			for (i = 0;i<m_params[SHINE::_rectIce_length];i+= 2) {				
				if (m_params[SHINE::m_paramX2] < 2) {//draw left
					g->DrawImage(g_pGame->_shineImgs[ m_params[SHINE::_rectIce_array+i+1] ] , m_posX - ox + x, m_params[SHINE::_rectIce_array+i] - oy + y + g_pGame->random(-1, 2), 0);
					//g_pGame->DrawImage(g_pGame->_shineImgs[_rectIce[i+1]], m_pX - g_pGame->s_cameraX, _rectIce[i] - g_pGame->s_cameraY + g_pGame->Rand(-1, 2), 0);
				}
				if (m_params[SHINE::m_paramX2] != 1) {//draw right
					g->DrawImage(g_pGame->_shineImgs[ m_params[SHINE::_rectIce_array+i+1] ], m_posX + m_params[SHINE::m_paramX1] - ox + x, m_params[SHINE::_rectIce_array+i] - oy + y + g_pGame->random(-1, 2), 0);
				}
			}
		}
		else
		{
			//g_pGame->s_sprites[DATA::SPRITE_EFFECT_LIGHT]->PaintAFrame(g_pGame->s_g, 0,(g_pGame->s_frameCounter%2),_px-g_pGame->s_cameraX, m_pY-g_pGame->s_cameraY, 0,  0, 0);
		}  
	}
}
#endif //hasShine


///////////////////////////////////////////////////////////////////////
//*
///////////////////////////////////////////////////////////////////////
bool cEntity::collisionObject_UserRect(int _entity_Num, int w, int h){

	int rect[4];
	
	rect[0] = g_pGame->getEntity(_entity_Num)->m_posX - ((w>>1)*TILE_W/20);
	rect[1] = g_pGame->getEntity(_entity_Num)->m_posY - ((h>>1)*TILE_W/20);
	rect[2] = w*TILE_W/20;
	rect[3] = h*TILE_W/20;

	return g_pGame->collisionDetection (rect, m_posX, m_posY);
}

bool cEntity::chcekBolck()
{
	if (m_params[PAR_PATROL_X1] > -1 && (m_posX < m_params[PAR_PATROL_X1] ||  m_posX > m_params[PAR_PATROL_X2]) )
	{
		return true;
	}
	else if (m_params[PAR_PATROL_Y1] > -1 && (m_posY < m_params[PAR_PATROL_Y1] || m_posY > m_params[PAR_PATROL_Y2]) )
	{
		return true;
	}
	return false;
}

int cEntity::directChange(int _slot,int _direct, int* _temp_direct, int* ani)
{	
	//int _temp_direct_length = m_stateArry_length;//Chen Shoutian
	//int* temp_direct = GL_NEW int[m_stateArry_length];

	//for(int i = 0 ; i < _temp_direct_length - 1 ; i++)
	//{
	//	if(_temp_direct[i] >= _direct){
	//		temp_direct[i] = _temp_direct[i+1];

	//	}
	//	else
	//	{
	//		temp_direct[i] = _temp_direct[i];
	//	}
	//}


	//int temp = temp_direct[g_pGame->random(0,(_temp_direct_length-2))];
	//if(temp == 0){
	//	setAnim(_slot,ani[temp] );//+ move_direct);
	//}else{
	//	setAnim(_slot,ani[temp]);
	//}

	//SAFE_DELETE_ARRAY(temp_direct);
	//return temp;
	return 0;
}



#include "Cinematic.h"


//--------------------------------------------------------------------------
cCinematic::cCinematic(void* _sASpriteSet)
//--------------------------------------------------------------------------
{
	s_ASpriteSet = (ASpriteSet*)_sASpriteSet;
}


//--------------------------------------------------------------------------
cCinematic::~cCinematic()
//--------------------------------------------------------------------------
{
	Release_Cinematics();
}


//--------------------------------------------------------------------------
void cCinematic::Load_Cinematics(char* _packtype, int _DataNum, int nextEvtcode, Field*	_pField)
//--------------------------------------------------------------------------
{
	//필드의 카메라를 일치시켜준다.
	//m_mapX = _pField->m_nSrcCamAngle_X;
	m_mapX = 0;
	m_nTheaterTimer = 0;

//	m_nReadyCinemaCount = 10;
//	m_nEndCinemaCount = 0;
	m_nNextEventCode = nextEvtcode;

	m_IsPlayCinema = true;
	m_IsSendEndEvt = false;

	byte* data = NULL;

//	SUTIL_Data_open(packIndex);
	SUTIL_Data_init(_packtype);
	data = SUTIL_Data_readAll(_DataNum);
	SUTIL_Data_free();

	int pos = 0;
	short cin_nums = data[pos++];

	s_cinematics = GL_NEW byte**[cin_nums];
	s_cinematics_sz_len = GL_NEW int[cin_nums];
	s_cinematics_sz2_len = GL_NEW int*[cin_nums];


	s_cinematicsId = GL_NEW short[cin_nums];
	s_cinematicsId_len = cin_nums;
	s_currentFramePos = GL_NEW int*[cin_nums];

//	s_runningCinematicTrackActors = GL_NEW int*[cin_nums];

	m_ASpriteIns = GL_NEW ASpriteInstance**[cin_nums];
	m_bIsFlag = GL_NEW CFlag*[cin_nums];


//	Init_Asprite ( cin_nums );

	for (int c = 0; c < cin_nums; c++)
	{
		s_cinematicsId[c] = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));

		pos += 2;

		byte tracks_nums = data[pos++];	

		s_tracks_nums = tracks_nums;

		pos += 2; //skip cinematic_number_of_key_frames

		s_cinematics[c] = GL_NEW byte*[tracks_nums];
		s_cinematics_sz2_len[c] = GL_NEW int[tracks_nums];
		s_cinematics_sz_len[c] = tracks_nums;
		s_currentFramePos[c] = GL_NEW int[tracks_nums];
		m_ASpriteIns[c] = GL_NEW ASpriteInstance*[tracks_nums];
		m_bIsFlag[c] = GL_NEW CFlag[tracks_nums];
//		s_runningCinematicTrackActors[c] = GL_NEW int[tracks_nums];

		s_infoasprite = GL_NEW int*[tracks_nums];
		s_infoasprite_len = tracks_nums;
		for (int t = 0; t < tracks_nums; t++)
		{
			m_ASpriteIns[c][t] = NULL;

			m_bIsFlag[c][t].m_IsShadow = NULL;
			m_bIsFlag[c][t].m_IsPauseAnim = NULL;
			m_bIsFlag[c][t].m_IsInvisible = NULL;

			s_infoasprite[t] = NULL;
			s_infoasprite[t] = GL_NEW int[4]; //sprite,ani,x,y

			//s_infoasprite = GL_NEW int[tracks_nums];

			int track_start = pos;
			byte track_type = data[pos++];
			byte a = pos++; //skip track_flags

			

			switch (track_type)
			{
				case CTRACK_BASIC:
				case CTRACK_CAMERA:
				//------------------------------------------------------
				{
//					Set_MatchAsprite( 0 , t );
					break;
				}
				case CTRACK_OBJ_LAYER:
				//------------------------------------------------------
				{
					int uid = (data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8);
//					s_runningCinematicTrackActors[c][t] = uid;
					pos += 2; // skip track_object_layer_id

					//	스프라이트를 로드시킨다.
//					m_ASpriteIns[c][t] = LoadSpriteInstance(uid);
					break;
				}
			}

//			Set_MatchAsprite( s_runningCinematicTrackActors[c][t] , t ); //Actor NUM , tracks_nums

			short key_frames_nums = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
			pos += 2;
			int keyframe_start = pos;

			for (int k = 0; k < key_frames_nums; k++)
			{
				pos += 2; //skip key_frame_time

				byte commands_nums = data[pos++];

				for (int l = 0; l < commands_nums; l++)
				{						
					byte cmd_type = data[pos++];	                    

					if(cmd_type >= CCMD_FIRST_CUSTOM)
					{
						//	//dbg("READING CUSTOM PARAM" + cmd_type + " " + GetCustomCinematicCommandNumParams(cmd_type));
						//	pos += GetCustomCinematicCommandNumParams(cmd_type);
					}
					else
					{
						switch (cmd_type)
						{
							case CCMD_CAMERA_SET_POS:
							case CCMD_CAMERA_CENTER_TO:
							case CCMD_OBJ_LAYER_SET_POS:
							case CCMD_BASIC_SET_POS:
							case CCMD_SI_SET_POS:
							//-------------------------------------------------------------
							{
								pos += 2; //skip key_frame_cmd_x
								pos += 2; //skip key_frame_cmd_y
								break;
							}
							case CCMD_CAMERA_FOCUS_ON:
							//-------------------------------------------------------------
							{
								pos += 1;  //skip Thread to follow,
								pos += 2;  //skip OffsetY
								pos += 2;  //skip OffsetY
								break;							
							}
							case CCMD_BASIC_SET_ACTION:
							//-------------------------------------------------------------
							{
								pos += 2; // skip key_frame_cmd_anim
								break;
							}
							case CCMD_OBJ_LAYER_SET_ANIM:
							case CCMD_SI_SET_ANIM:
							//-------------------------------------------------------------
							{
								pos++; // skip key_frame_cmd_anim
								break;
							}
							case CCMD_OBJ_LAYER_ADD_FLAGS:
							case CCMD_OBJ_LAYER_REMOVE_FLAGS:
							case CCMD_SI_ADD_FLAGS:
							case CCMD_SI_REMOVE_FLAGS:
							//-------------------------------------------------------------
							{
								pos += 4; // skip key_frame_cmd_flags
								break;
							}
							case CCMD_BASIC_OBJEVENT1:		{pos += 2;		break;}
							case CCMD_BASIC_OBJEVENT2:		{pos += 4;		break;}
							case CCMD_BASIC_OBJEVENT3:		{pos += 6;		break;}
							case CCMD_BASIC_EVENT1:			{pos += 2;		break;}
							case CCMD_BASIC_EVENT2:			{pos += 4;		break;}
							case CCMD_BASIC_EVENT3:			{pos += 6;		break;}
							default:
							//-------------------------------------------------------------
							{
								//	//dbg("Unknown command type " + cmd_type);
								//	//dbg("Current pos " + pos);									
								break;
							}
						}//End Switch
					}// End if(cmd_type)
				}//End for (int l = 0; l < commands_nums; l++) 
			}//End for (int k = 0; k < key_frames_nums; k++)

			int track_length = pos - track_start;

			s_cinematics[c][t] = GL_NEW byte[track_length + 2]; //2 more byte to store pos for use when reset
			s_cinematics_sz2_len[c][t] = track_length + 2;


			s_currentFramePos[c][t] = keyframe_start - track_start; //start key frame offset to track data
			//System.arraycopy(data, track_start, s_cinematics[c][t], 0, track_length);
			MEMCPY(s_cinematics[c][t],data+track_start,sizeof(byte)*track_length);
			s_cinematics[c][t][track_length] = (byte)(s_currentFramePos[c][t] & 0xFF);
			s_cinematics[c][t][track_length + 1] = (byte)((s_currentFramePos[c][t] >> 8) & 0xFF);

		}
		
	}

	SAFE_DELETE_ARRAY(s_cinematicsFrameTime);
	s_cinematicsFrameTime = GL_NEW short[cin_nums];
	s_cinematicsFrameTime_len = cin_nums;
///	Reset_Cinematics();

	SAFE_DELETE(data);

	//	필드 추가
	pField = _pField;

	//	한 프레임을 추가시켜서 리소스를 등록한다.
	Update_Cinematics();
}



//--------------------------------------------------------------------------
void cCinematic::Update_Cinematics()
//--------------------------------------------------------------------------
{
	bool isObjEvent = false;

	//	퍼즈상태일 경우는 에니메이션만 돌려준다.
	if(true == s_cinematicsPause)
	{
		for (int c = 0; c < s_cinematicsId_len; c++)
		{
			for (int t = 0; t < s_cinematics_sz_len[c]; t++)
			{
				if(NULL != m_ASpriteIns[c][t])
				{

					if(false == m_bIsFlag[c][t].m_IsPauseAnim)
					{
						SUTIL_UpdateTimeAsprite(m_ASpriteIns[c][t]);
					}
				}
			}
		}
		// 배경은 자동갱신되므로 따로 처리하지 않는다.
		return;
	}

	for (int c = 0; c < s_cinematicsId_len; c++)
	{
		s_param1 = s_param2 =  s_param3 = -1;
		if (s_cinematicsFrameTime[c] >= 0)
		{
			bool cinematicEnd = true;
			byte** currentCinematic = s_cinematics[c];
			int current_frame_time = s_cinematicsFrameTime[c]++;

			for (int t = 0; t < s_cinematics_sz_len[c]; t++)
			{
				//int uid;
				int pos = 0;
				byte* data = currentCinematic[t];
				if (s_currentFramePos[c][t] >= s_cinematics_sz2_len[c][t] - 2)
				{
					continue;
				}

				byte track_type = data[pos++];
				byte track_flags = data[pos++];

				switch (track_type)
				{
					case CTRACK_BASIC:
					//-------------------------------------------------------------
					{
						break;
					}
					case CTRACK_CAMERA:
					//-------------------------------------------------------------
					{
						break;
					}
					case CTRACK_OBJ_LAYER:
					//-------------------------------------------------------------
					{
						pos += 2;						
						break;
					}
				}

				pos = s_currentFramePos[c][t];
				int nextPosX = 0, nextPosY = 0, nextPosFrameTime = -1;
				short key_frame_time = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));

				pos += 2;
				byte command_nums = data[pos++];
				isObjEvent = false;
				byte cmd_type = 0;
				for (int k = 0; k < command_nums; k++)
				{
					cmd_type = data[pos++];

					if(cmd_type >= CCMD_FIRST_CUSTOM)
					{
						//pos += ExecuteCustomCinematicCommand(cmd_type, data, pos, current_frame_time, key_frame_time);
						continue;
					}

					isObjEvent = false;

					switch (cmd_type)
					{
						case CCMD_CAMERA_SET_POS:
						case CCMD_CAMERA_CENTER_TO:
						case CCMD_OBJ_LAYER_SET_POS:
						case CCMD_BASIC_SET_POS:
						case CCMD_SI_SET_POS:
						//-------------------------------------------------------------------
						{
							int cmd_x = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
							pos += 2;
							int cmd_y = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
							pos += 2;

							if(0 == current_frame_time && cmd_type == CCMD_OBJ_LAYER_SET_POS)
							{
								//	스프라이트를 로드시킨다.
								LoadSpriteInstance(c, t, cmd_x, cmd_y);

								int a = 0;
							}
							else
							{
								if(cmd_x == -1)	//use current position X
								{
									if ( s_infoasprite[t][0] > -1 )
									{
										cmd_x = s_infoasprite[t][2];
									}
								}

								if(cmd_y == -1)	//use current position in Y
								{

									if ( s_infoasprite[t][0] > -1 )
									{
										cmd_y = s_infoasprite[t][3];
									}
								}						


								if (current_frame_time <= key_frame_time)
								{
									nextPosX = cmd_x;
									nextPosY = cmd_y;

									nextPosFrameTime = key_frame_time;	
								}							
							}
							break;
						}
						case CCMD_CAMERA_FOCUS_ON:
						//-------------------------------------------------------------------
						{
							short focusedActorID = (short)(data[pos++] & 0xFF);
							short OffsetX = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
							pos += 2;
							short OffsetY = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
							pos += 2;
							if (current_frame_time <= key_frame_time)
							{
								//note : REMOVE THIS SPECIAL CASE HACK, I'm just not sure yet the newer code (in the else)
								// works for flying levels made in china...  (the focusedActorID == 1) is sort of cryptik.

								nextPosX += OffsetX;
								nextPosY += OffsetY;															

								nextPosFrameTime = key_frame_time;
							}	
							break;								
						}
						case CCMD_OBJ_LAYER_SET_ANIM:
						case CCMD_BASIC_SET_ACTION:
						case CCMD_SI_SET_ANIM:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								byte anim = data[pos];									
								if ( s_infoasprite[t][0] > -1 )
								{	
									s_infoasprite[t][1] = anim;
									SUTIL_SetTypeAniAsprite(m_ASpriteIns[c][t], s_infoasprite[t][1]);	
	//								s_ASprite[s_infoasprite[t][0]]->SetCurrentAnimation(s_infoasprite[t][1], anim, true );
								}
							}
							pos++;

							break;
						}

						case CCMD_OBJ_LAYER_ADD_FLAGS:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								if(data[pos++])		//	flipx
								{
									SUTIL_SetDirAsprite(m_ASpriteIns[c][t], SDIR_LEFT);
								}

								if(data[pos++])		//	flipy
								{
									//SUTIL_SetDirAsprite(m_ASpriteIns[c][t], SDIR_LEFT);
								}

								if(data[pos++])		//	invisi
								{
									m_bIsFlag[c][t].m_IsInvisible = true;
								}

								if(data[pos++])		//	pauseAnim
								{
									m_bIsFlag[c][t].m_IsPauseAnim = true;
								}
							}
							//pos += 4;
							break;
						}
						case CCMD_SI_ADD_FLAGS:
						//-------------------------------------------------------------------
						{
							pos += 4;
							break;
						}

						case CCMD_OBJ_LAYER_REMOVE_FLAGS:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
//								if( (C_FLAG_FLIP_X & data[pos]) )
//								{
//									SUTIL_SetDirAsprite(m_ASpriteIns[c][t], SDIR_RIGHT);
//								}

								if(data[pos++])		//	flipx
								{
									SUTIL_SetDirAsprite(m_ASpriteIns[c][t], SDIR_RIGHT);
								}

								if(data[pos++])		//	flipy
								{
									//SUTIL_SetDirAsprite(m_ASpriteIns[c][t], SDIR_RIGHT);
								}

								if(data[pos++])		//	invisi
								{
									m_bIsFlag[c][t].m_IsInvisible = false;
								}

								if(data[pos++])		//	pauseAnim
								{
									m_bIsFlag[c][t].m_IsPauseAnim = false;
								}
							}
							
							pos += 4;
							break;
						}
						case CCMD_SI_REMOVE_FLAGS:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								if( (C_FLAG_FLIP_X & data[pos]) )
								{
									SUTIL_SetDirAsprite(m_ASpriteIns[c][t], SDIR_RIGHT);
								}
							}
							
							pos += 4;
							break;
						}
						case CCMD_BASIC_OBJEVENT1:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								int a = 0;
							}
							pos += 2;
							break;
						}
						case CCMD_BASIC_OBJEVENT2:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								int a = 0;
							}
							pos += 4;
							break;
						}
						case CCMD_BASIC_OBJEVENT3:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								int a = 0;
							}
							pos += 6;
							break;
						}

						case CCMD_BASIC_EVENT1:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								short evtcode1 = (short)((data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
								ADD_EVENT_MSG(EVT_CINEMA_ADDEVT, 0, evtcode1);
							}

							pos += 2;
							break;
						}
						case CCMD_BASIC_EVENT2:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								short evtcode1 = (short)((data[pos    ] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
								short evtcode2 = (short)((data[pos + 2] & 0xFF) + ((data[pos + 3] & 0xFF) << 8));
								ADD_EVENT_MSG(EVT_CINEMA_ADDEVT, 0, evtcode1, evtcode2);
							}

							pos += 4;
							break;
						}
						case CCMD_BASIC_EVENT3:
						//-------------------------------------------------------------------
						{
							if (key_frame_time <= current_frame_time)
							{
								short evtcode1 = (short)((data[pos    ] & 0xFF) + ((data[pos + 1] & 0xFF) << 8));
								short evtcode2 = (short)((data[pos + 2] & 0xFF) + ((data[pos + 3] & 0xFF) << 8));
								short evtcode3 = (short)((data[pos + 4] & 0xFF) + ((data[pos + 5] & 0xFF) << 8));
								ADD_EVENT_MSG(EVT_CINEMA_ADDEVT, 0, evtcode1, evtcode2, evtcode3);
							}

							pos += 6;
							break;
						}
					}
				}//end of command

				if (key_frame_time == current_frame_time)
				{
					s_currentFramePos[c][t] = pos;
				}
				else if (key_frame_time < current_frame_time)
				{
					//bug:this may occour, sames like Aurola bug.
					s_currentFramePos[c][t] = pos;
				}

				if (s_currentFramePos[c][t] < s_cinematics_sz2_len[c][t] - 2)
				{
					cinematicEnd = false;
				}

				if (nextPosFrameTime >= 0)
				{
					if ( track_type == CTRACK_CAMERA )
					{
						if (nextPosFrameTime >= 0) {
							if( cmd_type == CCMD_CAMERA_FOCUS_ON )
							{
								m_mapX = nextPosX;//ConstraintToRange( nextPosX, cGame.VIEWPORT_WIDTH_HALF, s_mapWidth - cGame.VIEWPORT_WIDTH_HALF);
								m_mapY = nextPosY;//ConstraintToRange( nextPosY, cGame.VIEWPORT_HEIGHT_HALF, s_mapHeight - cGame.VIEWPORT_HEIGHT_HALF);

								if(pField)
								{
									pField->SetCamera(m_mapX+120);
								}

								//		//dbg("_CAMERA_FOCUS_ON   m_mapX = "+ m_mapX + "m_mapY = "+m_mapY);
							}
							else
							{
								int offsetX = (nextPosX - m_mapX) / (nextPosFrameTime - current_frame_time + 1);
								int offsetY = (nextPosY - m_mapY) / (nextPosFrameTime - current_frame_time + 1);									
								m_mapX = m_mapX + offsetX;//ConstraintToRange( m_mapX + offsetX, 0, cGame.m_tileMapW*DEF.TILE_W - m_pGame->width );
								m_mapY = m_mapY + offsetY;//ConstraintToRange( m_mapY + offsetY, 0, cGame.m_tileMapH*DEF.TILE_H - m_pGame->height );

								if(pField)
								{
									pField->SetCamera(m_mapX+120);
								}

								//		//dbg("_CAMERA_OTHER   m_mapX = "+ m_mapX + "m_mapY = "+m_mapY);
							}
						}
					}

					if ( track_type != CTRACK_CAMERA )
					{	

						if ( s_infoasprite[t][0] > -1 && s_infoasprite[t][1] > -1 )
						{
							//asp.UpdateSpriteAnim( );
							if ( s_infoasprite[t][0] > -1 )
							{	
								s_infoasprite[t][2] += (nextPosX - s_infoasprite[t][2]) / (nextPosFrameTime - current_frame_time + 1);
								s_infoasprite[t][3] += (nextPosY - s_infoasprite[t][3]) / (nextPosFrameTime - current_frame_time + 1);

								if(false == m_bIsFlag[c][t].m_IsPauseAnim)
								{
									SUTIL_UpdateTimeAsprite(m_ASpriteIns[c][t]);
								}
								//SUTIL_SetTypeAniAsprite(m_ASpriteIns[c][t], s_infoasprite[t][1]);	
//								s_ASprite[s_infoasprite[t][0]]->UpdateAnimation( s_infoasprite[t][1] );
							}
						}
					}
				}
			} // end of track

			if (cinematicEnd)
			{
				if(false == m_IsSendEndEvt)
				{
					m_IsSendEndEvt = true;
					ADD_EVENT_MSG(EVT_SCREEN_FADE_OUT, 0, 10);
					ADD_EVENT_MSG(EVT_END_CINEMA, 10, m_nNextEventCode);
				}
//				m_nEndCinemaCount = 10;
//				return 0;
///				EndCinematic(c);					
			}
		}// end of if cinema is running
	}// end of cinema

	if(pField)	{pField->Process();}

	return;
}

//--------------------------------------------------------------------------
void cCinematic::Paint_Cinematics()
//--------------------------------------------------------------------------
{
	if(pField)	{pField->Paint(true);}

	for (int c = 0; c < s_cinematicsId_len; c++)
	{
		for (int t = 0; t < s_cinematics_sz_len[c]; t++)
		{
			if(true == m_bIsFlag[c][t].m_IsInvisible )	{continue;}

			//	이미지
			if(NULL != m_ASpriteIns[c][t])
			{
				SUTIL_SetXPosAsprite(m_ASpriteIns[c][t], s_infoasprite[t][2]-m_mapX);
				SUTIL_SetYPosAsprite(m_ASpriteIns[c][t], s_infoasprite[t][3]-m_mapY);
				SUTIL_SetZPosAsprite(m_ASpriteIns[c][t], 0);
				SUTIL_PaintAsprite(m_ASpriteIns[c][t], S_INCLUDE_SORT);
			}

			//	그림자
			if(true == m_bIsFlag[c][t].m_IsShadow)
			{
				SUTIL_Paint_Frame(s_ASpriteSet->pShadowAs, 1, m_ASpriteIns[c][t]->m_posX, m_ASpriteIns[c][t]->m_posY, m_ASpriteIns[c][t]->m_posZ);
			}
		}
	}

	if(pField)
	{
		pField->MiddlePaint();
		pField->FrontPaint();
	}

	if(16 > m_nTheaterTimer)	{m_nTheaterTimer++;}
	m_nTheaterTimer = 16;

	if(m_nTheaterTimer)
	{
		SUTIL_SetColor(0x000000);
		SUTIL_FillRect(0,0,240,m_nTheaterTimer*2);
		SUTIL_FillRect(0,296-(m_nTheaterTimer*2),240,(m_nTheaterTimer*2));
//
//		SUTIL_SetColor(0xff1010);
		SUTIL_SetColor(0x555555);
		SUTIL_DrawLine(0,m_nTheaterTimer*2,240,m_nTheaterTimer*2);
		SUTIL_DrawLine(0,296-(m_nTheaterTimer*2),240,296-(m_nTheaterTimer*2));
	}




//	if(m_nReadyCinemaCount)
///	{
//		for(int loop = 0; loop < (m_nReadyCinemaCount); loop++)
//		{
//			_SUTIL->g->blandBlur(); 
//		}
//	}
//
//	if(m_nEndCinemaCount)
//	{
//		for(int loop = 0; loop < (10-m_nEndCinemaCount); loop++)
//		{
//			_SUTIL->g->blandBlur(); 
//		}
//	}
}


//--------------------------------------------------------------------------
void cCinematic::LoadSpriteInstance(int c, int t, int uniquenum, int color)
//--------------------------------------------------------------------------
{
	ASprite* pTmpAs = NULL;
	ASpriteInstance* pTmpAsIns = NULL;

	m_bIsFlag[c][t].m_IsShadow = true;

	switch(uniquenum)
	{
		case 0:	//	HERO_MC
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE, Character::Check_sex(SPRITE_WOMAN_BODY,SPRITE_MAN_BODY));
			pTmpAs->SetBlendFrame(Character::Check_sex(FRAME_WOMAN_BODY_BLEND,FRAME_MAN_BODY_BLEND));

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			break;
		}
		case 1:	//	HERO_MPC
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE, SPRITE_MAN_BODY);
			pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			break;
		}
		case 2:	//	NPC1_BOY
		case 3:	//	NPC2
		case 4:	//	NPC3_DAEMURI_NOIN
		case 5:	//	NPC_4
		case 6:	//	NPC_5
		case 7:	//	NPC_6
		case 8:	//	NPC_7
		case 9:	//	NPC_8
		case 10://	NPC_9
		case 11://	NPC_10
		case 12://	NPC_11_SIGE
		case 13://	NPC_12_RONE
		case 14://	NPC_13
		case 15://	NPC_14_ANGELS
		case 16://	NPC_15
		case 17://	NPC_16
		case 18://	NPC_17_SIRANO
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_NPC, uniquenum-2);
//			pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			break;
		}
		case 19://	MON_COBOLT
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_MON, SPRITE_MON_BEAR);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			break;
		}
		case 20://	EFFECT
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_FIELDEFT_UI);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			m_bIsFlag[c][t].m_IsShadow = false;
			break;
		}
		case 21://	NPC18
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_NPC, SPRITE_NPC_NPC18);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			break;
		}
		case 22://	NPC19
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_NPC, SPRITE_NPC_NPC19);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			break;
		}
		case 23://	BLACKOUT
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_CINEMA, SPRITE_CINEMA_BLACKOUT);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			m_bIsFlag[c][t].m_IsShadow = false;
			break;
		}
		case 24://	EMOTION_QUEST
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_CINEMA, SPRITE_CINEMA_EMOTION_QUEST);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			m_bIsFlag[c][t].m_IsShadow = false;
			break;
		}
		case 25://	EMOTION_ETC
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_CINEMA, SPRITE_CINEMA_EMOTION_ETC);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			m_bIsFlag[c][t].m_IsShadow = false;
			break;
		}
		case 26://	UI
		//--------------------------------------------------------------------------
		{
			pTmpAs = SUTIL_LoadSprite(PACK_SPRITE_UI, SPRITE_UI_ITEM_UI);
			//pTmpAs->SetBlendFrame(FRAME_MAN_BODY_BLEND);

			pTmpAsIns = GL_NEW ASpriteInstance(pTmpAs, 0, 500, NULL);
			m_bIsFlag[c][t].m_IsShadow = false;
			break;
		}

	}

	//	컬러셋팅
	pTmpAsIns->SetAniMoveLock(true);
	pTmpAsIns->m_pal = color;
	m_ASpriteIns[c][t] = pTmpAsIns;
}


//--------------------------------------------------------------------------
void cCinematic::Release_Cinematics()
//--------------------------------------------------------------------------
{
	m_IsPlayCinema = false;

	if(NULL != s_cinematics_sz_len)
	{
		for (int c = 0; c < s_cinematicsId_len; c++)
		{
			for (int t = 0; t < s_cinematics_sz_len[c]; t++)
			{
				if(NULL != m_ASpriteIns[c][t])
				{
					SUTIL_FreeSprite(m_ASpriteIns[c][t]->m_sprite);
					SUTIL_FreeSpriteInstance(m_ASpriteIns[c][t]);
				}

//				SAFE_DELETE(m_bIsFlag[c][t]);
			}
			SAFE_DELETE(m_bIsFlag[c]);
		}

		SAFE_DELETE(m_ASpriteIns);
		SAFE_DELETE(m_bIsFlag);
	}

	//m_pGame->m_waveInitY = 0;
	if(s_cinematics)
	{
		for(int i=0 ;i<s_cinematicsId_len;i++)
		{
			SAFE_DELETE_ARRAY_ARRAY(s_cinematics[i],s_cinematics_sz_len[i]);
		}
		SAFE_DELETE_ARRAY(s_cinematics);
	}

	SAFE_DELETE_ARRAY(s_cinematics_sz_len);
	SAFE_DELETE_ARRAY_ARRAY(s_cinematics_sz2_len,s_cinematicsId_len);
	SAFE_DELETE_ARRAY(s_cinematicsId);
	SAFE_DELETE_ARRAY(s_cinematicsFrameTime);
	SAFE_DELETE_ARRAY_ARRAY(s_currentFramePos,s_cinematicsId_len);
//	SAFE_DELETE_ARRAY_ARRAY(s_runningCinematicTrackActors,s_cinematicsId_len);
//	SAFE_DELETE(Back_Img);
//	SAFE_DELETE(mascot_asp);
	SAFE_DELETE_ARRAY_ARRAY(s_infoasprite,s_infoasprite_len);	

//	SAFE_DELETE(pField);




///////////////////////


	///////////////////////////////////////////////
/*

	s_cinematics = GL_NEW byte**[cin_nums];
	s_cinematics_sz_len = GL_NEW int[cin_nums];
	s_cinematics_sz2_len = GL_NEW int*[cin_nums];


	s_cinematicsId = GL_NEW short[cin_nums];
	s_currentFramePos = GL_NEW int*[cin_nums];

	m_ASpriteIns = GL_NEW ASpriteInstance**[cin_nums];

		s_cinematics[c] = GL_NEW byte*[tracks_nums];
		s_cinematics_sz2_len[c] = GL_NEW int[tracks_nums];

		s_currentFramePos[c] = GL_NEW int[tracks_nums];
		m_ASpriteIns[c] = GL_NEW ASpriteInstance*[tracks_nums];


		s_infoasprite = GL_NEW int*[tracks_nums];
		s_infoasprite[t] = GL_NEW int[4]; //sprite,ani,x,y

		//	스프라이트를 로드시킨다.
		m_ASpriteIns[c][t] = LoadSpriteInstance(uid);
		s_cinematics[c][t] = GL_NEW byte[track_length + 2]; //2 more byte to store pos for use when reset


	SAFE_DELETE_ARRAY(s_cinematicsFrameTime);
	s_cinematicsFrameTime = GL_NEW short[cin_nums];

///	Reset_Cinematics();

	SAFE_DELETE(data);

	//	필드 추가
	pField = _pField;
*/
}


//--------------------------------------------------------------------------
void cCinematic::Pause_Cinematics()
//--------------------------------------------------------------------------
{
	s_cinematicsPause = true;
}

//--------------------------------------------------------------------------
void cCinematic::Resume_Cinematics()
//--------------------------------------------------------------------------
{
	s_cinematicsPause = false;

//	//	싱크를 맞추기 위해서 리줌을 해준다.
//	Update_Cinematics();
//	Update_Cinematics();
}









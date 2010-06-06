#include "SUtil.h"


SUtil* SUtil::pSUtil = NULL;

//--------------------------------------------------------------------------
SUtil::SUtil()
//--------------------------------------------------------------------------
{
	//	Graphics
	CGraphics& _g = GetDevice().GetScreenImage().GetGraphics();
	g = &_g;

	//	Random
	setSeed((int)SUTIL_GetTime()/1000);

	pDrawList = GL_NEW List2<ASpriteInstance*>();
//	pDrawList->delmode = 1;
//	pDrawList->SetDelMode(L_DEL_ONLY_POINTER);

	pFont = GL_NEW S_KR_Font(SCREEN_WIDTH, SCREEN_HEIGHT);

	pSound = GL_NEW CMediaPlayer();
}	


//--------------------------------------------------------------------------
SUtil::~SUtil()
//--------------------------------------------------------------------------
{
	SAFE_DELETE(pDrawList);
	SAFE_DEL(pFont);
}


//--------------------------------------------------------------------------
SUtil* SUtil::GetInstance()
//--------------------------------------------------------------------------
{
	if(NULL == pSUtil)
	{
		pSUtil = GL_NEW SUtil();
	}

	return pSUtil;
}

//--------------------------------------------------------------------------
void SUtil::FreeInstance()
//--------------------------------------------------------------------------
{
	if(NULL != pSUtil)
	{
		delete pSUtil;
		pSUtil = NULL;
	}
}


//--------------------------------------------------------------------------
int SUtil::GetSpriteDB_Index(char* _packtype, int _spriteNum)
//--------------------------------------------------------------------------
{
	int idx = 0;

	while(1)
	{	
		if( !STRCMP(_packtype, PACK_SPRITE_MAP) )		{break;}
		else											{idx+= SPRITE_MAP_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_WORLDMAP) )		{break;}
		else											{idx+= SPRITE_WORLDMAP_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_UI) )		{break;}
		else											{idx+= SPRITE_UI_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_COSTUME) )	{break;}
		else											{idx+= SPRITE_COSTUME_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE) )			{break;}
		else											{idx+= SPRITE_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_MON) )		{break;}
		else											{idx+= SPRITE_MON_MAX;}
		
		if( !STRCMP(_packtype, PACK_SPRITE_NPC) )		{break;}
		else											{idx+= SPRITE_NPC_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_FACE) )		{break;}
		else											{idx+= SPRITE_FACE_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_MAINMENU) )	{break;}
		else											{idx+= SPRITE_MAINMENU_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_LOADING) )	{break;}
		else											{idx+= SPRITE_LOADING_MAX;}

		if( !STRCMP(_packtype, PACK_SPRITE_CINEMA) )	{break;}
		else											{idx+= SPRITE_CINEMA_MAX;}

	}

	idx += _spriteNum;

	return idx;
}


//--------------------------------------------------------------------------
ASprite* SUtil::LoadAsprite(char* _packtype, int _spriteNum)
//--------------------------------------------------------------------------
{
	int idx = GetSpriteDB_Index(_packtype, _spriteNum);

	SpriteRefDB[idx] += 1;
	if(1 < SpriteRefDB[idx])	{return SpriteDB[idx];}

	byte* buf;
	//ASprite* tmpSprite = NULL;

	pGame->Data_init(_packtype);
	buf = pGame->Data_readAll(_spriteNum);
	SAFE_DEL(SpriteDB[idx]);
	SpriteDB[idx] = GL_NEW ASprite();
	SpriteDB[idx]->Load(buf, 0);
	SpriteDB[idx]->uniqueIdx = idx;
	pGame->Data_free();
	SAFE_DELETE(buf);

	return SpriteDB[idx];
}


//--------------------------------------------------------------------------
void SUtil::LoadAspritePack(char* _packtype)
//--------------------------------------------------------------------------
{
//	int idx = GetSpriteDB_Index(_packtype, _spriteNum);
//
//	SpriteRefDB[idx] += 1;
//	if(1 < SpriteRefDB[idx])	{return SpriteDB[idx];}
//
//	byte* buf;
//	//ASprite* tmpSprite = NULL;

	pGame->Data_init(_packtype);
}


//--------------------------------------------------------------------------
ASprite* SUtil::LoadAspriteFromPack(char* _packtype, int _spriteNum)
//--------------------------------------------------------------------------
{
	int idx = GetSpriteDB_Index(_packtype, _spriteNum);

	SpriteRefDB[idx] += 1;
	if(1 < SpriteRefDB[idx])	{return SpriteDB[idx];}

	byte* buf;
	//ASprite* tmpSprite = NULL;

//	pGame->Data_init(_packtype);
	buf = pGame->Data_readAll(_spriteNum);
	SAFE_DEL(SpriteDB[idx]);
	SpriteDB[idx] = GL_NEW ASprite();
	SpriteDB[idx]->Load(buf, 0);
	SpriteDB[idx]->uniqueIdx = idx;
	SAFE_DELETE(buf);

	return SpriteDB[idx];

}


//--------------------------------------------------------------------------
void SUtil::ReleaseAspritePack()
//--------------------------------------------------------------------------
{
	pGame->Data_free();
}

//--------------------------------------------------------------------------
ASpriteInstance* SUtil::LoadAspriteInstance(ASprite* _Asprite, int xPos = 0, int yPos = 0)
//--------------------------------------------------------------------------
{
	return (ASpriteInstance*)(GL_NEW ASpriteInstance(_Asprite, xPos, yPos, NULL));
}

//--------------------------------------------------------------------------
void SUtil::FreeAsprite(ASprite* _delAsprite)
//--------------------------------------------------------------------------
{
	if(NULL == _delAsprite)	{return;}

	int idx = _delAsprite->uniqueIdx;

	SpriteRefDB[idx] -= 1;

	if(1 > SpriteRefDB[idx])
	{
		SAFE_DELETE(SpriteDB[idx]);
	}
}

//--------------------------------------------------------------------------
void SUtil::FreeAspriteInstance(ASpriteInstance* _delAspriteInstance)
//--------------------------------------------------------------------------
{
	SAFE_DELETE(_delAspriteInstance);
}

//--------------------------------------------------------------------------
void SUtil::PaintAsprite(ASpriteInstance* _srcASpriteInstance, int issort)
//--------------------------------------------------------------------------
{
	if(S_NOT_INCLUDE_SORT == issort)
	{
		_srcASpriteInstance->PaintSprite(g);
	}
	else
	{
		if(0 == GetNodeCount(pDrawList))
		{
			MoveTail(pDrawList);
			pDrawList->Insert_prev(_srcASpriteInstance);
			return;
		}
		else
		{
			MoveHead(pDrawList);
			MoveNext(pDrawList);
			while(NotEndList(pDrawList))
			{
				if(GetData(pDrawList)->m_posY > _srcASpriteInstance->m_posY)
				{
					pDrawList->Insert_prev(_srcASpriteInstance);
					return;
				}
				MoveNext(pDrawList);
			}
		}

		pDrawList->Insert_prev(_srcASpriteInstance);


/*
		pDrawList->Move(L_START);
		if(0 == pDrawList->GetCount())
		{
			pDrawList->Insert(_srcASpriteInstance);
			return;
		}

		while(NULL != pDrawList->CurNode())
		{
			if(pDrawList->CurNode()->m_posY > _srcASpriteInstance->m_posY)
			{
				pDrawList->Insert(_srcASpriteInstance, L_IPRE);
				return;
			}
			if(!(pDrawList->Move(L_NEXT)))	{break;}
		}

		pDrawList->Insert(_srcASpriteInstance, L_INEXT);
*/
	}
}
//--------------------------------------------------------------------------
void SUtil::InitAni(ASprite* p_Asprite)
//--------------------------------------------------------------------------
{
	p_Asprite->InitAnimation();
}
//--------------------------------------------------------------------------
void SUtil::PaintAni(ASprite* p_Asprite, int ani, int posX, int posY, int flags/*, bool LOOP*/)
//--------------------------------------------------------------------------
{
	p_Asprite->PaintAnimation(g, ani, posX, posY, flags, 0, 0/*, LOOP*/);
}
//--------------------------------------------------------------------------
void SUtil::PaintFrame(ASprite* p_Asprite, int frame, int posX, int posY, int flags)
//--------------------------------------------------------------------------
{
	p_Asprite->PaintFrame(g, frame, posX, posY, flags, 0, 0);
}
//--------------------------------------------------------------------------
void SUtil::PaintModule(ASprite* p_Asprite, int module, int posX, int posY, int flags, int anchor)
//--------------------------------------------------------------------------
{
	p_Asprite->PaintModule(g, module, posX, posY, flags, anchor);
}

//--------------------------------------------------------------------------
void SUtil::UpdateAsprite()
//--------------------------------------------------------------------------
{
	MoveHead(pDrawList);
	MoveNext(pDrawList);
	while(NotEndList(pDrawList))
	{
		GetData(pDrawList)->PaintSprite(g);
		MoveNext(pDrawList);
	}

	MoveHead(pDrawList);
	MoveNext(pDrawList);
	while(NotEndList(pDrawList))
	{
		pDrawList->Delete();
	}



/*
	pDrawList->Move(L_START);
	while(NULL != pDrawList->CurNode())
	{
		pDrawList->CurNode()->PaintSprite(g);
		if(!(pDrawList->Move(L_NEXT)))	{break;}
	}

	pDrawList->Move(L_START);
	pDrawList->DeleteAll();
*/
}

//--------------------------------------------------------------------------
void SUtil::SetTypeAsprite(ASpriteInstance* _srcASpriteInstance, int type, int printnum)
//--------------------------------------------------------------------------
{
	switch(type)
	{
		case 0 :	{_srcASpriteInstance->SetModule(printnum);	break;}		//	module
		case 1 :	{_srcASpriteInstance->SetFrame(printnum);	break;}		//	frame
		case 2 :	{_srcASpriteInstance->SetAnim(printnum);	break;}		//	animation
		default:	{break;}
	}
}


//--------------------------------------------------------------------------
void SUtil::SetDirAsprite(ASpriteInstance* _delAspriteInstance, int flag)
//--------------------------------------------------------------------------
{
	if(SDIR_LEFT == flag)	{_delAspriteInstance->m_flags=1;}
	else if(SDIR_RIGHT == flag)	{_delAspriteInstance->m_flags=0;}
}


void SUtil::getAniRect( int *rc, ASprite* asp, int aniIdx, int aniFrmIdx)
{
	int off = (asp->_anims_af_start[aniIdx] + aniFrmIdx) * 5;
	int frame = asp->_aframes[off]&0xFF;
	asp->GetFrameRect(rc, frame, 0, 0, (asp->_aframes[off+4]&0x0F), -asp->_aframes[off+2], -asp->_aframes[off+3]);
}



//--------------------------------------------------------------------------
int SUtil::next(int bits)
//--------------------------------------------------------------------------
{
	m_Seed = (m_Seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
	return (int)(m_Seed >> (48 - bits));
}


//--------------------------------------------------------------------------
int SUtil::nextInt()
//--------------------------------------------------------------------------
{
	int tmp = next(32);
	if(0 > tmp)	{tmp *= (-1);}
	return tmp;
}


//--------------------------------------------------------------------------
int SUtil::nextInt(int n)
//--------------------------------------------------------------------------
{
	if (n<=0)		{return -1;}
	if ((n & -n) == n)  // i.e., n is a power of 2
	{
		return ((int)((n * (long)next(31)) >> 31));
	}

    int bits, val;

    do
	{
		bits = next(31);
		val = bits % n;
	}
	while((bits - val + (n-1) < 0));

    return val;
}

//--------------------------------------------------------------------------
long SUtil::nextLong()
//--------------------------------------------------------------------------
{
	return ((long)next(32) << 32) + next(32);
}


//--------------------------------------------------------------------------
void SUtil::setSeed(long lSeed)
//--------------------------------------------------------------------------
{
	m_Seed = (lSeed ^ 0x5DEECE66DL) & ((1L << 48) - 1);
}


//--------------------------------------------------------------------------
TEXT_PACK* SUtil::LoadTextPack(char* _packtype, int _TextNum)
//--------------------------------------------------------------------------
{
	TEXT_PACK* tmpPack;
	tmpPack = GL_NEW TEXT_PACK;

	pGame->Data_init(_packtype);
	pGame->Data_open(_TextNum);

	tmpPack->nTextNum = pGame->Data_readS32();
	int* offset = GL_NEW int [tmpPack->nTextNum+1];

	// read text array offsets
	for (int i = 1; i < tmpPack->nTextNum+1; i++)	{offset[i] = pGame->Data_readS32();}

	tmpPack->nText = GL_NEW byte*[tmpPack->nTextNum];

	for (int i = 0; i < tmpPack->nTextNum; i++)
	{
		int size = offset[i+1] - offset[i];
		tmpPack->nText[i] = GL_NEW byte[size+1];
		MEMSET((char*)tmpPack->nText[i], 0, size+1);
		pGame->Data_read(tmpPack->nText[i], size);
	}

	pGame->Data_free();
	SAFE_DEL_ARRAY(offset);

	return tmpPack;
}


//--------------------------------------------------------------------------
void SUtil::FreeTextPack(TEXT_PACK* pTextpack)
//--------------------------------------------------------------------------
{
	if(pTextpack == NULL)return;
	for(int loop = 0; loop < pTextpack->nTextNum; loop++)
	{
		SAFE_DEL_ARRAY(pTextpack->nText[loop]);
	}
	SAFE_DEL_ARRAY(pTextpack->nText);
	SAFE_DELETE(pTextpack);
}

void SUtil::Sound_Load(int soundID)
{
	if(pSound->m_pData[soundID]) return;
	if(soundID >= MAX_SOUND) return;

	CStream *stream;
	switch(soundID){
		case EFFECT_SWORD_A	:	stream = GetResourceManager().GetResourceAsStream("/sfx_sword_A.mmf");	break;
		case EFFECT_SWORD_B	:	stream = GetResourceManager().GetResourceAsStream("/sfx_sword_B.mmf");	break;
		case EFFECT_SWORD_C	:	stream = GetResourceManager().GetResourceAsStream("/sfx_sword_C.mmf");	break;
		case EFFECT_SWORD_D	:	stream = GetResourceManager().GetResourceAsStream("/sfx_sword_D.mmf");	break;
		case EFFECT_GUN_A	:	stream = GetResourceManager().GetResourceAsStream("/sfx_shotgun_A.mmf");	break;
		case EFFECT_GUN_B	:	stream = GetResourceManager().GetResourceAsStream("/sfx_shotgun_B.mmf");	break;
		case EFFECT_ORB_A	:	stream = GetResourceManager().GetResourceAsStream("/sfx_orb_A.mmf");	break;
		case EFFECT_ORB_B	:	stream = GetResourceManager().GetResourceAsStream("/sfx_orb_B.mmf");	break;
		case EFFECT_ORB_C	:	stream = GetResourceManager().GetResourceAsStream("/sfx_orb_C.mmf");	break;
		case BGM_TEST_A		:	stream = GetResourceManager().GetResourceAsStream("/bgm_Test.mmf");	break;
		default: return;
	}

	pSound->m_pDataSize[soundID] = stream->GetLength();
	pSound->m_pData[soundID] = GL_NEW/*(memType) */unsigned char[pSound->m_pDataSize[soundID]];

	if(pSound->m_pData[soundID])
		stream->Read(pSound->m_pData[soundID], pSound->m_pDataSize[soundID]);

	SAFE_DELETE(stream);
}


void SUtil::Sound_Play(int soundID, bool loopflag)
{
	//	if(g_pGame->m_sndVol == 0) return;
	if(soundID >= MAX_SOUND) return;

	pSound->PlaySound(soundID, true, loopflag);
	pSound->Update();
}


void SUtil::Sound_Stop() 
{
	pSound->StopSound();
}

void SUtil::Sound_Free(int soundID) 
{
	SAFE_DEL_ARRAY(pSound->m_pData[soundID]);
}
//void SUtil::setVol(int _vol)
//{
//	if( _vol < 0 )
//	{
//		_vol = 0;
//	}
//	if( _vol > 100 )
//	{
//		_vol = 100;
//	}
//
//	pSound->m_nVolume = _vol;
//
//
//
//	if(_vol == 0)
//	{
//		pSound->StopSound();
//	}
//}
//void SUtil::getVol()
//{
//	return MC_mdaClipGetVolume(pSound->   m_pMediaPlayer);
//	/*if( _vol < 0 )
//	{
//		_vol = 0;
//	}
//	if( _vol > 100 )
//	{
//		_vol = 100;
//	}
//
//	pSound->m_nVolume = _vol;
//
//	
//
//	if(_vol == 0)
//	{
//		pSound->StopSound();
//	}*/
//}





////////////////////////////////////////////////////////
/*
//--------------------------------------------------------------------------
ASprite* SUtil::LoadAsprite(char* _packtype, int _spriteNum)
//--------------------------------------------------------------------------
{
	byte* buf;
	ASprite* tmpSprite = NULL;

	pGame->Data_init(_packtype);
	buf = pGame->Data_readAll(_spriteNum);
	SAFE_DEL(tmpSprite);
	tmpSprite = GL_NEW ASprite();
	tmpSprite->Load(buf, 0);
	pGame->Data_free();
	SAFE_DELETE(buf);

	return tmpSprite;
}


//--------------------------------------------------------------------------
ASpriteInstance* SUtil::LoadAspriteInstance(ASprite* _Asprite, int xPos = 0, int yPos = 0)
//--------------------------------------------------------------------------
{
	return (ASpriteInstance*)(GL_NEW ASpriteInstance(_Asprite, xPos, yPos, NULL));
}

//--------------------------------------------------------------------------
void SUtil::FreeAsprite(ASprite* _delAsprite)
//--------------------------------------------------------------------------
{
	SAFE_DELETE(_delAsprite);
}
*/
////////////////////////////////////////////////////////////

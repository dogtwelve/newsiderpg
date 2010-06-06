#ifndef		__SUtil_
#define		__SUtil_

#include	"WIPIheader.h"

//	추가 라이브러리
#include	"ResourceManager.h"
#include	"AspriteInstance.h"
#include	"Memory.h"
#include	"Graphics.h"
#include	"Device.h"
#include	"List.h"
#include	"../wipi/Small_Font.h"
#include	"Data.h"
//#include	"../RomanticDebuger_For_Wipi.h"


#define _SUTIL							(SUtil::GetInstance())

class ASprite;
class ASpriteInstance;
class Cengine;


typedef struct _TEXT_PACK
{	
	int nTextNum;
	byte** nText;
//	char* getText(int num)		{return nText[num];}
}TEXT_PACK;


class SUtil
{
private: 
	SUtil();
	static SUtil* pSUtil;



public:
	~SUtil();
	List2< class ASpriteInstance* >		*pDrawList;

	static SUtil* GetInstance();
	void FreeInstance();


	//	FUNCTION LIST
/*
	//--------------------------------------------------------------
	//	ABOUT FILE
	//--------------------------------------------------------------
	static const bool	k_data_dbgDataAccess = false;	
	static const int 	k_data_skipbufferSize = 256;	
	byte* 				s_data_skipBuffer;	
	CStream*			s_data_is;	
	char*				s_data_filename;	
	int					s_data_nbData;	
	int*				s_data_offset;	
	int					s_data_start;	
	int*				s_data_sizes;	
	int 				s_data_curOffset;	
	int					s_data_lastDataOpenType;
	int					Data_readAll_rtn_length;

	bool	Data_init (char* filename);
	void	Data_open (int index);	
	void	Data_skip (int nb)	;
	void	Data_close ();	
	void	Data_free ();
	int		Data_read ();	
	int		Data_read (byte* _array, int length);
	int		Data_read (byte* _array, int off, int len);	
	int		Data_readFully(byte* _array, int length);	
	int		Data_readFully(byte* _array,int offset,int length);	
	byte*	Data_readAll(int index);	
	int		Data_readU8();
	int		Data_readU16();	
	int		Data_readU16LittleEndian();	
	int		Data_readU16BigEndian();	
	int		Data_readS32();	
	int		Data_readS32LittleEndian();	
	int		Data_readS32BigEndian();	
	*/

	//--------------------------------------------------------------
	//	ABOUT GRAPHICS
	//--------------------------------------------------------------
	CGraphics*          g;


	//--------------------------------------------------------------
	//	ABOUT SPRITE
	//--------------------------------------------------------------
	ASprite*			SpriteDB[SPRITE_MAP_MAX+SPRITE_WORLDMAP_MAX+SPRITE_UI_MAX+SPRITE_COSTUME_MAX+SPRITE_MAX+SPRITE_MON_MAX+SPRITE_NPC_MAX+SPRITE_FACE_MAX+SPRITE_MAINMENU_MAX+SPRITE_LOADING_MAX+SPRITE_CINEMA_MAX];
	int					SpriteRefDB[SPRITE_MAP_MAX+SPRITE_WORLDMAP_MAX+SPRITE_UI_MAX+SPRITE_COSTUME_MAX+SPRITE_MAX+SPRITE_MON_MAX+SPRITE_NPC_MAX+SPRITE_FACE_MAX+SPRITE_MAINMENU_MAX+SPRITE_LOADING_MAX+SPRITE_CINEMA_MAX];

	int					GetSpriteDB_Index(char* _packtype, int _spriteNum);

	void				UpdateAsprite();
	ASprite*			LoadAsprite(char* _packtype, int _spriteNum);
	ASpriteInstance*	LoadAspriteInstance(ASprite* _Asprite, int _xPos, int _yPos);
	void				FreeAsprite(ASprite* _delAsprite);
	void				FreeAspriteInstance(ASpriteInstance* _delAspriteInstance);

	void				LoadAspritePack(char* _packtype);
	ASprite*			LoadAspriteFromPack(char* _packtype, int _spriteNum);
	void				ReleaseAspritePack();


	void				SetDirAsprite(ASpriteInstance* _delAspriteInstance, int flag);
	void				PaintAsprite(ASpriteInstance*, int issort);
	void				SetTypeAsprite(ASpriteInstance*, int type, int printnum);
	

	void				getAniRect( int *rc, ASprite* asp, int aniIdx, int aniFrmIdx = 0);

	void				InitAni(ASprite* p_Asprite);
	void				PaintAni(ASprite* p_Asprite, int ani, int posX, int posY, int flags/*, bool LOOP*/);
	void				PaintFrame(ASprite* p_Asprite, int frame, int posX, int posY, int flags);
	void				PaintModule(ASprite* p_Asprite, int module, int posX, int posY, int flags, int anchor);

	void				Sound_Load(int soundID);
	void				Sound_Play(int soundID, bool loopflag);
	void				Sound_Stop();
	void				Sound_Free(int soundID);
	//void				setVol(int _vol);
	//void				getVol();

	
	//--------------------------------------------------------------
	//	ABOUT RANDOM
	//--------------------------------------------------------------
	long	m_Seed;

	int		next(int bits);
	int		nextInt();
	int		nextInt(int n);
	void 	setSeed(long lSeed);
	long 	nextLong();


	//--------------------------------------------------------------
	//	ABOUT TEXT
	//--------------------------------------------------------------
	TEXT_PACK*			LoadTextPack(char* _packtype, int _TextNum);
	void				FreeTextPack(TEXT_PACK* pTextpack);

	//--------------------------------------------------------------
	//	ABOUT FONT
	//--------------------------------------------------------------
	S_KR_Font*			pFont;

	//--------------------------------------------------------------
	//	ABOUT SOUND
	//--------------------------------------------------------------
	CSound* 			pSound;

	

	//--------------------------------------------------------------
	//	나중에  수정할부분 
	//--------------------------------------------------------------
	cGame*				pGame;

};



//--------------------------------------------------------------
//	FUNCTION LIST MACRO
//--------------------------------------------------------------
//#define SUTIL_LoadSpriteInstance(a,b,c)		(_SUTIL->LoadAsprite((a),(b),(c)))

#define SUTIL_FreeInstance()				(_SUTIL->FreeInstance())

//	about math
#define	SQR(a)								((a)*(a))


//	about graphics
#define SUTIL_FillRect(a,b,c,d)				(_SUTIL->g->FillRect((a),(b),(c),(d)))
#define SUTIL_DrawRect(a,b,c,d)				(_SUTIL->g->DrawRect((a),(b),(c),(d)))
#define SUTIL_DrawLine(a,b,c,d)				(_SUTIL->g->DrawLine((a),(b),(c),(d)))
#define SUTIL_SetColor(a)					(_SUTIL->g->SetColor((a)))


//	about sound
#define SUTIL_Sound_Load(a)					(_SUTIL->Sound_Load(a))
#define SUTIL_Sound_Play(a,b)				(_SUTIL->Sound_Play(a,b))
#define SUTIL_SOUND_GetState()				(_SUTIL->pSound->m_curSound)
#define SUTIL_Sound_Stop()					(_SUTIL->Sound_Stop())
//#define SUTIL_SOUND_Update()				(_SUTIL->pSound->Update())
#define SUTIL_Sound_Free(a)					(_SUTIL->Sound_Free(a))
#define SUTIL_SOUND_GetVol()				(_SUTIL->pSound->m_nVolume)
#define SUTIL_SOUND_SetVol(a)				(_SUTIL->pSound->SetVolume(a))


//	about sprite
#define	SDIR_LEFT							(-1)
#define	SDIR_RIGHT							(1)

//	about sprite sort option
#define	S_INCLUDE_SORT						(1)
#define	S_NOT_INCLUDE_SORT					(0)


#define SUTIL_LoadAspritePack(a)			(_SUTIL->LoadAspritePack((a)))
#define SUTIL_LoadAspriteFromPack(a,b)		(_SUTIL->LoadAspriteFromPack((a),(b)))
#define SUTIL_ReleaseAspritePack()			(_SUTIL->ReleaseAspritePack())


#define SUTIL_UpdateSprite()				(_SUTIL->UpdateAsprite())
#define SUTIL_LoadSprite(a,b)				(_SUTIL->LoadAsprite((a),(b)))
#define SUTIL_LoadSpriteInstance(a)			(_SUTIL->LoadAspriteInstance((a)))
#define SUTIL_FreeSprite(a)					_SUTIL->FreeAsprite((a));	(a)=NULL;
#define SUTIL_FreeSpriteInstance(a)			_SUTIL->FreeAspriteInstance((a));	(a)=NULL;
#define SUTIL_FreeTextPack(a)				_SUTIL->FreeTextPack((a));	(a)=NULL;



#define SUTIL_SetDirAsprite(a,b)			(_SUTIL->SetDirAsprite((a),(b)))
#define SUTIL_PaintAsprite(a,b)				(_SUTIL->PaintAsprite((a),(b)))
#define SUTIL_SetTypeModuleAsprite(a,b)		(_SUTIL->SetTypeAsprite((a),(0),(b)))
#define SUTIL_SetTypeFrameAsprite(a,b)		(_SUTIL->SetTypeAsprite((a),(1),(b)))
#define SUTIL_SetTypeAniAsprite(a,b)		(_SUTIL->SetTypeAsprite((a),(2),(b)))
#define SUTIL_GetASpriteAniRect(a,b,c,d)	(_SUTIL->getAniRect((a),(b),(c),(d)))
#define SUTIL_SetXPosAsprite(a,b)			((a)->m_posX=(b))
#define SUTIL_SetYPosAsprite(a,b)			((a)->m_posY=(b))
#define SUTIL_SetZPosAsprite(a,b)			((a)->m_posZ=(b))
#define SUTIL_GetXPosAsprite(a)				((a)->m_posX)
#define SUTIL_GetYPosAsprite(a)				((a)->m_posY)
#define SUTIL_GetZPosAsprite(a)				((a)->m_posZ)
#define SUTIL_UpdateTimeAsprite(a)			((a)->UpdateSpriteAnim())
#define SUTIL_SetLoopAsprite(a,b)			((a)->m_bLoop=(b))

//SangHo
#define SUTIL_Init_Ani(p_Asprite)										(_SUTIL->InitAni(p_Asprite))
#define SUTIL_Paint_Ani(p_Asprite,ani,posX,posY,flags)					(_SUTIL->PaintAni(p_Asprite,ani,posX,posY,flags))
#define SUTIL_Paint_Frame(p_Asprite,frame,posX,posY,flags)				(_SUTIL->PaintFrame(p_Asprite,frame,posX,posY,flags))
#define SUTIL_Paint_Module(p_Asprite,module,posX,posY,flags,anchor)		(_SUTIL->PaintModule(p_Asprite,module,posX,posY,flags,anchor))


//	about random
#define SUTIL_GetRandom()					(_SUTIL->nextInt())

//	about time
#define SUTIL_GetTime()						(MC_knlCurrentTime())

//dongwan
#define SUTIL_Data_init(a)					(_SUTIL->pGame->Data_init(a))
#define SUTIL_Data_open(a)					(_SUTIL->pGame->Data_open(a))
#define SUTIL_Data_readU8()					(_SUTIL->pGame->Data_readU8())
#define SUTIL_Data_readU16()				(_SUTIL->pGame->Data_readU16())
#define SUTIL_Data_readAll(a)				(_SUTIL->pGame->Data_readAll(a))
#define SUTIL_s_data_offset					(_SUTIL->pGame->s_data_offset)
#define SUTIL_s_s_data_sizes				(_SUTIL->pGame->s_data_sizes)
#define SUTIL_Data_free()					(_SUTIL->pGame->Data_free())




#endif	//	__SUtil_
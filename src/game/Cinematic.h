#ifndef CCINEMATIC
#define CCINEMATIC

#include "SUtil.h"
#include "ASprite.h"


//Commands
#define CCMD_CAMERA							10
#define CCMD_CAMERA_SET_POS					(CCMD_CAMERA + 1) // SetPos(x, y);
#define CCMD_CAMERA_CENTER_TO				(CCMD_CAMERA + 2) // CenterTo(x, y);
#define CCMD_CAMERA_FOCUS_ON				(CCMD_CAMERA + 3) // focusOn(x, y);

#define CCMD_OBJ_LAYER						20
#define CCMD_OBJ_LAYER_SET_POS				(CCMD_OBJ_LAYER + 1) // SetPos(x, y);
#define CCMD_OBJ_LAYER_SET_ANIM				(CCMD_OBJ_LAYER + 2) // SetAnim(anim)
#define CCMD_OBJ_LAYER_ADD_FLAGS			(CCMD_OBJ_LAYER + 3) // AddFlags(flags)
#define CCMD_OBJ_LAYER_REMOVE_FLAGS			(CCMD_OBJ_LAYER + 4) // RemoveFlags(flags)

#define CCMD_BASIC							30
#define CCMD_BASIC_SET_POS					(CCMD_BASIC + 1) //SetPos(x, y)
#define CCMD_BASIC_SET_ACTION				(CCMD_BASIC + 2) //SetAction(action)
#define CCMD_BASIC_SET_ACTION_FLAGS			(CCMD_BASIC + 3) //SetActionFlags(action, flags)
#define CCMD_BASIC_OBJEVENT1				(CCMD_BASIC + 4) //SendObjectEvent(obj, param1)
#define CCMD_BASIC_OBJEVENT2				(CCMD_BASIC + 5) //SendObjectEvent(obj, param1, param2)
#define CCMD_BASIC_OBJEVENT3				(CCMD_BASIC + 6) //SendObjectEvent(obj, param1, param2, param3)
#define CCMD_BASIC_EVENT1					(CCMD_BASIC + 7) //SendEvent(param1)
#define CCMD_BASIC_EVENT2					(CCMD_BASIC + 8) //SendEvent(param1, param2)
#define CCMD_BASIC_EVENT3					(CCMD_BASIC + 9) //SendEvent(param1, param2, param3)

#define CCMD_SI								40
#define CCMD_SI_SET_POS						(CCMD_SI + 1) // SetPos(x, y);
#define CCMD_SI_SET_ANIM					(CCMD_SI + 2) // SetAnim(anim)
#define CCMD_SI_ADD_FLAGS					(CCMD_SI + 3) // AddFlags(flags)
#define CCMD_SI_REMOVE_FLAGS				(CCMD_SI + 4) // RemoveFlags(flags)

#define CCMD_FIRST_CUSTOM					100

	//Thread types
#define CTRACK_BASIC						0
#define CTRACK_CAMERA						1
#define CTRACK_OBJ_LAYER					2

	//Status
#define CINEMATIC_PLAYING					0x01
#define CINEMATIC_CIRCLE					0x02
#define CINEMATIC_PLAYED					0x04


#define C_FLAG_FLIP_X							0x01
#define C_FLAG_FLIP_Y							0x02
#define C_FLAG_INVISIBLE						0x04
#define C_FLAG_PAUSE_ANIM						0x08

//#define ReadCinematicDataShort(dest) dest = (data[pos] & 0xFF) + ((data[pos + 1] & 0xFF) << 8); pos += 2;
//#define	GetSendEventNumParams(cmd)	(((cmd - CCMD_BASIC_OBJEVENT1) % 3) + 1)


typedef struct _CFlag
{
	bool m_IsShadow;
	bool m_IsInvisible;
	bool m_IsPauseAnim;
	bool m_IsDummy;
}CFlag;

class cCinematic
{
public:
	struct ASpriteSet{//공용 스프라이트 묶음
		class ASprite* pShadowAs;
		class ASprite* pDebuffAs;
		class ASprite* pFieldUiAs;
		class ASprite* pItemAs;
	};
	ASpriteSet* s_ASpriteSet;

	// Members
	byte ***	s_cinematics;			// all cinematic data
	int *		s_cinematics_sz_len;
	int **		s_cinematics_sz2_len;

	short*     	s_cinematicsId; 		// every cinematic uid
	int			s_cinematicsId_len;
	short*     	s_cinematicsFrameTime; 	// every cinematic time
	int			s_cinematicsFrameTime_len;
	int**   	s_currentFramePos; 		// every cinematic running keyframe position
	bool 		s_cinematicsPause;

	ASpriteInstance***	m_ASpriteIns;
	CFlag**		m_bIsFlag;

	int** 		s_infoasprite;		// 1.spritenum 2.aninum 3.posX 4.posY
	int			s_infoasprite_len;

	int			m_mapX;
	int			m_mapY;
	int			s_tracks_nums;		// total track count
	int			s_param1, s_param2, s_param3;

	cCinematic(void* sASpriteSet);
	~cCinematic();
	void				Load_Cinematics (char* _packtype, int _DataNum, int nextEvtcode, Field*	_pField = NULL);
	void				Release_Cinematics ();
	void				Update_Cinematics();	//	리턴값으로 다음 이벤트를 체크한다.
	void				Paint_Cinematics();
	void				LoadSpriteInstance(int c, int t, int uniquenum, int color);

	void				Resume_Cinematics();
	void				Pause_Cinematics();

	//	씨네마가 실행중인지 확인
	bool		m_IsPlayCinema;
	bool		m_IsSendEndEvt;
	int			m_nNextEventCode;

	int			m_nTheaterTimer;

	//	추가 필드부분
	Field*		pField;
};

#endif
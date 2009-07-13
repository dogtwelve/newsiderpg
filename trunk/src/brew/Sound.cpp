/*
* ============================================================================
*  Name     : CSound
*  Part of  : Game
*  Created  : 2006-04-26 by Zhong Yan
*  Implementation notes:
*  Version  :
*  Copyright: Gameloft S.A.
*
* ============================================================================
*/

#include "../Common/Engine.h"
#include "..\Game\cGame.h"	//hw++
#include "Device.h"
#include "Sound.h"
#include "../game/DEF.h"
#include "../Common/ResourceManager.h"

#define FILE_NAME_SOUNDS "asdfasd"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaPlayer * g_pMediaPlay = NULL;	//hw++
bool			m_bSuspend = false;	//hw++
int				m_SuspendSound = -1;	//hw++

CSound::CSound()
	: m_flag(0)
	, m_nextSound(-1)
	, m_curSound(-1)
	//, m_nVolume(AEE_MAX_VOLUME)	//hw--
	, m_nVolume(AEE_MAX_VOLUME/5)	//hw++
{
}

CSound::~CSound()
{
}

bool CSound::LoadSound(int id, const char *filename, MemoryType memType)
{
	ASSERT(m_pData[id] == NULL);

	CStream *stream = GetResourceManager().GetResourceAsStream(filename);

	if(stream)
	{
		m_pDataSize[id] = stream->GetLength();
		m_pData[id] = GL_NEW/*(memType) */unsigned char[m_pDataSize[id]];
		
		if(m_pData[id])
			stream->Read(m_pData[id], m_pDataSize[id]);
		
		SAFE_DELETE(stream);

		return true;
	}

	return false;
}

//const char SOUNDS[] = "\\sound";

bool CSound::LoadSound(int id, MemoryType memType)
{
	ASSERT(m_pData[id] == NULL);

	CStream *stream = GetResourceManager().GetResourceAsStream(FILE_NAME_SOUNDS);
		
	if(stream)
	{
		int soundCount = stream->ReadUByte();
		
		for (int i = 0; i < soundCount; i++) 
		{
			int size = stream->ReadUShort();

			if (i == id) 
			{
				m_pDataSize[i] = size;
				m_pData[i] = GL_NEW/*(memType) */unsigned char[m_pDataSize[i]];
				
				if(m_pData[i])
					stream->Read(m_pData[i], m_pDataSize[i]);
			}
			else 
			{
				stream->Skip(size);
			}
		}

		SAFE_DELETE(stream);

		return true;
	}
	else
	{
		return false;
	}
}

bool CSound::LoadAllSound(int mask, MemoryType memType)
{
	CStream *stream = GetResourceManager().GetResourceAsStream(FILE_NAME_SOUNDS);
	int size;
	if(stream)
	{
		int soundCount = stream->ReadUByte();
		
		for (int i = 0; i < soundCount && i < 32; i++) 
		{
			size = stream->ReadUShort();

			if ((((unsigned int)1 << i) & mask) != 0) 
			{
				m_pDataSize[i] = size;
				m_pData[i] = GL_NEW/*(memType) */unsigned char[m_pDataSize[i]];
				
				if(m_pData[i])
					stream->Read(m_pData[i], m_pDataSize[i]);
			}
			else 
			{
				stream->Skip(size);
			}
		}
		SAFE_DELETE(stream);
		return true;
	}
	else
	{
		return false;
	}
}

void CSound::PlaySound(int id, bool stopOther, bool loop)
{
	if(id < 0)
		return;

// 	if(stopOther)	
// 		StopSound();
	
	m_nextSound = id;
	m_curSound	= -1;
	m_flag		= loop ? SOUND_LOOPMUSIC : 0;
}

void CSound::FreeSounds()
{
	for(int i = 0; i < MAX_SOUND; i++)
	{
		m_pData[i] = NULL;
		m_pDataSize[i] = NULL;
	}
}

void CSound::SetVolume(int vol)
{
	if( vol < 0 )
	{
		vol = 0;
	}
	if( vol > 100 )
	{
		vol = 100;
	}
	if(g_pMediaPlay){
		MC_mdaClipSetVolume(g_pMediaPlay->m_pMediaPlayer,vol);
	}
	
	m_nVolume = vol;
}

void CSound::SetupSoundDevice(bool preventKeyBeep, bool deviceToSpeaker)
{
#ifdef STEUP_SOUND_DEVICE
	ISound* pIsound;
	
	if(ISHELL_CreateInstance(GetGameApp()->a.m_pIShell, AEECLSID_SOUND, (void **)&pIsound) != SUCCESS)
	{
		DBGPRINTF("Error Creating ISound interface");
		return;
	}

	if(preventKeyBeep)
	{
		ISOUND_SetVolume(pIsound, 0);
	}	

	if(deviceToSpeaker)
	{
		AEESoundInfo soundInfo;
		soundInfo.eDevice     = AEE_SOUND_DEVICE_SPEAKER;
		soundInfo.eMethod     = AEE_SOUND_METHOD_MIDI;
		soundInfo.eAPath      = AEE_SOUND_APATH_BOTH;
		soundInfo.eEarMuteCtl = AEE_SOUND_MUTECTL_UNMUTED;
		soundInfo.eMicMuteCtl = AEE_SOUND_MUTECTL_UNMUTED;//AEE_SOUND_MUTECTL_UNMUTED;
		ISOUND_Set(pIsound, &soundInfo);
		ISOUND_SetDevice(pIsound);
	}

	if(pIsound != NULL)
	{
		ISOUND_Release(pIsound);
		pIsound = NULL;
	}
#endif
}

#if SOUND_LEVEL == 0

#ifdef WIPIC
CMediaPlayer::CMediaPlayer()
{
	m_pMediaPlayer = NULL;
	m_bSuspend = false;
	m_SuspendSound = -1;
}

CMediaPlayer::~CMediaPlayer()
{
	if(m_pMediaPlayer)
	{
		IMEDIA_Stop(m_pMediaPlayer);
		IMEDIA_RegisterNotify(m_pMediaPlayer, NULL, NULL);
		IMEDIA_Release(m_pMediaPlayer);
	}
}

bool CMediaPlayer::Init()	
{
	//do nothing;
	return true;
}

//static void NotifyProc(void * pUser, AEEMediaCmdNotify * pCmdNotify)
void NotifyProc(MC_MdaClip* clip, M_Int32 status)
{
	CMediaPlayer *pMedia = (CMediaPlayer*)g_pMediaPlay;

	//if (pCmdNotify->nCmd == MM_CMD_PLAY)  // IMEDIA_Play/IMEDIA_Record events
	{
		switch (status)
		{
		case MC_MDA_STATUS_START://재생시작
			pMedia->m_flag &= ~SOUND_END;
			pMedia->m_flag |= SOUND_PLAYING;
			//			pMedia->m_curSound = pMedia->m_nextSound;
			//			pMedia->m_nextSound = -1;
			break;

		case MC_MDA_STATUS_STOPPED://재생 종료
			//case MM_STATUS_ABORT:   // playback aborted				
			pMedia->m_flag |= SOUND_END;
			pMedia->m_flag &= ~SOUND_PLAYING;
			if((pMedia->m_flag & SOUND_LOOPMUSIC) == 0){
				pMedia->m_curSound = -1;
			}
			break;
		}
	}
}

void CMediaPlayer::SetVolume_instant(int vol)
{
	IMEDIA_SetVolume(m_pMediaPlayer, vol);
}

void CMediaPlayer::Update()
{
	m_cGame = (CGame*)(GetGameApp()->m_engine);

	//if(CGAME_KEY_PRESSED(GAMEDK_VOLUME_UP))
	//	if (m_cGame->gkPressed(CKeypad::DK_VOLUME_UP,  true))
	//	{
	////		m_nVolume += 10;
	////		if( m_nVolume > AEE_MAX_VOLUME )
	////			m_nVolume = AEE_MAX_VOLUME;
	//
	//		m_cGame->m_volume = (m_cGame->m_volume + 1) % VOLUME_COUNT;
	//		m_cGame->s_soundEnable = m_cGame->m_volume != VOLUME_OFF;
	//		m_cGame->m_sound->SetVolume(Volumes[m_cGame->m_volume]);
	//		m_cGame->saveRecord();
	//				
	//		IMEDIA_SetVolume(m_pMediaPlayer, Volumes[m_cGame->m_volume]);
	//	}
	//	//if(CGAME_KEY_PRESSED(GAMEDK_VOLUME_DOWN))
	//	if (m_cGame->gkPressed(CKeypad::DK_VOLUME_DOWN, true))
	//	{
	////		m_nVolume -= 10;
	////		if( m_nVolume < 0 )
	////			m_nVolume = 0;
	//				
	//		m_cGame->m_volume = (m_cGame->m_volume - 1) % VOLUME_COUNT;
	//		m_cGame->s_soundEnable = m_cGame->m_volume != VOLUME_OFF;
	//		m_cGame->m_sound->SetVolume(Volumes[m_cGame->m_volume]);
	//		m_cGame->saveRecord();
	//				
	//		IMEDIA_SetVolume(m_pMediaPlayer, Volumes[m_cGame->m_volume]);
	//	}

	if(m_nextSound > -1)//start to play
	{
		int ret = 0;

		AEEMediaData mediaData;

		if(NULL == m_pData[m_nextSound])
		{
			ASSERT(0);
			return;
		}

		mediaData.pData = m_pData[m_nextSound];
		mediaData.dwSize = m_pDataSize[m_nextSound];
		mediaData.eInput = SDT_BUFFER;

		if(NULL != m_pMediaPlayer)
		{
			IMEDIA_RegisterNotify ( m_pMediaPlayer, NULL, NULL);
			IMEDIA_Stop(m_pMediaPlayer);
			MC_mdaClipClearData(m_pMediaPlayer);
			IMEDIA_Release(m_pMediaPlayer);
			m_pMediaPlayer = NULL;
		}


		m_flag |= SOUND_PLAYING;//wu nuo
		g_pMediaPlay = this;
		m_pMediaPlayer = MC_mdaClipCreate ((signed char *)"Yamaha_SMAF", mediaData.dwSize, NotifyProc);
		if(m_pMediaPlayer != NULL)
		{
			MC_mdaClipPutData(m_pMediaPlayer, (unsigned char *)mediaData.pData, mediaData.dwSize);
		}

		//<< add by liu kun peng
		//bool volumeZero = false;
		//if(m_nVolume == 0)
		//{
		//	volumeZero = true;
		//	m_nVolume = 1;
		//}
		//>>

		IMEDIA_SetVolume(m_pMediaPlayer, m_nVolume);
		{
			m_curSound = m_nextSound;
			m_nextSound = -1;
		}

		//MC_mdaClipSetPosition(m_pMediaPlayer,2000);

		MC_mdaPlay(m_pMediaPlayer,  m_flag&SOUND_LOOPMUSIC);//IMEDIA_Play(m_pMediaPlayer);				
		
		//<<add by liu kun peng
		//if(volumeZero)
		//{
		//	IMEDIA_SetVolume(m_pMediaPlayer, 0);
		//	m_nVolume = 0;
		//}
		//>>
	}
	else if(m_pMediaPlayer != NULL && m_flag & SOUND_END && m_flag & SOUND_LOOPMUSIC && m_curSound != -1)
	{
		//IMEDIA_Rewind(m_pMediaPlayer, 0);
		m_flag |= SOUND_PLAYING;//wu nuo
		IMEDIA_SetVolume(m_pMediaPlayer, m_nVolume);
		MC_mdaPlay(m_pMediaPlayer,  m_flag&SOUND_LOOPMUSIC);
	}
}

void CMediaPlayer::StopSound()
{
	if(m_pMediaPlayer)
	{
		IMEDIA_Stop(m_pMediaPlayer);
		//	MC_mdaClipClearData(m_pMediaPlayer);
		m_curSound	= -1;
		m_nextSound = -1;
		m_flag		= 0;
	}
}

void CMediaPlayer::PauseSound()
{
	if(m_pMediaPlayer)
		MC_mdaPause(m_pMediaPlayer);
}

void CMediaPlayer::ResumeSound()
{
	if(m_pMediaPlayer)
		MC_mdaResume(m_pMediaPlayer);
}

void CMediaPlayer::ReleaseHardware()
{
	//ToDo
	// 	if( m_pMediaPlayer != NULL )
	//{
		// backup info
		//ISOUNDPLAYER_GetInfo ( m_pSoundPlayer, &m_pInfoBeforeSuspended ) ;

		// release hardware
		if( m_curSound > -1 )
		{
			m_bSuspend = true;
			m_SuspendSound = m_curSound;
		}
		else
		{
			m_bSuspend = false;
			m_SuspendSound = -1;
		}

		IMEDIA_Stop(m_pMediaPlayer); 
		ISOUNDPLAYER_RegisterNotify(m_pMediaPlayer, NULL, NULL); 
		ISOUNDPLAYER_Release(m_pMediaPlayer); 
		m_pMediaPlayer = NULL; 
	//}
	//	else 
	//	{
	//		m_bSuspend = false;
	//		m_SuspendSound = -1;
	//	}
}

void CMediaPlayer::RestoreHardware(boolean isSoundOn)
{
	if( m_bSuspend && m_SuspendSound > -1 )
	{
		PlaySound( m_SuspendSound );
	}
}
#else
CSoundPlayer::CSoundPlayer()
	: m_pSoundPlayer(NULL)
{
}
	
CSoundPlayer::~CSoundPlayer()
{
	if(m_pSoundPlayer)
	{
		ISOUNDPLAYER_RegisterNotify(m_pSoundPlayer, NULL, NULL);
		ISOUNDPLAYER_SetInfo(m_pSoundPlayer, 0);
		ISOUNDPLAYER_Release(m_pSoundPlayer);
		m_pSoundPlayer = NULL;
	}
}

static void NotifyProc(void * pUser, AEESoundPlayerCmd eCBType, AEESoundPlayerStatus eSPStatus, uint32 dwParam)
{
	CSound *pSound = (CSound*)pUser;

	switch(eCBType)
	{
	case AEE_SOUNDPLAYER_PLAY_CB:
		switch(eSPStatus)
		{
		case AEE_SOUNDPLAYER_SUCCESS:
			pSound->m_flag &= ~SOUND_END;
			pSound->m_flag |= SOUND_PLAYING;
			pSound->m_curSound = pSound->m_nextSound;
			pSound->m_nextSound = -1;
			break;

		case AEE_SOUNDPLAYER_ABORTED:
		case AEE_SOUNDPLAYER_DONE:
		case AEE_SOUNDPLAYER_FAILURE:
			pSound->m_flag |= SOUND_END;
			pSound->m_flag &= ~SOUND_PLAYING;
			if((pSound->m_flag & SOUND_LOOPMUSIC) == 0){
				pSound->m_curSound = -1;
			}
			break;
		}
		break;
	}
}

bool CSoundPlayer::Init()
{
	SetupSoundDevice();

	int nRet = EFAILED;

	if(NULL == m_pSoundPlayer)
	{
		nRet = ISHELL_CreateInstance (GetGameApp()->a.m_pIShell, AEECLSID_SOUNDPLAYER, (void **)&m_pSoundPlayer);
		
		if (SUCCESS != nRet)
		{
			ASSERT(false);
			return false;
		}

		if(NULL != m_pSoundPlayer)
		{
			ISOUNDPLAYER_RegisterNotify(m_pSoundPlayer, NotifyProc, this);
		}

//		ISOUNDPLAYER_SetVolume(m_pSoundPlayer, AEE_MAX_VOLUME);
	}
	
	return SUCCESS == nRet;
}

void CSoundPlayer::ReleaseHardware()
{
   if( m_pSoundPlayer != NULL )
   {   
      // backup info
      ISOUNDPLAYER_GetInfo ( m_pSoundPlayer, &m_pInfoBeforeSuspended ) ;

      // release hardware
      ISOUNDPLAYER_Stop(m_pSoundPlayer); 
      ISOUNDPLAYER_RegisterNotify(m_pSoundPlayer, NULL, NULL); 
      ISOUNDPLAYER_Release(m_pSoundPlayer); 
      m_pSoundPlayer = NULL; 
   }
}

void CSoundPlayer::RestoreHardware(boolean isSoundOn)
{
	Init();
   
	if( m_pSoundPlayer != NULL )
	{
		int ret = ISOUNDPLAYER_SetInfo( m_pSoundPlayer, &m_pInfoBeforeSuspended);//restore info
		
		if (ret == AEE_SUCCESS)
		{			
			if( isSoundOn 				
				&& m_curSound > -1
				&& ( (m_flag & SOUND_LOOPMUSIC) != 0 || (m_flag & SOUND_END) == 0) )//if loop and no end replay.
			{
#ifndef DISABLE_SET_VOLUME
				ISOUNDPLAYER_SetVolume(m_pSoundPlayer, m_nVolume);
#endif				
				ISOUNDPLAYER_Rewind(m_pSoundPlayer, 0);
				ISOUNDPLAYER_Play(m_pSoundPlayer);
			}
		}
	}
}

void CSoundPlayer::SetVolume(int vol)
{
	CSound::SetVolume(vol);

	if(m_pSoundPlayer)		
	{
#ifndef DISABLE_SET_VOLUME
		ISOUNDPLAYER_SetVolume(m_pSoundPlayer, m_nVolume);
#endif
	}
}


void CSoundPlayer::Update()
{	
	if(NULL == m_pSoundPlayer)
		return;

	if(m_nextSound >= 0)
	{	
		int ret = 0;

		AEESoundPlayerInfo pinfo;
			
		if(NULL == m_pData[m_nextSound])
		{
//			ASSERT(0);
			DBGPRINTF("Can't Get Sound Data ID: %d", m_nextSound);
			return;
		}
		
		pinfo.eInput = SDT_BUFFER;
		pinfo.pData = m_pData[m_nextSound];
		pinfo.dwSize = m_pDataSize[m_nextSound];
		
		ret = ISOUNDPLAYER_SetInfo(m_pSoundPlayer, &pinfo);
		
		if (ret == AEE_SUCCESS)
		{	
#ifndef DISABLE_SET_VOLUME
			ISOUNDPLAYER_SetVolume(m_pSoundPlayer, m_nVolume);
#endif
			ISOUNDPLAYER_Play(m_pSoundPlayer);	
		}
	}
	else if(m_flag & SOUND_END && m_flag & SOUND_LOOPMUSIC && m_curSound != -1)
	{
		ISOUNDPLAYER_Rewind(m_pSoundPlayer, 0);
		ISOUNDPLAYER_Play(m_pSoundPlayer);	
	}
}

void CSoundPlayer::StopSound()
{		
	if(m_pSoundPlayer)
	{
		ISOUNDPLAYER_Stop(m_pSoundPlayer);
		m_curSound = -1;
		m_nextSound = -1;
		m_flag = 0;
	}
}

void CSoundPlayer::PauseSound()
{
	if(m_pSoundPlayer)
		ISOUNDPLAYER_Pause(m_pSoundPlayer);	
}

void CSoundPlayer::ResumeSound()
{
	if(m_pSoundPlayer)
		ISOUNDPLAYER_Resume(m_pSoundPlayer);	
}
#endif

#elif SOUND_LEVEL == 1

CMediaPlayer::CMediaPlayer()
	: m_pMediaPlayer(NULL)
{

}

CMediaPlayer::~CMediaPlayer()
{
	if(m_pMediaPlayer)
	{
		IMEDIA_Stop(m_pMediaPlayer);
		IMEDIA_RegisterNotify(m_pMediaPlayer, NULL, NULL);
		IMEDIA_Release(m_pMediaPlayer);
	}
}

bool CMediaPlayer::Init()	
{
	//do nothing;
	return true;
}

static void NotifyProc(void * pUser, AEEMediaCmdNotify * pCmdNotify)
{
	CMediaPlayer *pMedia = (CMediaPlayer*)pUser;

	if (pCmdNotify->nCmd == MM_CMD_PLAY)  // IMEDIA_Play/IMEDIA_Record events
	{
		switch (pCmdNotify->nStatus)
		{
		case MM_STATUS_START:
//			pMedia->m_flag &= ~SOUND_END;
//			pMedia->m_flag |= SOUND_PLAYING;
//			pMedia->m_curSound = pMedia->m_nextSound;
//			pMedia->m_nextSound = -1;
			break;

		case MM_STATUS_DONE:    // playback done
		case MM_STATUS_ABORT:   // playback aborted				
			pMedia->m_flag |= SOUND_END;
			pMedia->m_flag &= ~SOUND_PLAYING;
			if((pMedia->m_flag & SOUND_LOOPMUSIC) == 0){
				pMedia->m_curSound = -1;
			}
			break;
		}
	}
}

void CMediaPlayer::Update()
{
	if(m_nextSound > -1)//start to play
	{
		int ret = 0;

		AEEMediaData mediaData;
			
		if(NULL == m_pData[m_nextSound])
		{
			ASSERT(0);
			return;
		}

		mediaData.pData = m_pData[m_nextSound];
		mediaData.dwSize = m_pDataSize[m_nextSound];
		mediaData.clsData = MMD_BUFFER;

		if(NULL != m_pMediaPlayer)
		{
			IMEDIA_RegisterNotify (m_pMediaPlayer, NULL, NULL);
			IMEDIA_Release(m_pMediaPlayer);
			m_pMediaPlayer = NULL;
		}
		
		const char *cpszMIME;
		AEECLSID	clsHandler;

		if (SUCCESS == ISHELL_DetectType(GetGameApp()->a.m_pIShell, mediaData.pData, &mediaData.dwSize, NULL,&cpszMIME))
		{			
			clsHandler = ISHELL_GetHandler(GetGameApp()->a.m_pIShell, AEECLSID_MEDIA, cpszMIME);
			
			if(clsHandler)
			{
				ret = ISHELL_CreateInstance(GetGameApp()->a.m_pIShell, clsHandler,(void **)&m_pMediaPlayer);			
			}
		}

		if(SUCCESS == ret)
		{
			ret = IMEDIA_SetMediaData(m_pMediaPlayer, &mediaData);
		
			if (ret == AEE_SUCCESS)
			{
				if(NULL != m_pMediaPlayer)
				{
					ret = IMEDIA_RegisterNotify (m_pMediaPlayer, NotifyProc, this);
				}
#ifndef DISABLE_SET_VOLUME				
				IMEDIA_SetVolume(m_pMediaPlayer, m_nVolume);	
#endif
				IMEDIA_Play(m_pMediaPlayer);
				{
					
					m_flag &= ~SOUND_END;
					m_flag |= SOUND_PLAYING;
					if(!(m_flag & SOUND_LOOPMUSIC) || !(m_nextSound == -1))
					{
						m_curSound = m_nextSound;
					}
					m_nextSound = -1;

				}
			}
		}
		else
		{
			m_pMediaPlayer = NULL;
			m_nextSound = -1;
		}
	}
	else if(m_pMediaPlayer != NULL && m_flag & SOUND_END && m_flag & SOUND_LOOPMUSIC && m_curSound != -1)
	{
		IMEDIA_Rewind(m_pMediaPlayer, 0);
		IMEDIA_Play(m_pMediaPlayer);
		{
			m_flag &= ~SOUND_END;
			m_flag |= SOUND_PLAYING;
			if(!(m_flag & SOUND_LOOPMUSIC) || !(m_nextSound == -1))
			{
				m_curSound = m_nextSound;
			}
			m_nextSound = -1;
		}
	}

}

void CMediaPlayer::StopSound()
{
	if(m_pMediaPlayer)
	{
		IMEDIA_Stop(m_pMediaPlayer);
		m_curSound	= -1;
		m_nextSound = -1;
		m_flag		= 0;
	}
	ReleaseHardware();
}

void CMediaPlayer::PauseSound()
{
	if(m_pMediaPlayer)
		IMEDIA_Pause(m_pMediaPlayer);
}

void CMediaPlayer::ResumeSound()
{
	if(m_pMediaPlayer)
		IMEDIA_Resume(m_pMediaPlayer);
}

void CMediaPlayer::ReleaseHardware()
{
	if(NULL != m_pMediaPlayer)
	{
		IMEDIA_Stop(m_pMediaPlayer);
		IMEDIA_RegisterNotify (m_pMediaPlayer, NULL, NULL);
		IMEDIA_Release(m_pMediaPlayer);
		m_pMediaPlayer = NULL;
	}
	m_curSound	= -1;
	m_nextSound = -1;
	m_flag		= 0;
}

void CMediaPlayer::RestoreHardware(boolean isSoundOn)
{
	//do nothing
}

#elif SOUND_LEVEL == 2

void ChannelNotifyProc(void * pUser, AEEMediaCmdNotify * pCmdNotify)
{
	CSoundChannel *pChannel = (CSoundChannel*)pUser;

	if (pCmdNotify->nCmd == MM_CMD_PLAY)
	{
		if(pCmdNotify->nStatus == MM_STATUS_TICK_UPDATE)
			return;

		switch (pCmdNotify->nStatus)
		{
		case MM_STATUS_START:		
			pChannel->SetState(CSoundChannel::CHANNEL_STATE_PLAYING);
			break;

		case MM_STATUS_DONE:    
		case MM_STATUS_ABORT: 			
			pChannel->SetState(CSoundChannel::CHANNEL_STATE_IDLE);
			pChannel->m_soundID = -1;
			break;
		}
	}
}

CSoundChannel::CSoundChannel()
	: m_pMedia(NULL)
	, m_state(CHANNEL_STATE_IDLE)
	, m_soundID(-1)
	, m_volume(AEE_MAX_VOLUME)
{

}

CSoundChannel::~CSoundChannel()
{
	FreeMedia();
}


bool CSoundChannel::PlaySound(AEEMediaData& data, int id)
{
	if(!IsChannelFree() || id == m_soundID)
		return false;

	FreeMedia();

	if(SUCCESS != AEEMediaUtil_CreateMedia(GetGameApp()->a.m_pIShell, &data, &m_pMedia))
		return false;
	
#ifndef AEE_SIMULATOR
  	IMEDIA_EnableChannelShare(m_pMedia, TRUE);
#endif		

	IMEDIA_RegisterNotify (m_pMedia, ChannelNotifyProc, this);
	IMEDIA_Play(m_pMedia);

	IMEDIA_SetVolume(m_pMedia, m_volume);

	m_soundID = id;

	return true;
}

void CSoundChannel::PauseSound()
{
	if(m_pMedia != NULL)
		IMEDIA_Pause(m_pMedia);
}
	
void CSoundChannel::ResumeSound()
{
	if(m_pMedia != NULL)
		IMEDIA_Resume(m_pMedia);
}

CMultiMediaPlayer::CMultiMediaPlayer()
{

}

CMultiMediaPlayer::~CMultiMediaPlayer()
{
	StopSound();
}

bool CMultiMediaPlayer::Init()	
{
	SetupSoundDevice();
	return true;
}

void CMultiMediaPlayer::Update()
{

}

void CMultiMediaPlayer::PlaySound(int id, bool stopOther, bool loop)
{
	AEEMediaData mediaData;
	
	if(NULL == m_pData[id])
	{
		//ASSERT(0);
		DBGPRINTF("Can't Get Sound Data ID: %d", m_nextSound);
		return;
	}
	
	mediaData.pData = m_pData[id];
	mediaData.dwSize = m_pDataSize[id];
	mediaData.clsData = MMD_BUFFER;
	
	const char *cpszMIME;
	AEECLSID	clsHandler;

	if (SUCCESS == ISHELL_DetectType(GetGameApp()->a.m_pIShell, mediaData.pData, &mediaData.dwSize, NULL,&cpszMIME))
	{			
		clsHandler = ISHELL_GetHandler(GetGameApp()->a.m_pIShell, AEECLSID_MEDIA, cpszMIME);	
	}

	//you can only choose one format to mix sound
 	if(AEECLSID_MEDIAPMD != clsHandler /*AEECLSID_MEDIAMIDI != clsHandler*/)
 		return;

	//use BG channel to play background music, this sound id can be choose by game.
	if(id == SOUND_INDEX_TITLE)
	{
		m_channelBG.PlaySound(mediaData, id);
	}
	else//All sfx played here. Now we have 3 channels available.If all channels are busy this sound will not be played.
	{
		for(int i = 0; i < SFX_CHANNEL_NUM; i++)
		{
			if(m_channelSFX[i].PlaySound(mediaData, id))
				break;
		}	
	}
}

void CMultiMediaPlayer::StopSound()
{
	m_channelBG.FreeMedia();

	for(int i = 0; i < SFX_CHANNEL_NUM; i++)
	{
		m_channelSFX[i].FreeMedia();
	}	

	return;
}

void CMultiMediaPlayer::PauseSound()
{	
	m_channelBG.PauseSound();

	for(int i = 0; i < SFX_CHANNEL_NUM; i++)
	{
		m_channelSFX[i].PauseSound();
	}	
}

void CMultiMediaPlayer::ResumeSound()
{
	m_channelBG.ResumeSound();

	for(int i = 0; i < SFX_CHANNEL_NUM; i++)
	{
		m_channelSFX[i].ResumeSound();
	}	
}

void CMultiMediaPlayer::ReleaseHardware()
{
	StopSound();
}

void CMultiMediaPlayer::RestoreHardware(boolean isSoundOn)
{
	//ToDo
}

void CMultiMediaPlayer::SetVolume(int vol)
{
	m_nVolume = vol;

	m_channelBG.SetVolume(vol);

	for(int i = 0; i < SFX_CHANNEL_NUM; i++)
	{
		m_channelSFX[i].SetVolume(vol);
	}	
}

#endif

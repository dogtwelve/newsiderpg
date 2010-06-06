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
#ifndef __SOUND_H__
#define __SOUND_H__

#include "..\common/Common.h"

#define DISABLE_SET_VOLUME	//hw++
#define ENABLE_MEDIAPLAYER	//hw++

#include "..\wipi\brewtowipi.h"	//hw++

//#define SOUND_LOOPMUSIC		(1 << 0)	//hw--
//#define SOUND_PLAYING		(1 << 1)	//hw--
//#define SOUND_END			(1 << 2)	//hw--

#define MAX_SOUND			50

class CGame;	//hw++

class CSound
{
public:
	CGame *m_cGame;	//hw++

	friend void SoundNotify(MC_MdaClip* clip, M_Int32 status);

	CSound();
	virtual ~CSound();

	virtual bool Init() = 0;	
	virtual void Update() = 0;
	virtual void StopSound() = 0;
	virtual void PauseSound() = 0;
	virtual void ResumeSound() = 0;
	virtual void PlaySound(int id, bool stopOther = true, bool loop = false);
	virtual void ReleaseHardware() = 0;
	virtual void RestoreHardware(boolean) = 0;
	virtual void SetVolume(int vol);
		
	bool	LoadSound(int id, const char *filename, MemoryType memType = POOL_BOTTOM);
	bool	LoadSound(int id, MemoryType memType = POOL_BOTTOM);
	bool	LoadAllSound(int mask, MemoryType memType = POOL_BOTTOM);
	void	FreeSounds();

	inline int CSound::GetNextSoundID(){
		return m_nextSound;
	}

	inline int CSound::GetCurrentSoundID(){
		return m_curSound;
	}

	void SetupSoundDevice(bool preventKeyBeep = false, bool deviceToSpeaker = false);
	
	int				m_flag;	
	int				m_nextSound;
	int				m_curSound;

//protected:
public:
	unsigned char	*m_pData[MAX_SOUND];
	int				m_pDataSize[MAX_SOUND];	
	int				m_nVolume;
};


#if SOUND_LEVEL == 0		
//	#include <AEESoundPlayer.h>	//hw--
#ifdef ENABLE_MEDIAPLAYER
	class CMediaPlayer : public CSound
	{
	public:
		CMediaPlayer();
		virtual ~CMediaPlayer();

		bool Init();	
		void Update();
		void StopSound();
		void PauseSound();
		void ResumeSound();
		void ReleaseHardware();
		void RestoreHardware(boolean);
		void SetVolume_instant(int vol);

	//private:
		IMedia					*m_pMediaPlayer;
	};
#else
	class CSoundPlayer : public CSound
	{
	public:
		CSoundPlayer();
		virtual ~CSoundPlayer();

		bool Init();	
		void Update();
		void StopSound();
		void PauseSound();
		void ResumeSound();
		void ReleaseHardware();
		void RestoreHardware(boolean);
		void SetVolume(int vol);
		
	private:
		AEESoundPlayerInfo	m_pInfoBeforeSuspended;
		ISoundPlayer		*m_pSoundPlayer;
	};
#endif

#elif SOUND_LEVEL == 1	
	//#include <AEEMedia.h>

	class CMediaPlayer : public CSound
	{
	public:
		CMediaPlayer();
		virtual ~CMediaPlayer();
		
		bool Init();	
		void Update();
		void StopSound();
		void PauseSound();
		void ResumeSound();
		void ReleaseHardware();
		void RestoreHardware(boolean);
		
	private:
		IMedia					*m_pMediaPlayer;
		IMedia					*m_pMediaBG;
	};
	
#elif SOUND_LEVEL == 2	
	#include <AEEMedia.h>
	#include <AEEMediaUtil.h>


	class CSoundChannel
	{
	public:
		enum ChannelState
		{
			CHANNEL_STATE_PLAYING,
				CHANNEL_STATE_IDLE
		};
		
		CSoundChannel();
		virtual ~CSoundChannel();
		
		bool PlaySound(AEEMediaData& data, int id = -1);				
		void PauseSound();
		void ResumeSound();

		inline bool IsChannelFree()
		{
			return m_state == CHANNEL_STATE_IDLE;
		};
		
		inline void FreeMedia()
		{
			if(m_pMedia != NULL)
			{
				IMEDIA_Stop(m_pMedia);
				IMEDIA_RegisterNotify (m_pMedia, NULL, NULL);
				IMEDIA_Release(m_pMedia);
				m_pMedia = NULL;
			}
			
			m_soundID = -1;
			m_state = CHANNEL_STATE_IDLE;
		};
		
		inline void SetState(ChannelState state){m_state = state;};
		inline ChannelState GetState(){return m_state;}

		inline void SetVolume(int vol){m_volume = vol;}
		
		int				m_soundID;	
		
	protected:
		IMedia*			m_pMedia;	
		ChannelState	m_state;
		int				m_volume;
		
	};

	class CMultiMediaPlayer : public CSound
	{
	public:
		CMultiMediaPlayer();
		virtual ~CMultiMediaPlayer();

		enum {SFX_CHANNEL_NUM = 3};

		bool Init();	
		void Update();
		void PlaySound(int id, bool stopOther = true, bool loop = false);
		void StopSound();
		void PauseSound();
		void ResumeSound();
		void ReleaseHardware();
		void RestoreHardware(boolean);
		void SetVolume(int vol);

	private:
		CSoundChannel			m_channelBG;
		CSoundChannel			m_channelSFX[SFX_CHANNEL_NUM];
	};
#endif

#endif // !defined(AFX_SOUND_H__BAA4CF77_0C12_4D44_982A_16A76D342B8E__INCLUDED_)

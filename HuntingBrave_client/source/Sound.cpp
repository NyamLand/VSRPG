
#include	"iextreme.h"
#include	"Sound.h"

//*******************************************************************************
//
//	Sound�N���X
//
//*******************************************************************************

//---------------------------------------------------------------------------
//	�O���[�o��
//---------------------------------------------------------------------------

	namespace
	{
		namespace
		{
			const		LPSTR	bgmfile[] =
			{
				"DATA/Sound/BGM/title.ogg",
				"DATA/Sound/BGM/menu.ogg",
				"DATA/Sound/BGM/fight.ogg",
				"DATA/Sound/BGM/fight1.ogg",
				"DATA/Sound/BGM/iiwake.ogg",
				"DATA/Sound/BGM/Result.ogg",
				"DATA/Sound/BGM/dead.ogg"
			};
		}

#define	VOLUME_MAX	200
	}

//---------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------

	//	�R���X�g���N�^
	Sound::Sound( void )
	{
		//	SE�Z�b�g
		IEX_SetWAV( SE::ATTACK, "DATA/Sound/SE/attack.wav" );
		IEX_SetWAV( SE::ATTACK_HIT1, "DATA/Sound/SE/attack01_hit.wav" );
		IEX_SetWAV( SE::ATTACK_HIT2, "DATA/Sound/SE/attack02_hit.wav" );
		IEX_SetWAV( SE::CANCEL, "DATA/Sound/SE/cancel.wav" );
		IEX_SetWAV( SE::ENEMY_DEAD, "DATA/Sound/SE/ene_dead.wav" );
		IEX_SetWAV( SE::BIG_ENEMY_DEAD, "DATA/Sound/SE/ene_dragon_down.wav" );
		IEX_SetWAV( SE::IM_OK, "DATA/Sound/SE/im-ok.wav" );
		IEX_SetWAV( SE::JOIN, "DATA/Sound/SE/join_game.wav" );
		IEX_SetWAV( SE::KILL, "DATA/Sound/SE/kill.wav" );
		IEX_SetWAV( SE::LVUP, "DATA/Sound/SE/LvUp.wav" );
		IEX_SetWAV( SE::MAGIC_CHARGE, "DATA/Sound/SE/mag_charging.wav" );
		IEX_SetWAV( SE::MAGIC_HIT, "DATA/Sound/SE/mag_hit.wav" );
		IEX_SetWAV( SE::MAGIC_SHOT, "DATA/Sound/SE/mag_shot.wav" );
		IEX_SetWAV( SE::MAX_UPGRADE, "DATA/Sound/SE/MaxUpgrade.wav" );
		IEX_SetWAV( SE::MOVE_SELECT, "DATA/Sound/SE/move_select.wav" );
		IEX_SetWAV( SE::OK, "DATA/Sound/SE/OK.wav" );
		IEX_SetWAV( SE::PLAYER_DEAD, "DATA/Sound/SE/Player_dead.wav" );
		IEX_SetWAV( SE::RESULT, "DATA/Sound/SE/result-jan.wav" );
		IEX_SetWAV( SE::STEP, "DATA/Sound/SE/step.wav" );
		IEX_SetWAV( SE::TIME_END, "DATA/Sound/SE/time-end.wav" );
		IEX_SetWAV( SE::TITLE_OK, "DATA/Sound/SE/title_ok.wav" );
		IEX_SetWAV( SE::UPGRADE_OPEN, "DATA/Sound/SE/UpgradeOpen.wav" );
		IEX_SetWAV( SE::USE_ITEM, "DATA/Sound/SE/Useitem.wav" );

		for ( int i = 0; i < BGM::BGM_MAX; i++ )
		{
			isPlay[i] = false;
			stream[i] = nullptr;
		}
	}

	//	�f�X�g���N�^
	Sound::~Sound( void )
	{

	}

//---------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------

	//	SE�Đ�
	void	Sound::PlaySE( int type )
	{
		IEX_PlaySound( type, false );
	}

	//	SE��~
	void	Sound::StopSE( int type )
	{
		IEX_StopSound( type );
	}

	//	BGM�Đ�
	void	Sound::PlayBGM( int type )
	{
		stream[type] = IEX_PlayStreamSound( bgmfile[ type ] );
		isPlay[type] = true;	
	}

	//	BGM��~
	void	Sound::StopBGM( void )
	{
		for ( int i = 0; i < BGM::BGM_MAX; i++ )
		{
			if ( !isPlay[i] )	continue;
			IEX_StopStreamSound( stream[i] );
			isPlay[i] = false;
		}
	}

	//	�S��~
	void	Sound::AllStop( void )
	{
		//	SE��~
		for ( int i = 0; i < SE::END; i++ )	IEX_StopSound( i );
		
		//	BGM��~
		StopBGM();
	}

//---------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------

	//	�{�����[���ݒ�
	void	Sound::SetVolume( int type, int volume )
	{
		IEX_SetStreamSoundVolume( stream[type], volume );
	}

	//	�{�����[�����Z�b�g
	void	Sound::ResetVolume( int type )
	{
		IEX_SetStreamSoundVolume( stream[type], VOLUME_MAX );
	}

	//	�~���[�g
	void	Sound::MuteVolume( int type )
	{
		IEX_SetStreamSoundVolume( stream[type], 0 );
	}

//---------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------

	//	SE�Đ���Ԏ擾
	bool	Sound::GetSEState( int type )
	{
		BOOL state = IEX_GetSoundStatus( type );

		if ( state )	return	true;
		return	false;
	}

	//	BGM�Đ���Ԏ擾
	bool	Sound::GetBGMState( void )
	{
		bool	out = isPlay[0];
		return	out;
	}

	//	���̎擾
	Sound*	Sound::GetInstance( void )
	{
		static	Sound	out;
		return	&out;
	}











#ifndef __SOUND_H__
#define	__SOUND_H__

//*********************************************************************************
//
//	Soundクラス
//
//*********************************************************************************

//	SoundInfo
namespace
{
	namespace SE
	{
		enum SE_TYPE
		{
			ATTACK,
			ATTACK_HIT1,
			ATTACK_HIT2,
			CANCEL,
			ENEMY_DEAD,
			BIG_ENEMY_DEAD,		//　まだ
			IM_OK,
			JOIN,

			KILL,
			LVUP,
			MAGIC_CHARGE,
			MAGIC_HIT,
			MAGIC_SHOT,
			MAX_UPGRADE,
			MOVE_SELECT,
			OK,
			PLAYER_DEAD,
			RESULT,
			STEP,
			TIME_END,
			TITLE_OK,
			UPGRADE_OPEN,
			USE_ITEM,

			END		//	終端
		};
	}

	namespace BGM
	{
		enum BGM_TYPE
		{
			TITLE,
			MENU,
			MAIN,
			IIWAKE,
			RESULT,
			DEAD,
			BGM_MAX
		};
	}
}

//	クラス
class Sound
{
private:
	LPDSSTREAM		stream[BGM::BGM_MAX];
	bool						isPlay[BGM::BGM_MAX];
	int	volume;

private:
	//	初期化・解放
	Sound( void );
	~Sound( void );

public:

	//	SE再生
	void	PlaySE( int type );
	void	StopSE( int type );

	//	BGM再生
	void	PlayBGM( int type );
	void	StopBGM( void );
	void	AllStop( void );

	//	情報設定
	void	SetVolume( int bgmType, int volume );
	void	ResetVolume( int bgmType );
	void	MuteVolume( int bgmType );

	//	情報取得
	bool	GetSEState( int type );
	bool	GetBGMState( void );
	static	Sound*	GetInstance( void );
};

#define	sound ( Sound::GetInstance() )

//*********************************************************************************
#endif // !__SOUND_H__


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
			//　プレイヤー・敵関連
			ATTACK,
			ATTACK_HIT1,
			ATTACK_HIT2,
			STEP,
			KILL,
			LVUP,
			MAGIC_CHARGE,
			MAGIC_HIT,
			MAGIC_SHOT,
			MAX_UPGRADE,
			PLAYER_DEAD,
			UPGRADE_OPEN,
			USE_ITEM,

			ENEMY_DEAD,
			BIG_ENEMY_DEAD,		//　まだ
			

			//　名前・メニュ－等
			MOVE_SELECT,
			OK,
			CANCEL,
			IM_OK,
			JOIN,

			TITLE_OK,
			RESULT,

			TIME_END,	//　まだ

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
			MAIN_2,
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


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
			JOIN,
			MOVE_SELECT,
			OK,
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
			RESULT
		};
	}
}

//	クラス
class Sound
{
private:
	LPDSSTREAM		stream;
	bool						isPlay;

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

	//	情報取得
	bool	GetSEState( int type );
	bool	GetBGMState( void );
	static	Sound*	GetInstance( void );
};

#define	sound ( Sound::GetInstance() )

//*********************************************************************************
#endif // !__SOUND_H__


#ifndef __SOUND_H__
#define	__SOUND_H__

//*********************************************************************************
//
//	Sound�N���X
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
			END		//	�I�[
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

//	�N���X
class Sound
{
private:
	LPDSSTREAM		stream;
	bool						isPlay;

private:
	//	�������E���
	Sound( void );
	~Sound( void );

public:
	//	SE�Đ�
	void	PlaySE( int type );
	void	StopSE( int type );

	//	BGM�Đ�
	void	PlayBGM( int type );
	void	StopBGM( void );
	void	AllStop( void );

	//	���擾
	bool	GetSEState( int type );
	bool	GetBGMState( void );
	static	Sound*	GetInstance( void );
};

#define	sound ( Sound::GetInstance() )

//*********************************************************************************
#endif // !__SOUND_H__

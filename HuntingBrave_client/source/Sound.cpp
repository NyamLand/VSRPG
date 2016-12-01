
#include	"iextreme.h"
#include	"Sound.h"

//*******************************************************************************
//
//	Soundクラス
//
//*******************************************************************************

//---------------------------------------------------------------------------
//	グローバル
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
				"DATA/Sound/BGM/iiwake.ogg"
			};
		}
	}

//---------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------

	//	コンストラクタ
	Sound::Sound( void )
	{
		isPlay = false;
	}

	//	デストラクタ
	Sound::~Sound( void )
	{

	}

//---------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------

	//	SE再生
	void	Sound::PlaySE( int type )
	{
		IEX_PlaySound( type, false );
	}

	//	SE停止
	void	Sound::StopSE( int type )
	{
		IEX_StopSound( type );
	}

	//	BGM再生
	void	Sound::PlayBGM( int type )
	{
		stream = IEX_PlayStreamSound( bgmfile[ type ] );
		isPlay = true;
	}

	//	BGM停止
	void	Sound::StopBGM( void )
	{
		if ( isPlay )
		{
			IEX_StopStreamSound( stream );
			isPlay = false;
			
		}
	}

	//	全停止
	void	Sound::AllStop( void )
	{
		//	SE停止
		for ( int i = 0; i < SE::END; i++ )	IEX_StopSound( i );
		
		//	BGM停止
		StopBGM();
	}

//---------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------

	//	SE再生状態取得
	bool	Sound::GetSEState( int type )
	{
		BOOL state = IEX_GetSoundStatus( type );

		if ( state )	return	true;
		return	false;
	}

	//	BGM再生状態取得
	bool	Sound::GetBGMState( void )
	{
		bool	out = isPlay;
		return	out;
	}

	//	実体取得
	Sound*	Sound::GetInstance( void )
	{
		static	Sound	out;
		return	&out;
	}










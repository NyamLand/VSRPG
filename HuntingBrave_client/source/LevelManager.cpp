
#include	"iextreme.h"
#include	"GameParam.h"
#include	"LevelManager.h"

//***************************************************************
//
//	LevelManagerクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	LevelManager::LevelManager( void )
	{
		//	経験値初期化
		levelInfo.exp = 0;

		//	各レベル初期化
		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
		{
			levelInfo.level[i] = -1;
		}
	}

	//	デストラクタ
	LevelManager::~LevelManager( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	レベル送信
	void	LevelManager::SendLevel( char levelType )
	{
		//	情報設定
		SendLevelData	sendLevelData( levelType );

		//	情報送信
		gameParam->send( ( LPSTR )&sendLevelData, sizeof( sendLevelData ) );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	経験値情報設定
	void	LevelManager::SetExp( int exp )
	{
		levelInfo.exp = exp;
	}

	//	レベル情報設定
	void	LevelManager::SetLevelInfo( char levelType, char level )
	{
		levelInfo.level[levelType] = level;
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	各プレイヤーレベル情報取得
	LevelInfo&	LevelManager::GetLevelInfo( void )
	{
		return	levelInfo;
	}

	//	各レベル取得
	char	LevelManager::GetLevel( char levelType )const
	{
		return	levelInfo.level[levelType];
	}

	//	経験値取得
	int	LevelManager::GetExp( void )const
	{
		return	levelInfo.exp;
	}








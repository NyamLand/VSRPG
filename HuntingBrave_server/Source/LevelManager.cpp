
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

//	実体
LevelManager*	levelManager = nullptr;

#define	LEVEL_MAX	6

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	LevelManager::LevelManager( void )
	{
		//	レベル情報初期化
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	経験値初期化
			levelInfo[p].exp = 0;

			//	各レベル初期化
			for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
			{
				levelInfo[p].level[i] = -1;
			}
		}

		expData[ENEMY_EXP::BIG_ENEMY] = 5000;
		expData[ENEMY_EXP::SMALL_ENEMY] = 1000;
	}

	//	デストラクタ
	LevelManager::~LevelManager( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	レベル加算
	void	LevelManager::AddLevel( int id, char levelType )
	{
		//	レベル加算
		levelInfo[id].level[levelType]++;

		//	レベル上限設定
		if ( levelInfo[id].level[levelType] >= LEVEL_MAX - 1 )
		{
			//	上限設定
			levelInfo[id].level[levelType] = LEVEL_MAX - 1;

			//	クラスチェンジ
			SendClassChange( id, levelType + 1 );
		}
	}

	//	経験値計算
	void	LevelManager::CalcExp( int id, char enemyType )
	{
		//	経験値加算
		levelInfo[id].exp += expData[enemyType];

		//	下限設定
		if ( levelInfo[id].exp <= 0 )	levelInfo[id].exp = 0;
	}

	//	レベル送信
	void	LevelManager::SendLevel( int id, char levelType )
	{
		//	情報設定
		SendLevelData	sendLevelData( levelType, levelInfo[id].level[levelType] );

		//	情報送信
		gameParam->send( id, ( LPSTR )&sendLevelData, sizeof( sendLevelData ) );
	}

	//	経験値送信
	void	LevelManager::SendExp( int id )
	{
		SendExpData	sendExpData( levelInfo[id].exp );
		gameParam->send( id, ( LPSTR )&sendExpData, sizeof( sendExpData ) );
	}

	//	クラスチェンジ情報送信
	void	LevelManager::SendClassChange( int id, char nextClass )
	{
		SendClassChangeData	sendData( id, nextClass );

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	各プレイヤーレベル情報取得
	LevelInfo&	LevelManager::GetLevelInfo( int id )
	{
		return	levelInfo[id];
	}

	//	各レベル取得
	char	LevelManager::GetLevel( int id, char levelType )const
	{
		return	levelInfo[id].level[levelType];
	}

	//	経験値取得
	int	LevelManager::GetExp( int id )const
	{
		return	levelInfo[id].exp;
	}








#include	"iextreme.h"
#include	"GameParam.h"
#include	"LevelManager.h"

//***************************************************************
//
//	LevelManager�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//	����
LevelManager*	levelManager = nullptr;

#define	LEVEL_MAX	6

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	LevelManager::LevelManager( void )
	{
		//	���x����񏉊���
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�o���l������
			levelInfo[p].exp = 0;

			//	�e���x��������
			for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
			{
				levelInfo[p].level[i] = -1;
			}
		}

		expData[ENEMY_EXP::BIG_ENEMY] = 5000;
		expData[ENEMY_EXP::SMALL_ENEMY] = 1000;
	}

	//	�f�X�g���N�^
	LevelManager::~LevelManager( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	���x�����Z
	void	LevelManager::AddLevel( int id, char levelType )
	{
		//	���x�����Z
		levelInfo[id].level[levelType]++;

		//	���x������ݒ�
		if ( levelInfo[id].level[levelType] >= LEVEL_MAX - 1 )
		{
			//	����ݒ�
			levelInfo[id].level[levelType] = LEVEL_MAX - 1;

			//	�N���X�`�F���W
			SendClassChange( id, levelType + 1 );
		}
	}

	//	�o���l�v�Z
	void	LevelManager::CalcExp( int id, char enemyType )
	{
		//	�o���l���Z
		levelInfo[id].exp += expData[enemyType];

		//	�����ݒ�
		if ( levelInfo[id].exp <= 0 )	levelInfo[id].exp = 0;
	}

	//	���x�����M
	void	LevelManager::SendLevel( int id, char levelType )
	{
		//	���ݒ�
		SendLevelData	sendLevelData( levelType, levelInfo[id].level[levelType] );

		//	��񑗐M
		gameParam->send( id, ( LPSTR )&sendLevelData, sizeof( sendLevelData ) );
	}

	//	�o���l���M
	void	LevelManager::SendExp( int id )
	{
		SendExpData	sendExpData( levelInfo[id].exp );
		gameParam->send( id, ( LPSTR )&sendExpData, sizeof( sendExpData ) );
	}

	//	�N���X�`�F���W��񑗐M
	void	LevelManager::SendClassChange( int id, char nextClass )
	{
		SendClassChangeData	sendData( id, nextClass );

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	�e�v���C���[���x�����擾
	LevelInfo&	LevelManager::GetLevelInfo( int id )
	{
		return	levelInfo[id];
	}

	//	�e���x���擾
	char	LevelManager::GetLevel( int id, char levelType )const
	{
		return	levelInfo[id].level[levelType];
	}

	//	�o���l�擾
	int	LevelManager::GetExp( int id )const
	{
		return	levelInfo[id].exp;
	}







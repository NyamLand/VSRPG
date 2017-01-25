
#include	"iextreme.h"
#include	<vector>
#include	"GameManager.h"
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
			levelInfo[p].total_level = 0;

			//	�e���x��������
			for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
			{
				levelInfo[p].level[i] = 0;
			}
		}

		expData[ENEMY_EXP::BIG_ENEMY] = 50;
		expData[ENEMY_EXP::SMALL_ENEMY] = 10;
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
		if ( levelInfo[id].level[levelType] >= LEVEL_MAX )
		{
			//	����ݒ�
			levelInfo[id].level[levelType] = LEVEL_MAX;

			//	�N���X�`�F���W
			SendClassChange( id, levelType + 1 );
		}

		else
		{
			//	�K�v�o���l�����Z
			levelInfo[id].exp -= 30 + levelInfo[id].total_level * 5;
			levelInfo[id].total_level++;
			SendExp(id);
		}

		//	�X�e�[�^�X�v�Z
		CulcStatus( id, levelType );
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
		gameParam->GetPlayerParam(id).charType = nextClass;

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

	//	�S�X�e�[�^�X���M
	void	LevelManager::SendAllStatus( int id )
	{
		//	���擾
		PlayerStatus		playerStatus = gameParam->GetPlayerStatus( id );
		SendAllStatusData	sendData(
			playerStatus.power,
			playerStatus.defense,
			playerStatus.magicAttack,
			playerStatus.magicDefense,
			gameParam->GetLifeInfo( id ).maxLife,
			playerStatus.speed );

		//	���M
		gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
	}

	//	�e�X�e�[�^�X���M
	void	LevelManager::SendStatus( int id, char statusType, float status )
	{
		//	���擾
		PlayerStatus		playerStatus = gameParam->GetPlayerStatus( id );

		//	�錾
		SendStatusData	sendStatus;
		sendStatus.statusType = statusType;

		switch ( statusType )
		{
		case SEND_STATUS::ATTACK:
			sendStatus.status = ( float )playerStatus.power;
			break;

		case SEND_STATUS::DEFENSE:
			sendStatus.status = ( float )playerStatus.defense;
			break;

		case SEND_STATUS::MAGIC_ATTACK:
			sendStatus.status = ( float )playerStatus.magicAttack;
			break;

		case SEND_STATUS::MAGIC_DEFENSE:
			sendStatus.status = ( float )playerStatus.magicDefense;
			break;

		case SEND_STATUS::SPEED:
			sendStatus.status = playerStatus.speed;
			break;
			
		case SEND_STATUS::LIFE:
			sendStatus.status = ( float )gameParam->GetLifeInfo( id ).maxLife;
			break;

		default:
			return;
		}

		//	���M
		gameParam->send( id, ( LPSTR )&sendStatus, sizeof( sendStatus ) );
	}
	
//----------------------------------------------------------------------------------------------
//	��M
//----------------------------------------------------------------------------------------------

	//	��������M
	void	LevelManager::ReceiveHuntInfo( int client, const LPSTR& data )
	{
		//	�\���̐錾
		static	struct HuntInfo
		{
			char com;
			char infoType;
			char enemyType;
		} *huntInfo;

		//	�ϊ�
		huntInfo = ( HuntInfo* )data;

		//	�o���l�v�Z
		levelManager->CalcExp( client, huntInfo->enemyType );
		levelManager->SendExp( client );
	}

//----------------------------------------------------------------------------------------------
//	���x�����̃X�e�[�^�X�v�Z
//----------------------------------------------------------------------------------------------

	//	�X�e�[�^�X�v�Z
	void	LevelManager::CulcStatus( int id, char levelType )
	{
		CulcPower( id, levelType );
		CulcDefense( id, levelType );
		CulcMagicAttack( id, levelType );
		CulcMagicDefense( id, levelType );
		CulcMaxLife( id, levelType );
		CulcSpeed( id, levelType );
	}

	//	�U���͌v�Z
	void	LevelManager::CulcPower( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade( 
			levelType, 
			UPGRADE_DATA::ATTACK,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcPower( addParam );
	}

	//	�h��͌v�Z
	void	LevelManager::CulcDefense( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::DEFENSE,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcDefense( addParam );
	}

	//	���@�U���͌v�Z
	void	LevelManager::CulcMagicAttack( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::MAGIC_ATTACK,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcMagicAttack( addParam );
	}

	//	���@�h��͌v�Z
	void	LevelManager::CulcMagicDefense( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::MAGIC_DIFENSE,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcMagicDefense( addParam );
	}

	//	�ő�HP�v�Z
	void	LevelManager::CulcMaxLife( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::HP,
			levelInfo[id].level[levelType] );
		gameParam->GetLifeInfo( id ).AddMaxLife( addParam );
	}

	//	�X�s�[�h�v�Z
	void	LevelManager::CulcSpeed( int id, char levelType )
	{
		float doubleParam = gameManager->GetUpGradeSpeed(
			levelType,
			levelInfo[id].level[levelType] );

		if ( doubleParam >= 0.5f )
			gameParam->GetPlayerStatus( id ).DoubleSpeed( doubleParam );
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







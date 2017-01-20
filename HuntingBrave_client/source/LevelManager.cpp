
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

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	LevelManager::LevelManager( void )
	{
		//	�o���l������
		levelInfo.exp = 0;

		//	�e���x��������
		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
		{
			levelInfo.level[i] = 0;
		}
	}

	//	�f�X�g���N�^
	LevelManager::~LevelManager( void )
	{

	}

	//	������
	bool	LevelManager::Initialize( void )
	{
		//	�o���l������
		levelInfo.exp = 0;

		//	�e���x��������
		for (int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++)
		{
			levelInfo.level[i] = 0;
		}

		return	true;
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	���x�����M
	void	LevelManager::SendLevel( char levelType )
	{
		//	���ݒ�
		SendLevelData	sendLevelData( levelType );

		//	��񑗐M
		gameParam->send( ( LPSTR )&sendLevelData, sizeof( sendLevelData ) );
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�o���l���ݒ�
	void	LevelManager::SetExp( int exp )
	{
		levelInfo.exp = exp;
	}

	//	���x�����ݒ�
	void	LevelManager::SetLevelInfo( char levelType, char level )
	{
		levelInfo.level[levelType] = level;
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�X�e�[�^�X�v�Z
	void	LevelManager::CulcStatus( const LPSTR& data )
	{
		switch ( data[1] )
		{
		case RECEIVE_STATUS::ATTACK:
			CulcPower( data );
			break;

		case RECEIVE_STATUS::DEFENSE:
			CulcDefense( data );
			break;

		case RECEIVE_STATUS::MAGIC_ATTACK:
			CulcMagicAttack( data );
			break;

		case RECEIVE_STATUS::MAGIC_DEFENSE:
			CulcMagicDefense( data );
			break;

		case RECEIVE_STATUS::SPEED:
			CulcSpeed( data );
			break;

		case RECEIVE_STATUS::LIFE:
			CulcMaxLife( data );
			break;

		case RECEIVE_STATUS::ALL:
			CulcAllStatus( data );
			break;
		}
	}

	//	�S�X�e�[�^�X�v�Z
	void	LevelManager::CulcAllStatus( const LPSTR& data )
	{
		ReceiveAllStatusData*	allStatusData = ( ReceiveAllStatusData* )data;
		gameParam->GetPlayerStatus().power = allStatusData->attack;
		gameParam->GetPlayerStatus().defense = allStatusData->defense;
		gameParam->GetPlayerStatus().magicPower = allStatusData->magicAttack;
		gameParam->GetPlayerStatus().magicDefense = allStatusData->magicDefense;
		gameParam->GetPlayerStatus().speed = allStatusData->speed;
	}

	//	�S�X�e�[�^�X�v�Z
	void	LevelManager::CulcAllStatus( const ReceiveAllStatusData& statusData )
	{
		gameParam->GetPlayerStatus().power = statusData.attack;
		gameParam->GetPlayerStatus().defense = statusData.defense;
		gameParam->GetPlayerStatus().magicPower = statusData.magicAttack;
		gameParam->GetPlayerStatus().magicDefense = statusData.magicDefense;
		gameParam->GetPlayerStatus().maxLife = statusData.life;
		gameParam->GetPlayerStatus().speed = statusData.speed;
	}

	//	�U���͌v�Z
	void	LevelManager::CulcPower( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcPower( ( int )statusData->status );
	}

	//	�h��͌v�Z
	void	LevelManager::CulcDefense( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcDefense( ( int )statusData->status );
	}

	//	���@�U���͌v�Z
	void	LevelManager::CulcMagicAttack( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcMagicPower( ( int )statusData->status );
	}
	
	//	���@�h��͌v�Z
	void	LevelManager::CulcMagicDefense( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcMagicDefense( ( int )statusData->status );
	}

	//	�ő�HP�v�Z
	void	LevelManager::CulcMaxLife( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcMaxLife( ( int )statusData->status );
	}

	//	�X�s�[�h�v�Z
	void	LevelManager::CulcSpeed( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().DoubleSpeed( statusData->status );
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	�e�v���C���[���x�����擾
	LevelInfo&	LevelManager::GetLevelInfo( void )
	{
		return	levelInfo;
	}

	//	�e���x���擾
	char	LevelManager::GetLevel( char levelType )const
	{
		return	levelInfo.level[levelType];
	}

	//	�o���l�擾
	int	LevelManager::GetExp( void )const
	{
		return	levelInfo.exp;
	}









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
			levelInfo.level[i] = -1;
		}
	}

	//	�f�X�g���N�^
	LevelManager::~LevelManager( void )
	{

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








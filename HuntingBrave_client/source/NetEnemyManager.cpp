
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
#include	"NetEnemyManager.h"

//***************************************************************
//
//	NetEnemyManager�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

namespace ENEMY_COMMAND
{
	enum
	{
		MOVE,
		MODE,
		MOTION,
		DEAD,
		ERASE = 10,
		APPEND
	};
}

#define	MINOTAURUS_SCALE	0.15f

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NetEnemyManager::NetEnemyManager( void ) : org( nullptr )
	{
		Initialize();
	}

	//	�f�X�g���N�^
	NetEnemyManager::~NetEnemyManager( void )
	{
		//Release();
	}

	//	������
	bool	NetEnemyManager::Initialize( void )
	{
		if ( org == nullptr )
		{
			org = new iex3DObj( "DATA/CHR/Enemy/halk/halk.IEM" );
			org->SetScale( MINOTAURUS_SCALE );
			org->Update();
		}

		enemyList.clear();
		return	true;
	}

	//	���
	void	NetEnemyManager::Release( void )
	{
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			it = enemyList.erase( it );
		}

		SafeDelete( org );
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------
	
	//	�X�V
	void	NetEnemyManager::Update( void )
	{
		for ( int i = 0; i < enemyList.size(); i++)
		{
			enemyList[i]->Update();
			bool	isAlive = enemyList[i]->GetIsAlive();
			if ( !isAlive )
			{
				enemyList.erase( enemyList.begin() + i );
			}
		}
	}

	//	�`��
	void	NetEnemyManager::Render( void )
	{
		for ( int i = 0; i < enemyList.size(); i++ )
		{
			enemyList[i]->Render();
		}
	}

	//	HP�`��
	void	NetEnemyManager::RenderHp(void)
	{
		for (auto it = enemyList.begin(); it != enemyList.end(); it++)
		{
			(*it)->RenderHpBar();
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	���X�g�ɒǉ�
	void	NetEnemyManager::Append( const Vector3& pos, float angle )
	{
		//	����
		NetEnemy*	enemy = new NetEnemy();

		//	������
		enemy->Initialize( org->Clone(), pos, angle );

		//	���X�g�ɒǉ�
		enemyList.push_back( enemy );
	}

	//	���X�g����폜
	void	NetEnemyManager::Erase( int index )
	{
		enemyList.erase( enemyList.begin() + index );
	}

//----------------------------------------------------------------------------------------------
//	��M�֐�
//----------------------------------------------------------------------------------------------

	//	��M
	void	NetEnemyManager::Receive( const LPSTR& data )
	{
		switch ( data[1] )
		{
		case ENEMY_COMMAND::MOVE:
			if ( enemyList.empty() )	break;
			ReceiveEnemyInfo( data );
			break;

		case ENEMY_COMMAND::MODE:
			if ( enemyList.empty() )	break;
			ReceiveModeInfo( data );
			break;

		case ENEMY_COMMAND::MOTION:
			if ( enemyList.empty() )	break;
			ReceiveMotionInfo( data );
			break;

		case ENEMY_COMMAND::DEAD:
			if ( enemyList.empty() )	break;
			ReceiveDeadInfo( data );
			break;

		case ENEMY_COMMAND::ERASE:
			if ( enemyList.empty() )	break;
			ReceiveEraseInfo( data );
			break;

		case ENEMY_COMMAND::APPEND:
			ReceiveAppendInfo( data );
			break;

		default:
			break;
		}
	}

	//	�G����M
	void	NetEnemyManager::ReceiveEnemyInfo( const LPSTR& data )
	{
		struct EnemyInfo
		{
			char com;
			char enemyCom;
			int	index;
			Vector3	pos;
			float			angle;
		}* enemyInfo = ( EnemyInfo* )data;

		SetInfo( enemyInfo->index, 
			enemyInfo->pos, 
			enemyInfo->angle );
	}

	//	�G���[�h����M
	void	NetEnemyManager::ReceiveModeInfo( const LPSTR& data )
	{
		//	���ݒ�
		struct EnemyInfo
		{
			char com;
			char infoType;
			char enemyIndex;
			char nextMode;
		} *receiveInfo = ( EnemyInfo* )data;
	}

	//	�G���[�V������M
	void	NetEnemyManager::ReceiveMotionInfo( const LPSTR& data )
	{
		//	���ݒ�
		struct EnemyInfo
		{
			char com;
			char infoType;
			char enemyIndex;
			int motion;
		} *receiveInfo = ( EnemyInfo* )data;

		enemyList[receiveInfo->enemyIndex]->SetMotion( receiveInfo->motion );
	}

	//	�G���S��M
	void	NetEnemyManager::ReceiveDeadInfo( const LPSTR& data )
	{

	}

	//	�G��������M
	void	NetEnemyManager::ReceiveEraseInfo( const LPSTR& data )
	{
		//	�ϊ�
		struct EnemyInfo
		{
			char com;
			char enemyCom;
			int	index;
		}* enemyInfo = ( EnemyInfo* )data;

		//	�폜
		Erase( enemyInfo->index );
	}

	//	�G�ǉ�����M
	void	NetEnemyManager::ReceiveAppendInfo( const LPSTR& data )
	{
		//	�ϊ�
		struct EnemyInfo
		{
			char com;
			char enemyCom;
			Vector3	pos;
			float			angle;
		}* enemyInfo = ( EnemyInfo* )data;

		Append( enemyInfo->pos, enemyInfo->angle );
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	��M���ݒ�
	void	NetEnemyManager::SetInfo( int index, const Vector3& pos, float angle )
	{
		enemyList[index]->SetPos( pos );
		enemyList[index]->SetAngle( angle );
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���X�g�擾
	std::vector<NetEnemy*>&		NetEnemyManager::GetList( void )
	{
		return	enemyList;
	}
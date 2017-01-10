
#include	"iextreme.h"
#include	<vector>
#include	"GameParam.h"
#include	"MagicManager.h"

//**************************************************************************
//
//	MagicManager�N���X
//
//**************************************************************************

//------------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------------

MagicManager*	magicManager = nullptr;

//------------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	MagicManager::MagicManager( void )
	{
		magicList.clear();
	}

	//	�f�X�g���N�^
	MagicManager::~MagicManager( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); )
		{
			it = magicList.erase( it );
		}
	}

//------------------------------------------------------------------------------------------
//	�X�V
//------------------------------------------------------------------------------------------
	
	//	�X�V
	void	MagicManager::Update( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); )
		{
			bool	isAlive = ( *it )->Update();
			int	index = std::distance( magicList.begin(), it );

			if ( !isAlive )	//	���ł��Ă���Ƃ����X�g����폜���A�폜��񑗐M
			{
				it = magicList.erase( it );
				SendMagicEraseInfo( index );
				continue;
			}
			else	//	�������Ă���Ƃ����W��񑗐M
			{
				SendMagicInfo( index, ( *it )->GetPos() );
			}

			//	����
			it++;
		}
	}

//------------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------------

	//	�ǉ�
	void	MagicManager::Append( int id, const Vector3& pos, const Vector3& vec )
	{
		//	������
		Magic*	magic = new Magic();
		magic->Initialize( id, pos, vec );

		//	���X�g�ɒǉ�
		magicList.push_back( magic );

		//	���X�g�ǉ���񑗐M
		SendMagicAppendInfo( id, pos );
	}

	//	���W���M
	void	MagicManager::SendMagicInfo( int index, const Vector3& pos )
	{
		//	���ݒ�
		SendMagicData sendMagicData( index, pos );
		
		//	��񑗐M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendMagicData, sizeof( sendMagicData ) );
		}
	}

	//	�폜��񑗐M
	void	MagicManager::SendMagicEraseInfo( int index )
	{
		//	���ݒ�
		SendMagicErase	sendMagicErase( index );

		//	��񑗐M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendMagicErase, sizeof( sendMagicErase ) );
		}
	}

	//	���X�g�ǉ���񑗐M
	void	MagicManager::SendMagicAppendInfo( int id, const Vector3& pos )
	{
		//	���ݒ�
		SendMagicAppend	sendMagicAppend( id, pos, gameParam->GetPlayerParam( id ).angle );
		
		//	��񑗐M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendMagicAppend, sizeof( sendMagicAppend ) );
		}
	}

//------------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------------

	//	���X�g�擾
	std::vector<Magic*>&		MagicManager::GetList( void )
	{
		return	magicList;
	}
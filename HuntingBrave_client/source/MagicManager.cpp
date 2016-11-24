
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
#include	"MagicManager.h"

//***************************************************************
//
//	MagicManager�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	MagicManager::MagicManager( void ) : org( nullptr )
	{

	}

	//	�f�X�g���N�^
	MagicManager::~MagicManager( void )
	{
		//Release();
	}

	//	������
	bool	MagicManager::Initialize( void )
	{
		if ( org == nullptr )
			org = new iexMesh( "DATA/Effect/magic/MagicBullet/magic-Bullet.IMO" );
		org->SetScale( 0.01f );
		org->Update();
		magicList.clear();
		return	true;
	}

	//	���
	void	MagicManager::Release( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); )
		{
			it = magicList.erase( it );
		}

		SafeDelete( org );
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------
	
	//	�X�V
	void	MagicManager::Update( void )
	{
	}

	//	�`��
	void	MagicManager::Render( void )
	{
		org->Render();

		for ( auto it = magicList.begin(); it != magicList.end(); it++ )
		{
			( *it )->Render();
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	���X�g�ɒǉ�
	void	MagicManager::Append( int id, const Vector3& pos, float angle )
	{
		//	����
		Magic*	magic = new Magic();

		//	������
		magic->Initialize( org->Clone(), pos, angle );

		//	���X�g�ɒǉ�
		magicList.push_back( magic );
	}

	//	���X�g����폜
	void	MagicManager::Erase( int index )
	{
		magicList.erase( magicList.begin() + index );
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------



#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	<vector>
#include	"MagicManager.h"
#include	"Particle.h"


//***************************************************************
//
//	MagicManager�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

namespace
{
	//	��M���
	namespace MAGIC_INFO
	{
		enum
		{
			POS,
			APPEND,
			ERASE
		};
	}

	//	���@�U�����
	struct ReceiveMagicData
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		char infoType;
		int	index;
		Vector3	pos;
	};

	//	���@�������
	struct ReceiveMagicAppend
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		char infoType;
		int	id;
		Vector3	pos;
		float			angle;
	};

	//	���@�������
	struct ReceiveMagicErase
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		char infoType;
		int	index;
		ReceiveMagicErase(int index) : index(index){}
	};
}

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
		org->SetScale( 0.02f );
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
		for ( int i = 0; i < ( int )magicList.size(); i++ )
		{
			magicList[i]->Update();
			particle->Semicircle(magicList[i]->GetPos(), magicList[i]->GetFront(), magicList[i]->GetRight(), magicList[i]->GetUp(), magicList[i]->GetRadius(), 0.4f);
		}
	}

	//	�`��
	void	MagicManager::Render( void )
	{
		for ( int i = 0; i < ( int )magicList.size(); i++ )
		{
			magicList[i]->Render();
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	����M
	void	MagicManager::Receive( const LPSTR& data )
	{
		switch ( data[1] )
		{
		case MAGIC_INFO::POS:
			{
				ReceiveMagicData	* receiveData = ( ReceiveMagicData* )data;
				SetPos( receiveData->index, receiveData->pos );
			}
			break;

		case MAGIC_INFO::APPEND:
			{
				ReceiveMagicAppend*	receiveData = ( ReceiveMagicAppend* )data;
				Append( receiveData->id, receiveData->pos, receiveData->angle );
			}
			break;

		case MAGIC_INFO::ERASE:
			{
				ReceiveMagicErase*	receiveMagicErase = ( ReceiveMagicErase* )data;
				Erase( receiveMagicErase->index );
			}
			break;

		default:
			break;
		}
	}

	//	���X�g�ɒǉ�
	void	MagicManager::Append( int id, const Vector3& pos, float angle )
	{
		//	����
		Magic*	magic = new Magic();

		//	������
		magic->Initialize( org->Clone(), id, pos, angle );

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

	//	���W�ݒ�
	void	MagicManager::SetPos( int index, const Vector3& pos )
	{
		magicList[index]->SetPos( pos );
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���X�g�擾
	std::vector<Magic*>&		MagicManager::GetList( void )
	{
		return	magicList;
	}
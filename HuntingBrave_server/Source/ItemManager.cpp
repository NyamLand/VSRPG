
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<map>
#include	"GameParam.h"
#include	"ItemManager.h"

//*****************************************************************************************************************************
//
//	ItemManager�N���X
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

ItemManager*	itemManager = nullptr;

#define	HEAL_LIFE	30

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	ItemManager::ItemManager( void )
	{
		Initialize();
	}

	//	�f�X�g���N�^
	ItemManager::~ItemManager( void )
	{
		Release();
	}

	//	������
	bool	ItemManager::Initialize( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{	
			itemState[id].leftItem = nullptr;
			itemState[id].rightItem = nullptr;
		}

		return	true;
	}

	//	���
	void	ItemManager::Release( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			SafeDelete( itemState[id].leftItem );
			SafeDelete( itemState[id].rightItem );
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�A�C�e���X�e�[�g�؂芷��
	void	ItemManager::ChangeItemState( int id, char itemType )
	{
		//	ON/OFF
	}

	//	�A�C�e���X�e�[�g�ǉ�
	void	ItemManager::AddItemState( int id, char leftItem, char rightItem )
	{
		
	}

	//	�A�C�e��������
	void	ItemManager::SetItem( Item* item, char itemType )
	{
		if ( item != nullptr )	return;

		switch ( itemType )
		{
		case ITEM_TYPE::ATK:
			break;

		case ITEM_TYPE::DEF:
			break;

		case ITEM_TYPE::HEAL:
			break;

		case ITEM_TYPE::LED:
			break;

		default:
			break;
		}
	}
	
//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	�A�C�e���X�e�[�g�擾
	bool	ItemManager::GetItemState( int id, char itemType )
	{
		return	false;
	}
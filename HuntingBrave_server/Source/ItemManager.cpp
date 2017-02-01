
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
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			itemState[id].leftItem = nullptr;
			itemState[id].rightItem = nullptr;
		}

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
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	ItemManager::Update( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( itemState[i].leftItem != nullptr )		itemState[i].leftItem->Update();
			if ( itemState[i].rightItem != nullptr )	itemState[i].rightItem->Update();
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	����M
	void	ItemManager::ReceiveData( int id, const LPSTR& data )
	{
		//	������
		if ( data[1] == ITEM_TYPE::SET_ITEM )	AddItemState( id, data );

		//	�A�C�e���X�e�[�g�؂�ւ�
		ChangeItemState( id, data[1] );
	}

	//	�A�C�e���X�e�[�g�؂芷��
	void	ItemManager::ChangeItemState( int id, char itemPos )
	{
		switch ( itemPos )
		{
		case ITEM_POS::LEFT_ITEM:
			itemState[id].leftItem->UseItem();
			break;

		case ITEM_POS::RIGHT_ITEM:
			itemState[id].rightItem->UseItem();
			break;

		default:
			break;
		}
	}

	//	�A�C�e���X�e�[�g�ǉ�
	void	ItemManager::AddItemState( int id, const LPSTR& data )
	{
		//	��M�����A�C�e�����
		struct ReceiveData
		{
			char com;
			char itemCom;
			char leftItem;
			char rightItem;
		} *receiveData;

		//	�ϊ�
		receiveData = ( ReceiveData* )data;

		//	�A�C�e���ݒ�
		SetItem( id, itemState[id].leftItem, receiveData->leftItem );
		SetItem( id, itemState[id].rightItem, receiveData->rightItem );
	}

	//	�A�C�e���Z�b�g
	void	ItemManager::SetItem( int id, Item*& item, char itemType )
	{
		if ( item != nullptr )	return;

		switch ( itemType )
		{
		case ITEM_TYPE::ATK:
			item = new AttackItem( id );
			break;

		case ITEM_TYPE::DEF:
			item = new DefenseItem( id );
			break;

		case ITEM_TYPE::HEAL:
			item = new HealItem( id );
			break;

		case ITEM_TYPE::SPEED:
			item = new SpeedItem( id );
			break;

		default:
			printf( "%dP itemSetError\n", id );
			break;
		}
	}
	
//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------


#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"InputManager.h"
#include	"GameParam.h"
#include	"ItemManager.h"

//**********************************************************************
//
//	ItemManager�N���X
//
//**********************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	ITEM_INTERVAL	0.01f

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	ItemManager::ItemManager( void )
	{
		
	}

	//	�f�X�g���N�^
	ItemManager::~ItemManager( void )
	{

	}

	//	������
	bool	ItemManager::Initialize( char itemType1, char itemType2 )
	{
		item[ITEM_POS::LEFT_ITEM] = { itemType1, true, 1.0f  };
		item[ITEM_POS::RIGHT_ITEM] = { itemType2, true, 1.0f };
		return	true;
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	ItemManager::Update( void )
	{
		for ( int i = 0; i < ITEM_POS::ITEM_MAX; i++ )
		{
			if ( !item[i].state )
			{
				item[i].state = Interpolation::PercentageUpdate( item[i].percentage, ITEM_INTERVAL );
			}
		}

		//	���E�L�[�Ŏg�p
		if ( item[ITEM_POS::LEFT_ITEM].state )
		{
			if ( KEY( KEY_LEFT ) == 3 )	
				UseItem( ITEM_POS::LEFT_ITEM );
		}
		
		if ( item[ITEM_POS::RIGHT_ITEM].state )
		{
			if ( KEY( KEY_RIGHT ) == 3 )	
				UseItem( ITEM_POS::RIGHT_ITEM );
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�A�C�e����񑗐M
	void	ItemManager::SendItemState( char item )
	{
		SendItemData	sendItemData( item );

		gameParam->send( ( LPSTR )&sendItemData, sizeof( sendItemData ) );
	}

	//	�A�C�e���ݒ著�M
	void	ItemManager::SendItemSet( char leftItem, char rightItem )
	{
		//	���M����A�C�e�����
		struct
		{
			char com;
			char itemCom;
			char leftItem;
			char rightItem;
		} sendData;

		//	���ݒ�
		sendData.com = SEND_COMMAND::ITEM_INFO;
		sendData.itemCom = ITEM_TYPE::SET_ITEM;
		sendData.leftItem = leftItem;
		sendData.rightItem = rightItem;
		
		//	��񑗐M
		gameParam->send( ( LPSTR )&sendData, sizeof( sendData ) );
	}

	//	�A�C�e�����p
	void	ItemManager::UseItem( char itemPos )
	{
		item[itemPos].percentage = 0.0f;
		item[itemPos].state = false;
		SendItemState( itemPos );
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

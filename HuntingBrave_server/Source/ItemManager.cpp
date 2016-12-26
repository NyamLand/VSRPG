
#include	"iextreme.h"
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
			itemMap[id].clear();
		}

		return	true;
	}

	//	���
	void	ItemManager::Release( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			itemMap[id].clear();
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	��
	void	ItemManager::Heal( int id )
	{
		//	��
		gameParam->GetLifeInfo( id ).CulcLife( HEAL_LIFE );
	}

	//	�U��
	void	ItemManager::Power( int id )
	{
		if ( !itemMap[id][ITEM_TYPE::ATK] )	return;

		//	�U���͑���
	}

	//	�h��
	void	ItemManager::Defense( int id )
	{
		if ( !itemMap[id][ITEM_TYPE::DEF] )	return;

		//	�h��͑���
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�A�C�e���X�e�[�g�؂芷��
	void	ItemManager::ChangeItemState( int id, char itemType )
	{
		//	ON/OFF
		itemMap[id][itemType] = !itemMap[id][itemType];
	}

	//	�A�C�e���X�e�[�g�ǉ�
	void	ItemManager::AddItemState( int id, char itemType )
	{
		//	������Ȃ�
		itemMap[id].insert(
			std::map<char, bool>::value_type( itemType, false ) );
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	�A�C�e���X�e�[�g�擾
	bool	ItemManager::GetItemState( int id, char itemType )
	{
		return	itemMap[id][itemType];
	}
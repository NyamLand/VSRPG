
#pragma once

//*****************************************************************************************************************************
//
//	ItemManager�N���X
//
//*****************************************************************************************************************************

//	include

//	class
class ItemManager
{
private:
	enum ITEM_TYPE
	{
		HEAL,
		ATK,
		DEF,
		LED
	};
	std::map<char, bool>	itemMap[PLAYER_MAX];

public:
	//	�������E���
	ItemManager( void );
	~ItemManager( void );
	bool	Initialize( void );
	void	Release( void );

	//	���ݒ�
	void	ChangeItemState( int id, char itemType );
	void	AddItemState( int id, char itemType );

	//	�A�C�e������
	void	Heal( int id );
	void	Power( int id );
	void	Defense( int id );

	//	���擾
	bool	GetItemState( int id, char itemType );
};

extern	ItemManager*	itemManager;

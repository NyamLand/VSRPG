
#pragma once

//***************************************************************
//
//	ItemSelect�N���X
//
//***************************************************************

//	include
#include	"ItemManager.h"
#include	"Image.h"

//	class
class ItemSelect
{
private:
	//	�\����
	struct ItemIcon
	{
		bool checkState;
		Image*		itemImage;
	};

	struct Result
	{
		bool checkState;
		Image*		resultImage;
		int Width, Height;
	};

private:
	//	�p�����[�^
	int	posX, posY;
	int	select, before;
	int	itemPos;
	float	percentage;
	float	percentage1;
	float	percentage2;
	ItemIcon		itemIcon[ITEM_TYPE::TYPE_MAX];
	Result			result;
	Image*			checkImage[ITEM_TYPE::TYPE_MAX];
	char				selectItem[ITEM_POS::ITEM_MAX];

public:
	//	�������E�J��
	ItemSelect( void );
	~ItemSelect(void);
	bool	Initialize();
	bool	Initialize( int id );

	//	�X�V�E�`��
	bool	Update( void );
	void	Render( void );

	//	����֐�
	bool	OpenItem( void );
	void	MoveCursor( void );
	bool	MoveInterpolation( void );
	bool	Dicision( void );
	bool	ResultCheck(void);
};


#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameManager.h"
#include	"system/System.h"
#include	"ItemManager.h"
#include	"Image.h"
#include	"ItemUI.h"

//***************************************************************
//
//	ItemUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

#define	ICON_SIZE		50
#define	ICON_SPACE	90
#define	ICON_HEIGHT_DIST	20
#define	ICON_SRC_SIZE	128

#define	WIDTH  512				//	�摜����
#define	HEIGHT  256				//	�摜�c��
#define	SPX  0
#define	SPY  256 * 3

namespace 
{
	const LPSTR fileName[] = 
	{
		"DATA/UI/icon/item/01Heal.png",
		"DATA/UI/icon/item/02Atk.png",
		"DATA/UI/icon/item/03Def.png",
		"DATA/UI/icon/item/03Led.png"
	};

}

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	ItemUI::ItemUI( int x, int y, int w, int h )
	{
		posx = x;
		posy = y;
		width = w;
		height = h;

		//	�A�C�R��������
		IconInitialize();

		//	�A�C�e���w�i������
		obj = new Image();
		obj->Initialize( "DATA/UI/main_UI/HP_item_UI.png", 
			posx, posy, width, height, 
			SPX, SPY, WIDTH, HEIGHT );
	}

	//	�f�X�g���N�^
	ItemUI::~ItemUI( void )
	{
		SafeDelete( obj );
		SafeDelete( icon[0] );
		SafeDelete( icon[1] );
	}

	//	�A�C�R��������
	void	ItemUI::IconInitialize( void )
	{
		//	�^�C�v�擾
		char leftItem = itemManager->GetItemType( ITEM_POS::LEFT_ITEM );
		char rightItem = itemManager->GetItemType( ITEM_POS::RIGHT_ITEM );

		//	���A�C�e��������
		icon[ITEM_POS::LEFT_ITEM] = new Image();
		icon[ITEM_POS::LEFT_ITEM]->Initialize(
			fileName[leftItem],
			posx - ICON_SPACE / 2, posy + ICON_HEIGHT_DIST,
			ICON_SIZE, ICON_SIZE,
			0, 0, ICON_SRC_SIZE, ICON_SRC_SIZE );

		//	�E�A�C�e��������
		icon[ITEM_POS::RIGHT_ITEM] = new Image();
		icon[ITEM_POS::RIGHT_ITEM]->Initialize(
			fileName[rightItem],
			posx + ICON_SPACE / 2, posy + ICON_HEIGHT_DIST,
			ICON_SIZE, ICON_SIZE,
			0, 0, ICON_SRC_SIZE, ICON_SRC_SIZE );

		//	��
		itemInterval[ITEM_POS::LEFT_ITEM] = 1.0f;
		itemInterval[ITEM_POS::RIGHT_ITEM] = 1.0f;
	}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

//	�X�V
void	ItemUI::Update( void )
{
	itemInterval[ITEM_POS::LEFT_ITEM] = 
		itemManager->GetInterval( ITEM_POS::LEFT_ITEM );

	itemInterval[ITEM_POS::RIGHT_ITEM] =
		itemManager->GetInterval( ITEM_POS::RIGHT_ITEM );
}

//	�`��
void	ItemUI::Render( void )
{
	obj->Render( IMAGE_MODE::ADOPTPARAM );

	for ( int i = 0; i < ITEM_POS::ITEM_MAX; i++ )
	{
		shader2D->SetValue( "center", Vector3( icon[i]->x, icon[i]->y, 0.0f ) );
		shader2D->SetValue( "radian", ( PI * 2 ) * itemInterval[i] - PI );
		icon[i]->Render( IMAGE_MODE::NORMAL, shader2D, "circleShadow" );
	}
}


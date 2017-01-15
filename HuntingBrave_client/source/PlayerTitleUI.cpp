
#include	"iextreme.h"
#include	"system/System.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"PlayerTitleUI.h"

//***************************************************************
//
//	PlayerTitleUI�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

#define	FRONT_MAX		10
#define	SRC_W		256
#define	SRC_H		102

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PlayerTitleUI::PlayerTitleUI( void ) : frontTitleImage( nullptr ), backTitleImage( nullptr ),
		index( - 1 ), posx( 0 ), posy( 0 )
	{

	}

	//	�f�X�g���N�^
	PlayerTitleUI::~PlayerTitleUI( void )
	{
		SafeDelete( frontTitleImage );
		SafeDelete( backTitleImage );
	}

	//	������ front : 0 ~ 19 back : 0 ~ 9
	void	PlayerTitleUI::Initialize( int front, int back, int x, int y, int w, int h )
	{
		this->front = front;
		this->back = back;

		//	�O�̍�������
		frontTitleImage = new Image();
		
		//	frontTitle������
		if ( front >= FRONT_MAX )
		{
			frontTitleImage->Initialize( "DATA/UI/menu_UI/PlTitle_front01.png", 
				x - w / 2, y, w, h, 
				( ( front - FRONT_MAX ) % 2 ) * SRC_W,
				( ( front - FRONT_MAX ) / 2 )	 * SRC_H,
				SRC_W, SRC_H );
		}
		else
		{
			frontTitleImage->Initialize( "DATA/UI/menu_UI/PlTitle_front02.png",
				x - w / 2, y, w, h,
				( front % 2 ) * SRC_W,
				( front / 2 )	 * SRC_H,
				SRC_W, SRC_H );
		}

		//	backTitle������
		backTitleImage = new Image();
		backTitleImage->Initialize( "DATA/UI/menu_UI/PlTitle_back01.png",
			x + w / 2, y, w, h,
			( back % 2 ) * SRC_W,
			( back / 2 )	 * SRC_H,
			SRC_W, SRC_H );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	PlayerTitleUI::Update( void )
	{

	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�`��
	void	PlayerTitleUI::Render( void )
	{
		frontTitleImage->Render( IMAGE_MODE::NORMAL );
		backTitleImage->Render( IMAGE_MODE::NORMAL );
	}

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

	//	���W
	void	PlayerTitleUI::SetPos( int x, int y )
	{
		frontTitleImage->x = x - frontTitleImage->w / 2;
		frontTitleImage->y = y;
		backTitleImage->x = x + frontTitleImage->w / 2;
		backTitleImage->y = y;
	}

	//	�̍��ݒ�
	void	PlayerTitleUI::SetTitle( int front, int back )
	{
		this->front = front;
		this->back = back;

		//	frontTitle������
		if ( front >= FRONT_MAX )
		{
				frontTitleImage->sx = ( ( front - FRONT_MAX ) % 2 ) * SRC_W;
				frontTitleImage->sy = ( ( front - FRONT_MAX ) / 2 )	 * SRC_H;
		}
		else
		{
				frontTitleImage->sx = ( front % 2 ) * SRC_W;
				frontTitleImage->sy = ( front / 2 )	 * SRC_H;
		}

		//	backTitle������
		backTitleImage->sx = ( back % 2 ) * SRC_W;
		backTitleImage->sy = ( back / 2 ) * SRC_H;
	}
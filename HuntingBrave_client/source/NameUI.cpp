
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameParam.h"
#include	"InputManager.h"
#include	"NameUI.h"

//***************************************************************
//
//	NameUI�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

#define	SRC_X_MAX		9
#define	SRC_Y_MAX		5
#define	SRC_SIZE			64

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NameUI::NameUI( void ) : posX( 0 ), posY( 0 ), space( 0 ), scale( 0 )
	{
		for ( int i = 0; i < NAME_MAX; i++ )
		{
			nameImage[i] = nullptr;
		}
	}

	//	�f�X�g���N�^
	NameUI::~NameUI( void )
	{
		for (int i = 0; i < NAME_MAX; i++ )
		{
			SafeDelete( nameImage[i] );
		}
	}

	//	������
	bool	NameUI::Initialize( int x, int y, int w, int h, int* name )
	{
		scale = w;
		space = w + 10;
		posX = x;
		posY = y;

		for ( int i = 0; i < NAME_MAX; i++ )
		{
			nameImage[i] = new Image();
			nameImage[i]->Initialize( "DATA/UI/main_UI/ward.png", x, y, w, h, 0, 0, SRC_SIZE, SRC_SIZE );
			
			//	�ǂݍ��݈ʒu�ݒ�
			if ( name[i] == 0 )
			{
				nameImage[i]->sy = 0;
				nameImage[i]->sx = 0;
			}
			else
			{
				nameImage[i]->sy = SRC_SIZE * ( name[i] / SRC_X_MAX );

				if ( nameImage[i]->sy == 0 )	nameImage[i]->sx = name[i];
				else nameImage[i]->sx = SRC_SIZE * ( name[i] % ( nameImage[i]->sy * SRC_X_MAX ) );
			}
		}
		return	true;
	}

//----------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------

	//	�X�V
	void	NameUI::Update( void )
	{
		for ( int i = 0; i < NAME_MAX; i++ ) 
		{
			nameImage[i]->x = ( int )( posX - ( space * 1.5f ) + ( space * i ) );
			nameImage[i]->y = posY;
		}
	}

	//	�`��
	void	NameUI::Render( void )
	{
		for ( int i = 0; i < NAME_MAX; i++ )
		{
			nameImage[i]->Render( IMAGE_MODE::NORMAL );
		}
	}

//----------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

	//	���W�ݒ�
	void	NameUI::SetPos( int posx, int posy )
	{
		posX = posx;
		posY = posy;
	}

	//	�Ԋu�ݒ�
	void	NameUI::SetSpace( int space )
	{
		this->space = space;
	}

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------


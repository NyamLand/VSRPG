
#include	"iextreme.h"
#include	"system/System.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameParam.h"
#include	"InputManager.h"
#include	"ItemSelect.h"

//***************************************************************
//
//	ItemSelect�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

namespace
{
	//	�t�@�C����
	namespace
	{
		const LPSTR filename[] =
		{
			"DATA/UI/icon/item/01Heal.png",
			"DATA/UI/icon/item/02Atk.png",
			"DATA/UI/icon/item/03Def.png",
			"DATA/UI/icon/item/03Led.png"
		};
	}
	
	//	�摜�T�C�Y
	#define	IMAGE_SIZE		90
	#define	IMAGE_SPACE		100
	#define	IMAGE_BIG_SIZE		110

	//	�ǂݍ��݃T�C�Y
	#define	SRC_SIZE		128
}

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	ItemSelect::ItemSelect( void ) : posX( 0 ), posY( 0 ), select1( 0 ), select2( 0 ), before( 1 ),
		percentage( 0.0f ), percentage1( 0.0f ), percentage2( 1.0f ), circleGage( 0.0f )
	{
		//	�摜
		for ( int i = 0; i < 4; i++ )
		{
			itemImage[i] = nullptr;
			itemImage[i] = new Image();
		}
	}

	//	�f�X�g���N�^
	ItemSelect::~ItemSelect( void )
	{
		for ( int i = 0; i < 4; i++ )
		{
			SafeDelete( itemImage[i] );
		}
	}

	//	������
	bool	ItemSelect::Initialize( int id )
	{
		posX = ( int )( iexSystem::ScreenWidth / 4 );
		posY = ( int )( iexSystem::ScreenHeight * 0.7f );
		for ( int i = 0; i < 4; i++ )
		{
			itemImage[i]->Initialize( filename[i],
				posX - ( int )( IMAGE_SPACE * 1.5f ) + ( IMAGE_SPACE * i ), 
				posY, 
				IMAGE_SIZE, IMAGE_SIZE, 0, 
				0, SRC_SIZE, SRC_SIZE );
		}

		return	true;
	}

//----------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------

	//	�X�V
	void	ItemSelect::Update( void )
	{
		circleGage += 0.02f;
		if ( circleGage >= 1.0f	)	circleGage = 0.0f;

		//	�W�J
		for ( int i = 0; i < 4; i++ )
		{
			Interpolation::CubicFunctionInterpolation( itemImage[i]->x, posX, ( int )( posX - ( IMAGE_SPACE * 1.5f ) + ( IMAGE_SPACE * i ) ), percentage );
		}
		if ( !Interpolation::PercentageUpdate( percentage, 0.05f ) )	return;

		//	���͎擾
		float	axisX, axisY;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	���
		bool state1 = Interpolation::PercentageUpdate( percentage1, 0.1f );
		bool state2 = Interpolation::PercentageUpdate( percentage2, 0.1f );
		Interpolation::LinearInterpolation( itemImage[select1]->w, IMAGE_SIZE, IMAGE_BIG_SIZE, percentage1 );
		Interpolation::LinearInterpolation( itemImage[select1]->h, IMAGE_SIZE, IMAGE_BIG_SIZE, percentage1 );
		Interpolation::LinearInterpolation( itemImage[before]->w, IMAGE_BIG_SIZE, IMAGE_SIZE, percentage2 );
		Interpolation::LinearInterpolation( itemImage[before]->h, IMAGE_BIG_SIZE, IMAGE_SIZE, percentage2 );

		//	�I��
		if ( state1 && state2 )
		{
			if ( abs( axisX ) >= 0.3f )
			{
				before = select1;
				if ( axisX > 0.0f )	select1++;
				else select1--;
				percentage1 = percentage2 = 0.0f;

				if ( select1 >= 4 )		select1 = 0;
				if ( select1 < 0 )	select1 = 3;
			}
		}
	}

	//	�`��
	void	ItemSelect::Render( void )
	{
		for ( int i = 0; i < 4; i++ )
		{
			itemImage[i]->Render( IMAGE_MODE::NORMAL );
		}
	}

//----------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------


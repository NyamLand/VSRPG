
#include	"iextreme.h"
#include	"system/System.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameParam.h"
#include	"Sound.h"
#include	"InputManager.h"
#include	"ItemManager.h"
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

	//	�`�F�b�N�A�C�R���ǂݍ���
	#define	CHECK_SRC_POS_X	650
	#define	CHECK_SRC_POS_Y		240
	#define	CHECK_SRC_SIZE_X	325
	#define	CHECK_SRC_SIZE_Y	240

	//	�ǂݍ��݃T�C�Y
	#define	SRC_SIZE		128

	//	��ԃX�s�[�h
	#define	LERP_SPEED	0.1f
	#define	OPEN_SPEED	0.05f

	//	���͍ŏ��l
	#define	MIN_INPUT	0.3f
}

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	ItemSelect::ItemSelect( void ) : posX( 0 ), posY( 0 ), select( 0 ), before( 1 ),
		percentage( 0.0f ), percentage1( 0.0f ), percentage2( 1.0f )
	{
		//	�摜
		for ( int i = 0; i < ITEM_TYPE::TYPE_MAX; i++ )
		{
			itemIcon[i].itemImage = nullptr;
			itemIcon[i].itemImage = new Image();

			checkImage[i] = nullptr;
			checkImage[i] = new Image();
		}

		result.resultImage = nullptr;
		result.resultImage = new Image();


		selectItem[ITEM_POS::LEFT_ITEM] = 0;
		selectItem[ITEM_POS::RIGHT_ITEM] = 0;
	}

	//	�f�X�g���N�^
	ItemSelect::~ItemSelect( void )
	{
		for ( int i = 0; i < ITEM_TYPE::TYPE_MAX; i++ )
		{
			SafeDelete( itemIcon[i].itemImage );
			SafeDelete( checkImage[i] );
		}

		SafeDelete(result.resultImage);
	}

	//	������
	bool	ItemSelect::Initialize()
	{
		posX = (int)(iexSystem::ScreenWidth / 4);
		posY = (int)(iexSystem::ScreenHeight * 0.7f);
		for (int i = 0; i < ITEM_TYPE::TYPE_MAX; i++)
		{
			//	�A�C�e���A�C�R��������
			itemIcon[i].itemImage->Initialize(filename[i],
				posX - (int)(IMAGE_SPACE * 1.5f) + (IMAGE_SPACE * i),
				posY,
				IMAGE_SIZE, IMAGE_SIZE,
				0, 0, SRC_SIZE, SRC_SIZE);
			itemIcon[i].checkState = false;

			checkImage[i]->Initialize(
				"DATA/UI/BackGround/matching_gamen_parts.png",
				itemIcon[i].itemImage->x, itemIcon[i].itemImage->y,
				IMAGE_SIZE, IMAGE_SIZE,
				CHECK_SRC_POS_X, CHECK_SRC_POS_Y,
				CHECK_SRC_SIZE_X, CHECK_SRC_SIZE_Y);

			checkImage[i]->renderflag = false;
			itemPos = ITEM_POS::LEFT_ITEM;



			//�A�C�e���ŏI�m�F����
			result.Width = 0;
			result.Height = 0;
			result.resultImage->Initialize("DATA/UI/menu_UI/last_understand.png",
				iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 2, 512, 512,
				0, 0, result.Width, result.Height);
			result.checkState = false;

		}

		return	true;
	}

	bool	ItemSelect::Initialize( int id )
	{
		posX = ( int )( iexSystem::ScreenWidth / 4 );
		posY = ( int )( iexSystem::ScreenHeight * 0.7f );
		for ( int i = 0; i < ITEM_TYPE::TYPE_MAX; i++ )
		{
			//	�A�C�e���A�C�R��������
			itemIcon[i].itemImage->Initialize( filename[i],
				posX - ( int )( IMAGE_SPACE * 1.5f ) + ( IMAGE_SPACE * i ), 
				posY, 
				IMAGE_SIZE, IMAGE_SIZE, 
				0,	0, SRC_SIZE, SRC_SIZE );
			itemIcon[i].checkState = false;

			checkImage[i]->Initialize( 
				"DATA/UI/BackGround/matching_gamen_parts.png",
				itemIcon[i].itemImage->x, itemIcon[i].itemImage->y, 
				IMAGE_SIZE, IMAGE_SIZE,
				CHECK_SRC_POS_X, CHECK_SRC_POS_Y,
				CHECK_SRC_SIZE_X, CHECK_SRC_SIZE_Y );

			checkImage[i]->renderflag = false;
			itemPos = ITEM_POS::LEFT_ITEM;



			//�A�C�e���ŏI�m�F����
			result.Width = 0;
			result.Height = 0;
			result.resultImage->Initialize("DATA/UI/menu_UI/last_understand.png",
				iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 2, 512, 512,
				0, 0, result.Width, result.Height);
			result.checkState = false;

		}

		return	true;
	}

//----------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------

	//	�X�V
	bool	ItemSelect::Update( void )
	{
		//	�W�J
		bool	openState = OpenItem();
		if ( !openState )	return false;

		//	�I��
		bool dicisionState = false;
		if (itemPos != ITEM_POS::ITEM_MAX)
		{
			bool moveState = MoveInterpolation();
			if (moveState)
			{
				//	�J�[�\���ړ�
				MoveCursor();

				//	����
				if (KEY(KEY_TYPE::A) == 3)	dicisionState = Dicision();
			}
		}
		else if (itemPos == ITEM_POS::ITEM_MAX)
		{
			dicisionState = ResultCheck();
		}

		return	dicisionState;
	}

	//	�`��
	void	ItemSelect::Render( void )
	{
		for ( int i = 0; i < ITEM_TYPE::TYPE_MAX; i++ )
		{
			itemIcon[i].itemImage->Render( IMAGE_MODE::NORMAL );
			checkImage[i]->Render( IMAGE_MODE::NORMAL );
		}


		result.resultImage->Render(IMAGE_MODE::ADOPTPARAM, iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 2, result.Width, result.Height,
			0, 0, 512, 512);
	}

//----------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------

	//	�A�C�e���W�J
	bool	ItemSelect::OpenItem( void )
	{
		bool openState = Interpolation::PercentageUpdate( percentage, OPEN_SPEED );

		//	�W�J
		for ( int i = 0; i < ITEM_TYPE::TYPE_MAX; i++ )
		{
			Interpolation::CubicFunctionInterpolation( 
				itemIcon[i].itemImage->x, 
				posX, 
				( int )( posX - ( IMAGE_SPACE * 1.5f ) + ( IMAGE_SPACE * i ) ), 
				percentage );
		}

		return	openState;
	}

	//	�J�[�\�����
	bool	ItemSelect::MoveInterpolation( void )
	{
		//	���
		bool state1 = Interpolation::PercentageUpdate( percentage1, LERP_SPEED );
		bool state2 = Interpolation::PercentageUpdate( percentage2, LERP_SPEED );
		Interpolation::LinearInterpolation( itemIcon[select].itemImage->w, IMAGE_SIZE, IMAGE_BIG_SIZE, percentage1 );
		Interpolation::LinearInterpolation( itemIcon[select].itemImage->h, IMAGE_SIZE, IMAGE_BIG_SIZE, percentage1 );
		Interpolation::LinearInterpolation( itemIcon[before].itemImage->w, IMAGE_BIG_SIZE, IMAGE_SIZE, percentage2 );
		Interpolation::LinearInterpolation( itemIcon[before].itemImage->h, IMAGE_BIG_SIZE, IMAGE_SIZE, percentage2 );

		if ( state1 && state2 )	return	true;
		return	false;
	}

	//	�J�[�\���ړ�
	void	ItemSelect::MoveCursor( void )
	{
		//	���͎擾
		float	axisX, axisY;
		inputManager->GetStickInputLeft( axisX, axisY );

		if ( abs( axisX ) >= MIN_INPUT )
		{
			before = select;
			if ( axisX > 0.0f )
			{
				select++;
				if ( select >= ITEM_TYPE::TYPE_MAX )
				{
					select = 0;
					if ( itemIcon[select].checkState )	select++;
				}
				else
				{
					//	�I���ς݂Ȃ�X�L�b�v
					if ( itemIcon[select].checkState )	select++;
					if ( select >= ITEM_TYPE::TYPE_MAX )	select = 0;
				}
			}
			else
			{
				select--;
				if ( select < 0 )
				{
					select = ITEM_TYPE::TYPE_MAX - 1;
					if ( itemIcon[select].checkState )	select--;
				}
				else
				{
					//	�I���ς݂Ȃ�X�L�b�v
					if ( itemIcon[select].checkState )	select--;
					if ( select < 0 )	select = ITEM_TYPE::TYPE_MAX - 1;
				}

			}
			
			sound->PlaySE(SE::MOVE_SELECT);

			//	�p�����[�^���Z�b�g
			percentage1 = percentage2 = 0.0f;
		}
	}

	//	����
	bool	ItemSelect::Dicision( void )
	{
		//	���W����
		checkImage[select]->renderflag = true;
		itemIcon[select].checkState = true;
		selectItem[itemPos] = select;
		itemPos++;

		////	��I���ŏI��
		//if (itemPos == ITEM_POS::ITEM_MAX)
		//{
		//	itemManager->Initialize( 
		//		selectItem[ITEM_POS::LEFT_ITEM], 
		//		selectItem[ITEM_POS::RIGHT_ITEM] );
		//	itemManager->SendItemSet( 
		//		selectItem[ITEM_POS::LEFT_ITEM], 
		//		selectItem[ITEM_POS::RIGHT_ITEM] );

		//	sound->PlaySE(SE::IM_OK);

		//	return true;
		//}
		/*else*/ sound->PlaySE(SE::OK);

		
		//	�J�[�\�����炵
		before = select;
		select++;
		if ( select >= ITEM_TYPE::TYPE_MAX )	select = 0;
		percentage1 = percentage2 = 0.0f;
		return	false;
	}



	bool	ItemSelect::ResultCheck(void)
	{
		static bool state = false;
		static bool state2 = false;

		if (state == false)
		{
			if (result.Width < 512) result.Width += 16;
			if (result.Height < 512) result.Height += 16;
			if (result.Width >= 512 && result.Height >= 512) state = true;
		}



		if (state == true)
		{
			if (KEY(KEY_TYPE::A) == 3)
			{
				itemManager->Initialize(
					selectItem[ITEM_POS::LEFT_ITEM],
					selectItem[ITEM_POS::RIGHT_ITEM]);
				itemManager->SendItemSet(
					selectItem[ITEM_POS::LEFT_ITEM],
					selectItem[ITEM_POS::RIGHT_ITEM]);

				sound->PlaySE(SE::IM_OK);
				return true;
			}
			else if (KEY(KEY_TYPE::B) == 3)
			{
				state2 = true;

			}
			if (state2 == true)
			{
				if (result.Width > 0) result.Width -= 16;
				if (result.Height > 0) result.Height -= 16;

				if (result.Width <= 0 && result.Height <= 0)
				{
					state = false;
					state2 = false;
					Initialize();
				}
			}
		}
		return false;
	}
//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------


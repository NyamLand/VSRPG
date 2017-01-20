
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"Image.h"
#include	"MapUI.h"

//***************************************************************
//
//	MapUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//	�}�b�v�A���[�_�[����
#define	MAP_MAX_LENGTH		400.0f
#define	RADER_LENGTH		50.0f

//	�}�b�vUI�T�C�Y
#define	MAP_SIZE		250
#define	MAP_POS_X		1150
#define	MAP_POS_Y		130
#define	MAP_SRC_SIZE	512

//	�A�C�R��UI�T�C�Y
#define	ICON_SIZE	15
#define	MY_ICON_SIZE	20
#define	ICON_MAX_POS	125
#define	ICON_SRC_POS	512
#define	ICON_SRC_SIZE	32

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	MapUI::MapUI( void )
	{
		//	���W�A�T�C�Y���i�[
		posx = MAP_POS_X;	
		posy = MAP_POS_Y;	
		width = MAP_SIZE;	
		height = MAP_SIZE;

		//	���[�_�[�w�i������
		back = new Image();
		back->Initialize( "DATA/UI/main_UI/Map_UI.png", 
			MAP_POS_X, MAP_POS_Y, 
			MAP_SIZE, MAP_SIZE, 
			0, 0, MAP_SRC_SIZE, MAP_SRC_SIZE );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			player[i] = new Image();
			player[i]->Initialize( "DATA/UI/main_UI/Map_UI.png",
				MAP_POS_X, MAP_POS_Y,
				ICON_SIZE, ICON_SIZE,
				ICON_SRC_POS + ICON_SRC_SIZE * ( i % 2 ), 
				ICON_SRC_SIZE * ( i / 2 ), 
				ICON_SRC_SIZE, ICON_SRC_SIZE );

			if ( !gameParam->GetPlayerActive( i ) )	player[i]->renderflag = false;

			//	���L���������኱�傫���\��
			if ( gameParam->GetMyIndex() == i )
			{
				player[i]->w = player[i]->h = MY_ICON_SIZE;
			}
		}
	}

	//	�f�X�g���N�^
	MapUI::~MapUI( void )
	{
		SafeDelete( back );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( player[i] );
		}
	}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

	//	�X�V
	void	MapUI::Update( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( !gameParam->GetPlayerActive( i ) )	continue;

			PlayerParam	playerParam = gameParam->GetPlayerParam( i );

			//	�}�b�v��������̋��������߂�
			Vector3 vec = playerParam.pos - Vector3( 0.0f, 0.0f, 0.0f );

			//	�}�b�v�\���p�Ɋ��������߂�
			float length = vec.Length() / MAP_MAX_LENGTH;

			//	�}�b�v��̃A�C�R�����W�����߂�
			vec.Normalize();
			Vector3 iconPos = vec * ( ICON_MAX_POS * length );

			//	�A�C�R�����W�ݒ�
			player[i]->x = player[i]->p.x = MAP_POS_X + ( int )iconPos.x;
			player[i]->y = player[i]->p.y = MAP_POS_Y - ( int )iconPos.z;

			//	�A�C�R�������ݒ�
			player[i]->angle = playerParam.angle;
		}
	}

	//	�`��
	void	MapUI::Render( void )
	{
		back->Render( IMAGE_MODE::ADOPTPARAM );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			player[i]->Render( IMAGE_MODE::ADOPTPARAM );
		}
	}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------


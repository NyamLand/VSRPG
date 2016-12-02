
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
#include	"Random.h"
#include	"GlobalFunction.h"
#include	"Image.h"
#include	"DrawShape.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"EnemyManager.h"
#include	"Collision.h"
#include	"Sound.h"

//
#include	"BaseEquipment.h"
//

#include	"sceneMain.h"
#include	"sceneMatching.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************


//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************

bool	sceneMatching::Initialize(void)
{
	//	���ݒ�
	iexLight::SetAmbient( 0x404040 );
	iexLight::SetFog( 800, 1000, 0 );

	Vector3 dir( 1.0f, -1.0f, -0.5f );
	dir.Normalize();
	iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

	//	�J�����ݒ�
	mainView = new Camera();
	mainView->Initialize(
		Camera::VIEW_MODE::TRACKING_VIEW,
		Vector3( 0.0f, 5.0f, -20.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	�t�@�C���ݒ�

	//	���f��������
	for ( int i = 0; i < PLAYER_MAX; i++ )
	{
		obj[i] = make_unique<iex3DObj>( LPSTR( "DATA/CHR/suppin/suppin.IEM" ) );		
		char	fileName[256] = "DATA/CHR/suppin/s_body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", i );
		strcat_s( fileName, playerNum );
		obj[i]->SetTexture( 0, fileName );
	}

	//	GameParam������
	gameParam = new GameParam();
	
	//	�e�L�X�g�ǂݍ���
	std::ifstream	ifs( "onlineInfo.txt" );
	ifs >> addr;
	ifs >> name;

	//	�摜�ǂݍ���
	back = new iex2DObj( "DATA/UI/BackGround/matching_gamen.png" );

	//	BGM�Đ�( �����_���Ō�����̃e�[�} )
	if ( random->PercentageRandom( 0.2f ) )	sound->PlayBGM( BGM::IIWAKE );
	else	sound->PlayBGM( BGM::MENU );

	step = 0;
	return true;
}

sceneMatching::~sceneMatching( void )
{
	SafeDelete( mainView );
	SafeDelete( back );
	sound->StopBGM();
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneMatching::Update( void )
{
	//	�T�[�o�[�������M
	gameParam->Update();

	//	�e�X�g
	switch ( step )
	{
	case 0:
		//	�N���C�A���g������( server�Ɛڑ� )
		if( gameParam->InitializeClient( addr, 7000, name ) )	step++;
		break;

	case 1:
		//	GameManager�X�V
		gameManager->Update();
	
		//	���f���X�V
		ObjUpdate();
	
		CheckComplete();
	
		if ( KEY_Get( KEY_ENTER ) == 3 )
		{
			gameManager->isComplete = true;
		}
		break;
	}

}

void	sceneMatching::ObjUpdate()
{
	//�ڑ����Ă邩�ǂ��������̊m�F�̂��߁A���W�����`��̓N���C�A���g�ł������E�E�E�悭�Ȃ��H
	Vector3 temppos;
	for ( int i = 0; i < PLAYER_MAX; i++ )
	{
		temppos = Vector3( -10.0f + i * 5.0f, 0, 0 );
		int active = gameParam->GetPlayerActive( i );

		if ( active )
		{
			obj[i]->SetPos( temppos );
			obj[i]->SetAngle( 180 * PI / 180 );
			obj[i]->SetScale( 0.2f );
			obj[i]->Animation();
			obj[i]->Update();
		}
	}
}

void	sceneMatching::CheckComplete()
{
	bool check = true;
	for ( int i = 0; i < PLAYER_MAX; i++ )
	{
		if ( gameParam->GetPlayerActive( i ) )
		{
			if ( gameParam->GetMatchingInfo( i ).isComplete == false ) check = false;
		}
	}

	if ( check )
	{
		gameManager->isComplete = false;
		MainFrame->ChangeScene( new sceneMain() );
		return;
	}
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************
void	sceneMatching::Render(void)
{
	//	��ʃN���A
	mainView->Activate();
	mainView->Clear();

	//	back
	iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
	back->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
	iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

	for ( int i = 0; i < PLAYER_MAX; i++ )
	{
		int active = gameParam->GetPlayerActive( i );

		if ( active )
		{
			obj[i]->Render();
		}
	}

	//	�e�v���C���[���W�\��
	DebugRender();

	//MyInfoRender();
}

//	debug�p�`��
void	sceneMatching::DebugRender( void )
{
	for ( int p = 0; p < PLAYER_MAX; p++ )
	{
		//	�e�v���C���[���O�C�����Ă��邩�ǂ���
		PlayerParam	playerParam = gameParam->GetPlayerParam( p );
		int active = gameParam->GetPlayerActive( p );

		char	str[256];
		char	str2[256];

		if ( gameParam->GetMatchingInfo( p ).isComplete == false )sprintf_s( str2, "Enter�L�[�������Ă�������" );
		else sprintf_s( str2, "��������" );

		if ( active )
		{
			sprintf_s( str, "%dP pos = �ڑ��� : %s", p + 1, str2 );
		}
		else
		{
			sprintf_s( str, "%dP pos = �ҋ@�� : %s", p + 1, str2 );
		}
		IEX_DrawText( str, 20, 300 + p * 50, 500, 200, 0xFFFFFF00 );
	}
}

//	�����̏��\��
void	sceneMatching::MyInfoRender( void )
{
	//	������ID( Player�ԍ� )
	int	 id = gameParam->GetMyIndex();

	//	�����̖��O
	LPSTR name = gameParam->GetPlayerName(id);

	//	�\��
	char	str[256];
	//sprintf_s(str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z);
	IEX_DrawText(str, 20, 50, 500, 500, 0xFFFFFF00);
}








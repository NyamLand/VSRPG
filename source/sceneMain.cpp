
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<string>
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"

#pragma comment( lib, "WSOCK32.lib" )

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

iexMesh*	stage = nullptr;	//	��(��Ώ���)



//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************

bool	sceneMain::Initialize( void )
{
	//	WinSock������
	WSADATA	wsaData;
	WSAStartup( MAKEWORD( 1, 1 ), &wsaData );

	//	���ݒ�
	iexLight::SetAmbient( 0x404040 );
	iexLight::SetFog( 800, 1000, 0 );

	Vector3 dir( 1.0f, -1.0f, -0.5f );
	dir.Normalize();
	iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );
	
	//	GameParam������
	m_GameParam = new GameParam();
	gameParam = m_GameParam;

	//	�J�����ݒ�
	mainView = new Camera();
	mainView->Initialize(
		Camera::VIEW_MODE::TRACKING_VIEW,
		Vector3( 0.0f, 15.0f, -15.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	player�ݒ�
	playerManager->Initialize();

	//	stage�ݒ�
	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

	//	ui�̐ݒ�
	uiManager->Initialize();

	//	GameManager�̏�����
	gameManager->Initialize();

	char addr[64], name[64];
	std::ifstream	ifs( "onlineInfo.txt" );
	ifs >> addr;
	ifs >> name;

	//	�N���C�A���g������( server�Ɛڑ� )
	if ( !m_GameParam->InitializeClient( addr, PORT_NUM, name, 0 ) )
	{
		MessageBox( iexSystem::Window, "�N���C�A���g���������s", "ERROR", MB_OK );
		PostQuitMessage( 0 );
		return	false;
	}
	
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	SafeDelete( m_GameParam );
	playerManager->Release();
	uiManager->Release();

	//	WinSock�I��
	WSACleanup();
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	m_GameParam->Update();

	//	GameManager�X�V
	gameManager->Update();

	//	player�X�V
	playerManager->Update();

	//	ui�X�V
	uiManager->Update();

	//	camera�X�V
	mainView->Update( playerManager->GetPlayer()->GetPos() );
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	//	��ʃN���A
	mainView->Activate();
	mainView->Clear();

	//	stage�`��
	stage->Render();

	//	player�`��
	playerManager->Render();

	//	ui�`��
	uiManager->Render();

	//	�e�v���C���[���W�\��
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			Vector3	p_pos = m_GameParam->GetPlayerParam( p ).pos;
			char	str[256];
			sprintf_s( str, "%dP pos = Vector3( %.2f, %.2f, %.2f )",  p + 1, p_pos.x, p_pos.y, p_pos.z );
			IEX_DrawText( str, 20 , 300 + p * 50, 500, 200, 0xFFFFFF00 );
		}
	}

	MyInfoRender();
}

//	��

//	�����̏��\��
void	sceneMain::MyInfoRender( void )
{
	//	������ID( Player�ԍ� )
	int	 id = m_GameParam->GetMyIndex();
	
	//	�����̖��O
	LPSTR name = m_GameParam->GetMyInfo( id ).name;
	
	//	�����̍��W
	Vector3	pos = m_GameParam->GetPlayerParam( id ).pos;

	//	�\��
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}









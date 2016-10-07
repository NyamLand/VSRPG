
#include	"iextreme.h"
#include	"system/system.h"
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

	//	�N���C�A���g������
	if ( !m_GameParam->InitializeClient( LPSTR( "127.0.0.1" ), PORT_NUM, LPSTR( "aaa" ), 0 ) )
	{
		MessageBox( iexSystem::Window, "�N���C�A���g���������s", "ERROR", MB_OK );
		PostQuitMessage( 0 );
		return	true;
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
}




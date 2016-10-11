
#include	"iextreme.h"
#include	"system/system.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"Enemy.h"

#pragma comment( lib, "WSOCK32.lib" )

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

iexMesh*	stage = nullptr;	//	��(��Ώ���)

Enemy* enemy;

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

	// enemy
	enemy = new Enemy;
	enemy->Initialize();

	//	stage�ݒ�
	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

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
	SafeDelete(enemy);
	playerManager->Release();

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

	//	gameManager�X�V
	gameManager->Update();

	//	player�X�V
	playerManager->Update();

	enemy->Update();
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

	enemy->Render();
}




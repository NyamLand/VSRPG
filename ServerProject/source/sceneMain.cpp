
#include	"iextreme.h"
#include	<thread>
#include	"system/system.h"
#include	"GameParam.h"
#include	"GlobalFunction.h"
#include	"PlayerManager.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

GameParam*	sceneMain::gameParam;

//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************

bool	sceneMain::Initialize( void )
{
	//	���ݒ�
	iexLight::SetAmbient( 0x404040 );
	iexLight::SetFog( 800, 1000, 0 );

	Vector3 dir( 1.0f, -1.0f, -0.5f );
	dir.Normalize();
	iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

	//	�J�����ݒ�
	view = new iexView();
	view->Set( Vector3( 0, 3, -5 ), Vector3( 0, 0, 0 ) );

	//	�Q�[���p�����[�^������
	gameParam = new GameParam();

	//	�v���C���[������
	playerManager->Initialize( gameParam );

	//	�T�[�o�[������
	gameParam->InitializeServer();

	return true;
}

sceneMain::~sceneMain( void )
{
	playerManager->Release();
	SafeDelete( view );
	SafeDelete( gameParam );

}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	int client = gameParam->Receive();

	if ( client != -1 )
	{
		playerManager->Update( client );
		gameParam->Send( client );
	}
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	//	��ʃN���A
	view->Activate();
	view->Clear();

	gameParam->Render();






}





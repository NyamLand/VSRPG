
#include	"iextreme.h"
#include	"system/system.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"

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
		Vector3( 0.0f, 15.0f, -15.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	player�ݒ�
	playerManager->Initialize();

	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	playerManager->Release();



}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	//	gameManager�X�V
	gameManager->Update();

	//	player�X�V
	playerManager->Update();

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

	stage->Render();

	//	player�`��
	playerManager->Render();

}




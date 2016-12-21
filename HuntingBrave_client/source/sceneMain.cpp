
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<vector>
#include	<thread>
#include	<map>
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
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"NameManager.h"
#include	"Collision.h"
#include	"Sound.h"

//
#include	"BaseEquipment.h"
//

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

iexMesh*	stage = nullptr;	//	��(��Ώ���)
iexMesh*	magic = nullptr;	//	��(��Ώ���)
BaseEquipment* baseEquipment;	//	��(��Ώ���)

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

	//	player������
	playerManager->Initialize();

	//	enemy������
	enemyManager->Initialize();

	//	magic������
	magicManager->Initialize();
	
	//	stage������
	stage = new iexMesh( "DATA/BG/stage.imo" );
	stage->SetPos( 0.0f, -5.0f, 0.0f );
	stage->SetScale( 0.1f );
	stage->Update();

	baseEquipment = new BaseEquipment("DATA\\player_data.csv");

	//	ui�̐ݒ�
	uiManager->Initialize();

	//	�퓬BGM
	sound->PlayBGM( BGM::MAIN );

	//	���M
	gameParam->SendResponseInfo( RESPONSE_COMMAND::GAME_START );

	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	enemyManager->Release();
	uiManager->Release();
	magicManager->Release();
	playerManager->Release();
	sound->StopBGM();
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	//	�o�ߎ��Ԏ擾
	float elapseTime = GetElapseTime();

	//	����M
	std::thread		ThreadFunc( ThreadFunction );
	ThreadFunc.join();

	//	GameManager�X�V
	gameManager->Update();

	//	player�X�V
	playerManager->Update();

	//	enemy�X�V
	enemyManager->Update();

	//	magic�X�V
	magicManager->Update();

	//	ui�X�V
	uiManager->Update();

	//	camera�X�V
	int index = gameParam->GetMyIndex();
	mainView->Update( playerManager->GetPlayer( index )->GetPos() );

	//	collision
	collision->AllCollision();

	//	�V�[���؂�ւ�
	gameManager->ChangeScene( SCENE::RESULT );
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

	//	enemy�`��
	enemyManager->Render();

	//	magic�`��
	magicManager->Render();

	//	ui�`��
	uiManager->Render();

	//	�e�v���C���[���W�\��
	DebugRender();

	MyInfoRender();
}

//	debug�p�`��
void	sceneMain::DebugRender( void )
{
	for ( int p = 0; p < PLAYER_MAX; p++ )
	{
		//	�e�v���C���[���W�`��
		PlayerParam	playerParam = gameParam->GetPlayerParam( p );
		int	point = gameParam->GetPointInfo( p ).point;
		Vector3	p_pos = playerParam.pos;
		int	life = playerParam.life;
		char	str[256];
		sprintf_s( str, "%dP pos = Vector3( %.2f, %.2f, %.2f ), score = %d, life = %d",  p + 1, p_pos.x, p_pos.y, p_pos.z, point, life );
		IEX_DrawText( str, 20 , 300 + p * 50, 500, 200, 0xFFFFFF00 );
	}
}

//	�����̏��\��
void	sceneMain::MyInfoRender( void )
{
	//	������ID( Player�ԍ� )
	int	 id = gameParam->GetMyIndex();
	
	//	�����̖��O
	LPSTR name = gameParam->GetPlayerName( id );
	nameManager->SetNameIndex( id, name );

	//	�����̍��W
	Vector3	pos = playerManager->GetPlayer( id )->GetPos();

	//	�o���l
	int	exp = levelManager->GetExp();

	//	�\��
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )\n\nexp : %d", id + 1, name, pos.x, pos.y, pos.z, exp );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}

//	��M���M
void	sceneMain::ThreadFunction( void )
{
	//	�T�[�o�[�������M
	gameParam->Update();
}











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
#include	"ItemManager.h"
#include	"Collision.h"
#include	"Sound.h"

#include	"sceneMain.h"

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

	//	stage������
	stage = new Stage();

	//	player������
	playerManager->Initialize();

	//	enemy������
	enemyManager->Initialize();

	//	magic������
	magicManager->Initialize();

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

	//	item�X�V
	itemManager->Update();

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
	PlayerStatus	playerStatus = gameParam->GetPlayerStatus();

	int atk = playerStatus.power;
	int def = playerStatus.defense;
	int mgcAtk = playerStatus.magicPower;
	int mgcDef = playerStatus.magicDefense;

	char str[256];
	sprintf( str, "power = %d\ndefense = %d\nmagicAttack = %d\nmagicDefense = %d\n", atk, def, mgcAtk, mgcDef );
	IEX_DrawText( str, 20, 300, 500, 500, 0xFFFFFF00 );
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










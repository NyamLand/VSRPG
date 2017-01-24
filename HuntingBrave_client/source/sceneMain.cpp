
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<vector>
#include	<thread>
#include	<map>
#include	<process.h>
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
#include	"NetEnemyManager.h"
#include	"Collision.h"
#include	"Sound.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

bool	sceneMain::threadState;

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

	//	�J����������
	mainView->AngleInit( gameParam->GetMyIndex() );

	//	stage������
	stage = new Stage();

	//	player������
	playerManager->Initialize();

	//	enemy������
	enemyManager->Initialize();

	//	netEnemy������
	netEnemyManager->Initialize();

	//	magic������
	magicManager->Initialize();

	//	ui�̐ݒ�
	uiManager->Initialize();

	//	�퓬BGM
	sound->PlayBGM( BGM::MAIN );

	//	level������
	levelManager->Initialize();

	//	���M
	gameParam->SendResponseInfo( RESPONSE_COMMAND::GAME_START );

	_beginthread( ThreadFunction, 0, nullptr );
	threadState = false;
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	enemyManager->Release();
	netEnemyManager->Release();
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
	//	���M
	gameParam->Send();

	//	�o�ߎ��Ԏ擾
	float elapseTime = GetElapseTime();

	//	GameManager�X�V
	gameManager->Update();

	//	player�X�V
	playerManager->Update();

	//	enemy�X�V
	enemyManager->Update();

	//	netEnemy�X�V
	netEnemyManager->Update();

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
	if ( threadState )
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
	
	//	netEnemy�`��
	netEnemyManager->Render();

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
	LPSTR name = gameParam->GetPlayerName()->GetName( id );
	nameManager->SetNameIndex( id, name );

	//	�����̍��W
	Vector3	pos = playerManager->GetPlayer( id )->GetPos();

	//	���S����̋���
	float			length = Vector3( Vector3( 0.0f, 0.0f, 0.0f ) - pos ).Length();
	//	�o���l
	int	exp = levelManager->GetExp();

	//	�\��
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )\n\nexp : %d\n\nlength : %.2f", id + 1, name, pos.x, pos.y, pos.z, exp, length );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}

//	��M���M
void	sceneMain::ThreadFunction( void* ptr )
{
	//	�T�[�o�[�������M
	for (;;)
	{
		gameParam->Receive();

		if ( gameManager->GetChangeSceneFrag() )	break;
	}

	threadState = true;
	_endthread();
}










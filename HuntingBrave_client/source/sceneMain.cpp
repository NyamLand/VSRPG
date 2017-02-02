
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<vector>
#include	<thread>
#include	<map>
#include	<process.h>
#include	"Screen.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"Image.h"
#include	"DrawShape.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"TimeUpUI.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"EnemyManager.h"
#include	"MagicManager.h"
#include	"EffectManager.h"
#include	"LevelManager.h"
#include	"NameManager.h"
#include	"ItemManager.h"
#include	"PointManager.h"
#include	"NetEnemyManager.h"
#include	"Collision.h"
#include	"Sound.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

#define	BLACK_WHITE_SPEED		0.01f
#define	MAP_SIZE		250
#define	MAP_POS_X		1150
#define	MAP_POS_Y		130
#define	MAP_SRC_SIZE	720

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

	//	level������
	levelManager->Initialize();

	//	Effect������
	effectManager->Initialize();

	//	point������
	pointManager->Initialize();

	//	collision������
	collision->Initialize(gameParam->GetMyIndex(), "DATA/BG/stage_atari.IMO" );

	//	particle������
	particle->Initialize();

	//	���M
	gameParam->SendResponseInfo( RESPONSE_COMMAND::GAME_START );

	//	�퓬BGM
	sound->PlayBGM( BGM::MAIN );

	//	�o�b�N�o�b�t�@�|�C���^�ޔ�
	iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );
	mainScreen = new iex2DObj( iexSystem::ScreenWidth, iexSystem::ScreenHeight, IEX2D_RENDERTARGET );

	screen->SetScreenMode( SCREEN_MODE::FADE_IN, 0.01f );

	blackWhitePercentage = 0.0f;

	_beginthread( ThreadFunction, 0, nullptr );
	threadState = false;

	//	�^�C���A�b�v�p
	timeUp = new TimeUpUI();
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	SafeDelete( mainScreen );
	SafeDelete( timeUp );
	backBuffer->Release();
	enemyManager->Release();
	netEnemyManager->Release();
	uiManager->Release();
	magicManager->Release();
	//playerManager->Release();
	effectManager->Release();
	particle->Release();
	collision->Release();
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
	//if (!threadState){
		gameParam->Send();
	//}

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

	//	Effect�X�V
	effectManager->Update();

	//	camera�X�V
	int index = gameParam->GetMyIndex();
	mainView->Update( playerManager->GetPlayer( index )->GetPos() );

	//	collision
	collision->AllCollision();

	//	particle
	particle->Update();

	//	�X�N���[������
	screen->Update();
	DeadScreen();

	//	�V�[���؂�ւ�
	if ( threadState ){
	//	sound->PlaySE(SE::TIME_END);
	//	if (timeUp->Update() == true && sound->GetSEState(SE::TIME_END) == true)	
		gameManager->ChangeScene(SCENE::RESULT);
	}
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	//	�����_�[�^�[�Q�b�g�ݒ�
	mainScreen->RenderTarget( 0 );

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

	//	effect�`��
	effectManager->Render();

	//	particle�`��
	particle->Render();

	stage->GetTexture()->Render(IMAGE_MODE::NORMAL, MAP_POS_X, MAP_POS_Y, MAP_SIZE, MAP_SIZE,
		280, 0, MAP_SRC_SIZE, MAP_SRC_SIZE);

	//	ui�`��
	uiManager->Render();
	
	screen->Render();

	//	�e�v���C���[���W�\��
	//DebugRender();

	//MyInfoRender();

	timeUp->Render();

	//	�t���[���o�b�t�@�֐؂�ւ�
	iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

	shader2D->SetValue( "percentage", blackWhitePercentage );
	mainScreen->Render( 0, 0, 1280, 720, 0, 0, 1280, 720, shader2D, "blackWhiteOutSet" );
}

//	debug�p�`��
void	sceneMain::DebugRender( void )
{
	PlayerStatus	playerStatus = gameParam->GetPlayerStatus();

	int life = gameParam->GetPlayerParam( gameParam->GetMyIndex() ).life;
	int atk = playerStatus.power;
	int def = playerStatus.defense;
	int mgcAtk = playerStatus.magicPower;
	int mgcDef = playerStatus.magicDefense;

	char str[256];
	sprintf( str, "life = %d\npower = %d\ndefense = %d\nmagicAttack = %d\nmagicDefense = %d\n", life, atk, def, mgcAtk, mgcDef );
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

//	�����`�F�b�N
void	sceneMain::DeadScreen( void )
{
	int index = gameParam->GetMyIndex();
	
	//	�������Ă�����X�L�b�v
	if ( gameParam->GetPlayerParam( index ).motion != MOTION_NUM::DEAD )
	{
		blackWhitePercentage = 0.0f;
		return;
	}

	//	��ԏ���
	bool state = Interpolation::PercentageUpdate( blackWhitePercentage, BLACK_WHITE_SPEED );
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










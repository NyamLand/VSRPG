
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"EnemyManager.h"

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

	//	GameParam������
	gameParam = new GameParam();
	
	//	�J�����ݒ�
	mainView = new Camera();
	mainView->Initialize(
		Camera::VIEW_MODE::TRACKING_VIEW,
		Vector3( 0.0f, 15.0f, -15.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	player�ݒ�
	playerManager->Initialize();

	//	enemy�ݒ�
	enemyManager->Initialize();
	
	//	stage�ݒ�
	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

	baseEquipment = new BaseEquipment("DATA\\player_data.csv");

	//	ui�̐ݒ�
	uiManager->Initialize();

	//	GameManager�̏�����
	gameManager->Initialize();

	//	�e�L�X�g�ǂݍ���
	char addr[64], name[17];
	std::ifstream	ifs( "onlineInfo.txt" );
	ifs >> addr;
	ifs >> name;

	//drawShape->Initialize();

	//	�N���C�A���g������( server�Ɛڑ� )
	bool	serverOK = false;
	for ( int i = 0; i < 100; i++ )
	{
		printf( "�z�X�g������\n" );
		if ( gameParam->InitializeClient( addr, 7000, name ) )
		{
			serverOK = true;
			break;
		}
	}
	if ( !serverOK )
	{
		MessageBox(iexSystem::Window, "�N���C�A���g���������s!", "ERROR!", MB_OK );
		return	false;
	}
	//��
	//baseEquipment = new BaseEquipment();
	
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	SafeDelete( gameParam );
	playerManager->Release();
	enemyManager->Release();
	uiManager->Release();
	

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
	printf( "�o�ߎ��� : %f\n", elapseTime );

	//	�T�[�o�[�������M
	gameParam->Update();

	//	GameManager�X�V
	gameManager->Update();

	//	player�X�V
	playerManager->Update();

	//	enemy�X�V
	enemyManager->Update();

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

	//	enemy�`��
	enemyManager->Render();

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
		Vector3	p_pos = playerParam.pos;
		char	str[256];
		sprintf_s( str, "%dP pos = Vector3( %.2f, %.2f, %.2f )",  p + 1, p_pos.x, p_pos.y, p_pos.z );
		IEX_DrawText( str, 20 , 300 + p * 50, 500, 200, 0xFFFFFF00 );

		//	�����̓X�L�b�v
		if ( gameParam->GetMyIndex() == p )	continue;

		//	���ŋ��̕`��
		if ( gameParam->GetPlayerInfo( p ).active )
		{
			//	���̕`��
			drawShape->DrawSphereMesh( playerParam.pos, 2.0f, 0xFFFFFF00 );
		}
	}
}

//	�����̏��\��
void	sceneMain::MyInfoRender( void )
{
	//	������ID( Player�ԍ� )
	int	 id = gameParam->GetMyIndex();
	
	//	�����̖��O
	LPSTR name = gameParam->GetPlayerName( id );
	
	//	�����̍��W
	Vector3	pos = playerManager->GetPlayer()->GetPos();

	//	�\��
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}








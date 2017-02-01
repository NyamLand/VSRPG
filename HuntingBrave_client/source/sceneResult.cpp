
#include	"iextreme.h"
#include	"system/Scene.h"
#include	"system/Framework.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"Camera.h"
#include	"InputManager.h"
#include	"sceneMatching.h"
#include	"PointManager.h"
#include	"Sound.h"
#include	"sceneTitle.h"
#include	"sceneResult.h"

//***************************************************************
//
//	sceneResult�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	������
	bool	sceneResult::Initialize( void )
	{
		//	���ݒ�
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	���s���ݒ�
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );
		
		//	�J����������
		mainView = new Camera();
		mainView->Initialize( Camera::VIEW_MODE::FIX_VIEW,
			Vector3( 0.0f, 50.0f, 200.0f ),
			Vector3( 0.0f, 3.0f, 300.0f ) );

		//	�摜�ǂݍ���
		back = new iex2DObj( "DATA/UI/BackGround/result_UI.png" );

		testResult = new TestResult();

		//	�T�C���A�E�g
		gameParam->CloseClient();

		//	BGM�Đ�
		sound->PlayBGM( BGM::RESULT );

		pointManager->Sort();

		index = 0;
		viewPos = Vector3( 0.0f, 50.0f, 200.0f );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			playerPos[i] = Vector3( 0.0f, 0.0f, 250.0f );
			obj[i] = new iex3DObj( "DATA/CHR/Suppin/suppin.IEM" );
			obj[i]->SetScale( 0.2f );
			obj[i]->SetPos( 0.0f, 0.0f, 250.0f );
			obj[i]->Update();
		}

		return	true;
	}

	//	���
	sceneResult::~sceneResult( void )
	{
		SafeDelete( mainView );
		SafeDelete( back );
		SafeDelete( gameParam );
		SafeDelete( testResult );
		sound->StopBGM();
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	sceneResult::Update( void )
	{
		//if ( KEY( KEY_RIGHT ) == 1 )	viewPos.x += 10.0f;
		//if ( KEY( KEY_LEFT ) == 1 )		viewPos.x -= 10.0f;
		if ( KEY( KEY_UP ) == 1 )		viewPos.z += 10.0f;
		if ( KEY( KEY_DOWN ) == 1 )	viewPos.z -= 10.0f;

		if ( KEY( KEY_AXISX ) < 0 )		playerPos[index].x -= 1.0f;
		if ( KEY( KEY_AXISX ) > 0 )		playerPos[index].x += 1.0f;
		if ( KEY( KEY_AXISY ) < 0 )		playerPos[index].z += 1.0f;
		if ( KEY( KEY_AXISY ) > 0 )		playerPos[index].z -= 1.0f;

		obj[index]->SetPos( playerPos[index] );
		obj[index]->Update();
		
		mainView->Set( viewPos, Vector3( 0.0f, 3.0f, 300.0f ) );

		if ( KEY( KEY_ENTER ) == 3 )
		{
			index++;
			if ( index >= PLAYER_MAX )	index = 0;	
		}
	}

	//	�`��
	void	sceneResult::Render( void )
	{
		mainView->Activate();
		mainView->Clear();

		//	���U���g�`��
		testResult->Render();

		char str[256];

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int player = pointManager->GetPlayer( i );
			sprintf(str, "%d��	    %dP	   score : %d", i + 1, player + 1, pointManager->GetPoint( player ) );
			IEX_DrawText( str, 600, 300 + i * 50, 200, 200, 0xFFFFFFFF );

			obj[i]->Render();
		}

		//	���W�\��
		sprintf( str, "pos.x = %2f\npos.y = %2f\npos.z = %2f", playerPos[index].x, playerPos[index].y, playerPos[index].z );
		IEX_DrawText( str, 20, 600, 200, 200, 0xFFFFFF00 );

		sprintf( str, "viewPos.x = %2f\nviewPos.y = %2f\nviewPos.z = %2f", viewPos.x, viewPos.y, viewPos.z );
		IEX_DrawText( str, 20, 200, 200, 200, 0xFFFFFF00 );
	}

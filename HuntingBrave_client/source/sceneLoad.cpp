
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/Scene.h"
#include	"system/System.h"
#include	<process.h>
#include	"GlobalFunction.h"
#include	"Camera.h"
#include	"sceneMain.h"
#include	"sceneMatching.h"
#include	"sceneResult.h"
#include	"sceneTitle.h"
#include	"sceneLoad.h"

//***************************************************************
//
//	sceneLoad�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

bool	sceneLoad::threadState;

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	������
	sceneLoad::sceneLoad( Scene* nextScene ) : newScene( nextScene )
	{
		threadState = false;
	}

	//	������
	bool	sceneLoad::Initialize( void )
	{
		//	���ݒ�
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	���C�g�ݒ�
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	�J����������
		view = new iexView();

		//	waitLoad������
		waitLoad = new WaitLoad();

		//	��thread�쐬
		_beginthread( Thread, 0, ( void* )newScene );

		return	true;
	}

	//	���
	sceneLoad::~sceneLoad( void )
	{
		SafeDelete( view );
		SafeDelete( waitLoad );
	}

//----------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------

	//	�X�V
	void	sceneLoad::Update( void )
	{
		//	���[�h���o
		waitLoad->Update();

		if ( threadState )
		{
			MainFrame->ChangeScene( newScene, false );
			return;
		}
	}

	//	�`��
	void	sceneLoad::Render( void )
	{
		view->Activate();
		view->Clear();

		//	���[�h���o
		waitLoad->Render();
	}

//----------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------

	//	�X���b�h����
	void	sceneLoad::Thread( void* arg )
	{
		//	���񂳂��鏈��
		Scene*	scene = ( Scene* )arg;
		scene->Initialize();

		//	�X���b�h�I��
		threadState = true;
		_endthread();
	}

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------


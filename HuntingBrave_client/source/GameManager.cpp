
#include	"iextreme.h"

#include	"GlobalFunction.h"
#include	"system/Framework.h"
#include	"sceneMatching.h"
#include	"sceneMain.h"
#include	"sceneResult.h"
#include	"sceneTitle.h"
#include	"GameManager.h"

//***************************************************************
//
//	GameManager�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameManager::GameManager( void ) : timer(0), isComplete( false ), changeSceneFrag( false )
	{
		scene = SCENE::MATCHING;
	}

	//	�f�X�g���N�^
	GameManager::~GameManager( void )
	{

	}

	//	������
	bool	GameManager::Initialize( void )
	{
		return	true;
	}

	//	���
	void	GameManager::Release( void )
	{

	}

	//	�N���C�A���g������
	void	GameManager::InitializeClient( void )
	{
		////	WinSock������
		//WSADATA	wsaData;
		//WSAStartup( MAKEWORD( 1, 1 ), &wsaData );
	}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

	//	�X�V
	void	GameManager::Update( void )
	{
		
	}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

	//	�V�[���؂�ւ�
	void	GameManager::ChangeScene( char nextScene )
	{
		if ( !changeSceneFrag )	return;

		//	�V�[���؂�ւ�
		switch ( nextScene )
		{
		case SCENE::TITLE:
			MainFrame->ChangeScene( new sceneTitle() );
			break;

		case SCENE::MATCHING:
			MainFrame->ChangeScene( new sceneMatching() );
			break;

		case SCENE::MAIN:
			MainFrame->ChangeScene( new sceneMain() );
			break;

		case SCENE::RESULT:
			MainFrame->ChangeScene( new sceneResult() );
			break;
		}

		changeSceneFrag = false;
	}

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------


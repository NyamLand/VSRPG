
#include	"iextreme.h"
#include	<vector>
#include	<memory>
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
	GameManager::GameManager( void ) : 
		timer( 0 ),
		isComplete( false ), changeSceneFrag( false ), gameState( false )
	{
		//	�t�H���g�ǉ�
		AddFontResourceEx( "DATA/font001.TTF", FR_PRIVATE, NULL );

		scene = SCENE::MATCHING;

		//	CSV�ǂݍ���
		LoadData();
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

	//	CSV�ǂݍ���
	bool	GameManager::LoadData( void )
	{
		//	CSV�t�@�C��
		fstream playerStream( "DATA/player_data.csv" );

		//	CSV���[�_�[������
		std::unique_ptr<CSVReader>	reader = 
			std::make_unique<CSVReader>( playerStream );

		//	�t�@�C������ǂݍ��݁Avector�z��ɕۑ�����
		int index = 0;
		while (1)
		{
			playerData.resize( index + 1 );
			reader->Read( playerData[index] );
			if ( playerData[index].size() == 0 )	break;
			index++;
		}
		return	true;
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

	//	�A�b�v�O���[�h�f�[�^�擾
	int	GameManager::GetUpGrade( char type, char param, char level )
	{
		return	std::stoi( playerData[1 + ( type * 5 )+ level][param] );
	}

	//	�t���[�o�[�e�L�X�g�擾
	char*	GameManager::GetFlavorText( char type, char level )
	{
		//	��s�ڂ͐����Ȃ̂ŃX�L�b�v
		string str = playerData[1 + ( type * 6 ) + level][UPGRADE_DATA::TEXT];
		int length = str.length();
		char*	ret = new char[length + 1];
		memcpy( ret, str.c_str(), length + 1 );
		return	ret;
	}

#include	"iextreme.h"
#include	"FrameWork.h"
#include	"GameParam.h"
#include	"sceneMain.h"
#include	"sceneMatching.h"
#include	"GameManager.h"

//*****************************************************************************************************************************
//
//		�Q�[���f�[�^�Ǘ�
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	TIME_MAX	( 1.0f * MINUTE )
#define	INIT_LIFE		7

//	����
GameManager*	gameManager = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameManager::GameManager( void ) : timer( nullptr ),
		timeUp( false ), gameState( true )
	{
		//	�������W�ݒ�
		int initMotion = 0;
		initPlayerParam[0].Set( Vector3( 0.0f, 0.0f, 15.0f ), D3DX_PI, initMotion, 0 );
		initPlayerParam[1].Set( Vector3( 15.0f, 0.0f, 0.0f ), D3DX_PI * 1.5f, initMotion, 0 );
		initPlayerParam[2].Set( Vector3( 0.0f, 0.0f, -15.0f ), 0.0f, initMotion, 0 );
		initPlayerParam[3].Set( Vector3( -15.0f, 0.0f, 0.0f ), D3DX_PI * 0.5f, initMotion, 0 );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			matchingInfo[i].isComplete = false;
		}

		//	�^�C�}�[������
		timer = new Timer();
		timer->Start( TIME_MAX );
	}

	//	�f�X�g���N�^
	GameManager::~GameManager( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}

	//	�}�b�`���O��񏉊���
	void	GameManager::MatchingInfoInitialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			matchingInfo[p].isComplete = false;
		}
	}

//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	GameManager::Update( void )
	{
		//	�^�C�}�[�X�V
		if ( gameState )
			timeUp = timer->Update();
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�v���C���[�`�F�b�N
	bool	GameManager::PlayerCheck( void )
	{
		bool	ret = false;
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( !gameParam->GetPlayerActive( p ) )	continue;
			ret = matchingInfo[p].isComplete;
		}

		return	ret;
	}

	//	�V�[���؂�ւ�
	void	GameManager::ChangeScene( char& out, char nextScene )
	{
		//	�V�[���ݒ�
		out = nextScene;
		Response	response( RESPONSE_COMMAND::CHANGE_SCENE );
		
		//	���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&response, sizeof( response ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	�������W�擾
	PlayerParam	GameManager::GetInitInfo( int id )const
	{
		return	initPlayerParam[id];
	}

	//	�^�C�}�[�擾
	Timer*&	GameManager::GetTimer( void )
	{
		return	timer;
	}

	//	�}�b�`���O���擾
	MatchingInfo&	GameManager::GetMatchingInfo( int id )
	{
		return	matchingInfo[id];
	}

	//	�^�C���A�b�v�擾
	bool	GameManager::GetTimeUp( void )
	{
		return	timeUp;
	}

	//	�Q�[����Ԏ擾
	bool	GameManager::GetGameState( void )
	{
		return	gameState;

	}



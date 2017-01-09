
#include	"iextreme.h"
#include	<vector>
#include	<memory>
#include	"FrameWork.h"
#include	"GameParam.h"
#include	"sceneMain.h"
#include	"sceneMatching.h"
#include	"CSVReader.h"
#include	"GameManager.h"

//*****************************************************************************************************************************
//
//		�Q�[���f�[�^�Ǘ�
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	TIME_MAX	( 5 )
#define	INIT_LIFE		5

//	����
GameManager*	gameManager = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameManager::GameManager( void ) : timer( nullptr ),
		timeUp( false ), gameState( false )
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
		playerData.clear();

		//	csv�ǂݍ���
		LoadData();
	}

	//	�f�X�g���N�^
	GameManager::~GameManager( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}

		playerData.clear();
	}

	//	�}�b�`���O��񏉊���
	void	GameManager::MatchingInfoInitialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			matchingInfo[p].isComplete = false;
		}
	}

	//	CSV�ǂݍ���
	void	GameManager::LoadData( void )
	{
		//	CSV�t�@�C��
		fstream playerStream( "DATA/player_data.csv" );

		//	CSV���[�_�[������
		std::unique_ptr<CSVReader>	reader =
			std::make_unique<CSVReader>( playerStream );

		//	�t�@�C������ǂݍ��݁Avector�z��ɕۑ�����
		int index = 0;
		while ( 1 )
		{
			playerData.resize( index + 1 );
			reader->Read( playerData[index] );
			if ( playerData[index].size() == 0 )	break;
			index++;
		}
	}

	//	������
	bool	GameManager::Initialize( void )
	{
		//	���
		Release();

		//	�}�b�`���O��񏉊���
		MatchingInfoInitialize();
		if ( timer == nullptr )	
			timer = new Timer();

		return	true;
	}

	//	���
	void	GameManager::Release( void )
	{
		if ( timer != nullptr )
		{
			delete	timer;
			timer = nullptr;
		}

		gameState = false;
		timeUp = false;
	}

	//	�v���C���[�X�e�[�^�X������
	void	GameManager::InitializeStatus( PlayerStatus& playerStatus )
	{
		int power = GetUpGrade( 0, UPGRADE_DATA::ATTACK, 0 );
		int defense = GetUpGrade( 0, UPGRADE_DATA::DEFENSE, 0 );
		int magicAttack = GetUpGrade( 0, UPGRADE_DATA::MAGIC_ATTACK , 0 );
		int magicDefense = GetUpGrade( 0, UPGRADE_DATA::MAGIC_DIFENSE, 0 );
		float speed = GetUpGradeSpeed( 0, 0 );

		playerStatus.Initialize( power, defense, magicAttack, magicDefense, speed );
	}

//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	GameManager::Update( void )
	{
		//	�^�C�}�[�X�V
		if ( gameState )
		{
			if ( timer != nullptr )		timeUp = timer->Update();
		}
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

	//	�Q�[����Ԑݒ�
	void	GameManager::SetGameState( bool state )
	{
		gameState = state;
	}

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

	//	�A�b�v�O���[�h�f�[�^�擾
	int	GameManager::GetUpGrade( char levelType, char upGradeData, char level )
	{
		return	std::stoi( playerData[1 + ( levelType * 5 ) + level][upGradeData] );
	}

	//	�X�s�[�h�A�b�v�O���[�h�f�[�^�擾
	float	GameManager::GetUpGradeSpeed( char levelType, char level )
	{
		return	std::stof( playerData[1 + ( levelType * 5 ) + level][UPGRADE_DATA::SPEED] );
	}



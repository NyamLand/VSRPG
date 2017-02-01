
#pragma once

//****************************************************************
//
//	GameData
//
//****************************************************************

//	include
#include	<time.h>
#include	"iextreme.h"
#include	"SendData.h"
#include	"ReceiveData.h"

//-------------------------------------------------------------------------------------
//	�Q�[�����
//-------------------------------------------------------------------------------------

//	����
#define	MINUTE		60
#define	HOUR		MINUTE * 60
#define	GRAVITY	-0.1f

//	�V�[��
namespace SCENE
{
	enum
	{
		TITLE,
		MATCHING,
		MAIN,
		RESULT,
		MAX
	};

}

//-------------------------------------------------------------------------------------
//	�v���C���[���
//-------------------------------------------------------------------------------------

#define	PLAYER_MAX		4

	//	�v���C���[��{���
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
		int frontTitle;
		int backTitle;
		PlayerInfo( void ){};
		PlayerInfo( bool active, const LPSTR& name, int frontTitle, int backTitle );
		void Set( bool active, const LPSTR& name, int frontTitle, int backTitle );
	};

	//	�v���C���[�p�����[�^
	struct PlayerParam
	{
		Vector3	pos;
		Vector3	move;
		char			charType;
		float			angle;
		float			cameraAngle;
		float			effParam;
		int			motion;
		int			frame;
		PlayerParam( void ){}
		PlayerParam( const Vector3& pos, float angle, float cameraAngle, float effParam, int motion, int frame );
		void Set( const Vector3& pos, float angle, float cameraAngle, float effParam, int motion, int frame );
	};

	//	�v���C���[�X�e�[�^�X
	struct PlayerStatus
	{
		//	parameter
		int	power, savePower;
		int	defense, saveDefense;
		int	magicAttack, saveMagicAttack;
		int	magicDefense, saveMagicDefense;
		int	maxLife;
		float	speed, saveSpeed;

		//	�v�Z
		void	Initialize( int power, int defense, int magicAttack, int magicDefense, int maxLife, float speed );
		void	CulcPower( int power );
		void	CulcDefense( int defense );
		void	CulcMagicAttack( int power );
		void	CulcMagicDefense( int defense );
		void	CulcMaxLife( int maxLife );
		void	DoubleSpeed( float param );
	};

	//	�_���A���ʏ��
	struct PointInfo
	{
		//	�ϐ�
		int		point;
		int		addPoint;
	};

	//	�}�b�`���O���
	struct MatchingInfo
	{
		bool		isComplete;
	};

	//	�f�[�^�\��
	enum
	{
		COMMAND,
		ID,
		DATA,
	};

//*****************************************************************************************************************************
//	�l�b�g�f�[�^
//*****************************************************************************************************************************
	
	//	�R�}���h
	namespace
	{
		//	�T�C���R�}���h
		namespace COMMANDS
		{
			enum
			{
				MATCHING = 12,
				SIGN_UP,
				SIGN_OUT,
				RESPONSE,
				DEBUG
			};
		}

		//	�ԓ��R�}���h
		namespace RESPONSE_COMMAND
		{
			enum
			{
				SIGN_UP,
				GAME_START,
				CHANGE_SCENE,
				KILL_INFO,
				HIT_SE_TYPE
			};
		}
	}

	//	�V�K�Q�����
	struct SignUp
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		int		name[4];
		int		frontTitle;
		int		backTitle;
		SignUp( void ){}
		SignUp( int id, int* name, int frontTitle, int backTitle );
		void Set( int id, int* name, int frontTitle, int backTitle );
	};

	//	�E�ޏ��
	struct SignOut
	{
		char  com = COMMANDS::SIGN_OUT;
		int	  id;
		SignOut( void ){}
		SignOut( int id ){ this->id = id; }
	};

	//	����
	struct Response
	{
		char com = COMMANDS::RESPONSE;
		char	responseCom;
		Response( char responseCom ) : responseCom( responseCom ){}
	};

	//	�}�b�`���O���
	struct Matching
	{
		char com = COMMANDS::MATCHING;
		int	id;
		bool	isComplete;
		Matching( void );
		Matching( int id, bool mode );
		void	Set( int id, bool mode );
	};

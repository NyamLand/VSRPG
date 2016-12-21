
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
		PlayerInfo( void ){};
		PlayerInfo( bool active, const LPSTR& name );
		void Set( bool active, const LPSTR& name );
	};

	//	�v���C���[�p�����[�^
	struct PlayerParam
	{
		Vector3	pos;
		float			angle;
		int			motion;
		int			frame;
		PlayerParam( void ){}
		PlayerParam( const Vector3& pos, float angle, int motion, int frame );
		void Set( const Vector3& pos, float angle, int motion, int frame );
	};

	//	�v���C���[�X�e�[�^�X
	struct PlayerStatus
	{
		//	parameter
		int	power;
		int	defense;
		float	speed;
		float initSpeed;

		//	�v�Z
		void	Initialize( int power, int defense, float speed );
		void	CulcPower( int id, int power );
		void	CulcDefense( int id, int defense );
		void	DoubleSpeed( int id, float param );
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
				MATCHING = 10,
				SIGN_UP,
				SIGN_OUT,
				RESPONSE
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
			};
		}
	}

	//	�V�K�Q�����
	struct SignUp
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
		SignUp( void ){}
		SignUp( int id, const LPSTR& name );
		void Set( int id, const LPSTR& name );
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
		Matching( int id, int mode );
		void	Set( int id, int mode );
	};

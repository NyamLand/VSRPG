
#pragma once

//****************************************************************
//
//	GameData
//
//****************************************************************

//	include
#include	<time.h>
#include	"iextreme.h"

//-------------------------------------------------------------------------------------
//	�Q�[�����
//-------------------------------------------------------------------------------------

//	����
#define	MINUTE		60
#define	HOUR		MINUTE * 60

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
		Vector3 pos;
		float	moveX, moveZ;
		float	angle;
		int		motion;
		PlayerParam( void ){}
		PlayerParam( const Vector3& pos, float moveX, float moveZ, float angle, int motion );
		void Set( const Vector3& pos, float moveX, float moveZ, float angle, int motion );
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
	enum COMMANDS
	{
		NO_COMMAND = -1,
		CHARA_INFO,
		CHAR_MOVE,
		CHARA_RECEIVEDATA,
		GAME_INFO,
		SIGN_UP = 10,
		SIGN_OUT,
		CONTROLLE_AXIS,
	};

	//	�V�K�Q�����
	struct NET_IN
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
		NET_IN( void ){}
		NET_IN( int id, const LPSTR& name );
		void Set( int id, const LPSTR& name );
	};

	//	�Q�[�����
	struct NET_GAME
	{
		char com = GAME_INFO;
		int		limitTimer;
		NET_GAME( void ){};
		NET_GAME( int timer ){ limitTimer = timer; }
	};

	//	�L�����f�[�^
	struct NET_CHARA
	{
		char com = COMMANDS::CHARA_INFO;
		int		id;
		Vector3	pos;
		float		angle;
		int			motion;
		NET_CHARA( void ){}
		NET_CHARA( int id, const Vector3& pos, float angle, int motion );
		void	Set( int id, const Vector3& pos, float angle, int motion );
	};

	//	�ړ����
	struct NET_MOVE
	{
		char com = COMMANDS::CHAR_MOVE;
		int		id;
		float	axisX, axisY;
		NET_MOVE( void ){};
		NET_MOVE( int id, float axisX, float axisY );
		void	Set(int id, float axisX, float axisY );
	};

	//	����f�[�^�̉�
	struct NET_CHAR_RECEIVEDATA
	{
		char com = COMMANDS::CHARA_RECEIVEDATA;
		int		id;
		float	axisX, axisY;
		float	angle;
		NET_CHAR_RECEIVEDATA(void){}
		NET_CHAR_RECEIVEDATA(int id, const float& axisX, const float& axisY, const float& angle);
		void	Set(int id, const float& axisX, const float& axisY, float& angle);
	};

//***************************����g�����������******************
	//	�L�����ړ��f�[�^
	struct NET_CHARA_MOVE
	{
		char com = COMMANDS::CHAR_MOVE;
		int		id;
		Vector3	move;
		NET_CHARA_MOVE(void){}
		NET_CHARA_MOVE(int id, const Vector3& move);
		void	Set(int id, const Vector3& move);
	};

	//	�R���g���[���[�����
	struct NET_CONTROLLE_AXIS
	{
		char com = COMMANDS::CONTROLLE_AXIS;
		int		id;
		float axisX,axisY;
		NET_CONTROLLE_AXIS(void){}
		NET_CONTROLLE_AXIS(int id, const float& axisX, const float& axisY);
		void	Set(int id, const float& axisX, const float& axisY);
	};

//****************************************************************

	//	�E�ޏ��
	struct NET_OUT
	{
		char  com = COMMANDS::SIGN_OUT;
		int	  id;
		NET_OUT( void ){}
		NET_OUT( int id ){ this->id; }
	};
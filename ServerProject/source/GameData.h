
#pragma once

//***************************************************************
//
//	GameData�N���X
//
//***************************************************************

//	include
#include	"iextreme.h"

//-------------------------------------------------------------------------------------
//	�萔
//-------------------------------------------------------------------------------------
#define	PLAYER_MAX	4		//	�v���C���[�ő吔
#define	PORT_NUM	9000	//	�|�[�g�ԍ�

//-------------------------------------------------------------------------------------
//	�v���C���[�f�[�^
//-------------------------------------------------------------------------------------

	//	�v���C���[��{���
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
		int		type;
	};

	//	�v���C���[�p�����[�^
	struct PlayerParam
	{
		Vector3	pos;
		float		angle;
		int			motion;

		Vector3	move;
	};

//-------------------------------------------------------------------------------------
//	�l�b�g���
//-------------------------------------------------------------------------------------

	//	����萔
	enum DATA_MODE
	{
		MOVE,
		POS,
		CHAT,
		SIGN_UP = 10,
		SIGN_OUT = 11,
		DATA_MAX
	};

	//	��{���
	struct NET_INFO
	{
		char com;
		int		id;
		int		type;
		char	name[17];
	};

	//	�`���b�g���
	struct NET_CHAT
	{
		char  com;
		int	  id;
		char  msg[50];
	} ;

	//	�ގ����
	struct NET_OUT
	{
		char	com;
		int		id;
	};

	//	�ړ����
	struct NET_MOVE
	{
		char  com;
		float vx;
		float vz;
	};

	//	�ʒu���
	struct NET_POS
	{
		char com;
		int id;
		Vector3	pos;
	};

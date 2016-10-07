
#pragma once

//***************************************************************
//
//	GameData
//
//***************************************************************

//	include
#include	"iextreme.h"

//----------------------------------------------------------------------------
//	�萔
//----------------------------------------------------------------------------

#define	PLAYER_MAX	4			//	�v���C���[�l��
#define	PORT_NUM	9000		//	�|�[�g�ԍ�

//----------------------------------------------------------------------------
//	�v���C���[���
//----------------------------------------------------------------------------

	//	�v���C���[��{���
	struct PlayerInfo
	{
		bool	active;
		int		type;
		char	name[17];
	};

	//	�v���C���[�p�����[�^
	struct PlayerParam
	{
		Vector3	pos;
		float		angle;
		int			motion;
	};

	//	�`���b�g�p�����[�^
	struct ChatParam
	{
		char	msg[50];
		int		count;
	};

//----------------------------------------------------------------------------
//	�f�[�^����M�p�\����
//----------------------------------------------------------------------------

	enum RECEIVE_MODE
	{
		MOVE,
		POS,
		CHAT,
		SIGN_UP = 10,
		SIGN_OUT = 11,
	};

	//	�V�K�Q�����
	struct NET_INFO
	{
		char	com;
		int		id;
		int		type;
		char	name[17];
	};

	//	�E�ޏ��
	struct NET_OUT
	{
		char	com;
		int		id;
	};

	//	�`���b�g���
	struct NET_CHAT
	{
		char	com;
		int		id;
		char	msg[50];
	};

	//	�ʒu���
	struct NET_POS
	{
		char com;
		Vector3	pos;
	};

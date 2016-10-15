
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

	//	�f�[�^���
	enum DATA_INFO
	{
		COMMAND,
		ID,
		DATA
	};
	
	//	�v���C���[��{���
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
	};

	//	�v���C���[�p�����[�^
	struct PlayerParam
	{
		Vector3	pos;
		float		angle;
	};

//----------------------------------------------------------------------------
//	�f�[�^����M�p�\����
//----------------------------------------------------------------------------

	//	�R�}���h���
	enum COMMANDS
	{
		NO_COMMAND = -1,
		CHARA_INFO,
		SIGN_UP = 10,
		SIGN_OUT,
	};

	//	�L�������
	struct NET_CHARA
	{
		char	com = COMMANDS::CHARA_INFO;
		int		id;
		float	angle;
		Vector3	pos;

		//	���W�ݒ�
		void	SetPos( const Vector3& pos )
		{
			this->pos = pos;
		}

		//	���W�擾
		Vector3	GetPos( void )const
		{
			return	pos;
		}

	};

	//	�T�C���A�E�g
	struct NET_OUT
	{
		char	com = COMMANDS::SIGN_OUT;
		int		id;
	};

	//	�T�C���C��
	struct NET_IN
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
	};
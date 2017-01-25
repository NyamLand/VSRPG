
#pragma once

//***************************************************************
//
//	Player�N���X
//
//***************************************************************

struct Status
{
	float	hp;
	float	atk;
	float	dif;
	float	mat;
	float	mdf;
	float	speed;
};

//	include
#include	"BaseChara.h"
#include	"BaseEquipment.h"
#include	"GameData.h"

namespace
{
	//	���[�V�����Ǘ�
	namespace MOTION_NUM
	{
		//	���[�V�����ԍ�
		enum
		{
			POSUTURE,						//	�ҋ@
			RUN_START,						//	����o��
			RUN,									//	����
			ATTACK1,							//	�U���P
			ATTACK2,							//	�U���Q
			STEP,								//	�X�e�b�v
			MAGIC_CHANT_START,		//	�r���J�n
			MAGIC_CHANT,					//	�r����
			MAGIC_ACTUATION,			//	���@����
			KNOCKBACK1,					//	������P
			KNOCKBACK2,					//	������Q
			FALL,									//	�|���
			DEAD,								//	���S
			EAT,									//	�H�ׂ�
			MENU_OPEN,						//	���j���[���J��
			MENU,								//	���j���[���쒆
			LEVEL_UP,							//	���x���A�b�v
			MENU_CLOSE,					//	���j���[�����
			WIN,									//	����
			WIN_KEEP,						//	�����L�[�v
			CRY									//	����
		};
	}
}

//	class
class Player : public BaseChara
{
protected:
	//	�p�����[�^
	int	id;
	PlayerParam		playerParam;
	iex3DObj* org;
	iex3DObj* nextObj;
	char	fileName[256];
	enum	MODE//	��
	{
		MOVE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		MODE_MAX
	};

public:
	//	�������E���
	Player( void );
	~Player( void );
	virtual	bool	Initialize( int id );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	����֐�
	void	SetAttackShape( void );
	virtual	void	ChangeTexture( int colorNum ) = 0;
	void	PlaySE(int motion);

	//	���ݒ�
	void	SetPlayerParam( const PlayerParam& playerParam );
	void	SetCollisionShape( const PlayerParam& playerParam );
	void	SetMotion(int motion) override;

};

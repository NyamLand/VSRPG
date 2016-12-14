
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

//struct Equipments
//{
//	BaseEquipment*	atk;
//	BaseEquipment*	mat;
//	BaseEquipment*
//
//};


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
private:
	//	�p�����[�^
	int	id;
	PlayerParam		playerParam;
	iex3DObj* org;

	enum	MODE//	��
	{
		MOVE,
		//POSTURE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		MODE_MAX
	};

public:
	//	�������E���
	Player( void );
	~Player( void );
	bool	Initialize( int id );
	
	//	�X�V�E�`��
	void	Update( PlayerParam& playerParam );
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	����֐�
	bool		Move( void );
	void		SetAttackShape( void );
	void		ChangeTexture( int colorNum );

	//	���ݒ�
	void	SetPlayerParam( const PlayerParam& playerParam );
	void	SetModel( void );
};

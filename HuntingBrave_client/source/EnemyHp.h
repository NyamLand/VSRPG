
#pragma once

//***************************************************************
//
//	ENEMYHpUI�N���X
//
//***************************************************************
#include	"Singleton.h"

namespace
{
	namespace HP_MAX
	{
		enum
		{
			WIDTH = 768,				//	�摜����
			HEIGHT =128,				//	�摜�c��
		};

	}

	namespace HPUI_TYPE
	{
		enum
		{
			PLAYER,
			ENEMY,
		};
	}
}

//	class
class EnemyHpUI
{
private:
	iex2DObj* hpFrame_obj;
	iex2DObj* hp_obj;
	int mode_type;
	float	width, height;
	float	hp;
	float maxHp;

public:
	//	�������E���
	EnemyHpUI( void );
	~EnemyHpUI(void);
	void Initilaize(int type, float maxhp);

	//	�X�V�E�`��
	void	Update( void );
	void	Render(float hp, Vector3 pos, Vector3 up);
};


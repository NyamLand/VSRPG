
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
	int	width, height;
	int hp;
	int mode_type;
	int maxHp;

public:
	//	�������E���
	EnemyHpUI( void );
	~EnemyHpUI(void);
	void Initilaize(int type, int maxhp);

	//	�X�V�E�`��
	void	Update( void );
	void	Render(int hp, Vector3 pos, Vector3 up);
};


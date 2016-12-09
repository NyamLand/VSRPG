
#pragma once

//***************************************************************
//
//	ENEMYHpUI�N���X
//
//***************************************************************
#include	"Singleton.h"

namespace
{
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
	int	id;
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
	void	Render(float hp, const Vector3& pos, const Vector3& up);

	void	SetId(int id);
};


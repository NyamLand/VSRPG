

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "CSVReader.h"

namespace TYPE
{
	enum
	{
		ATTACK,
		MAGIC_ATTACK,
		DEFFENCE,
		MAGIC_DEFFENCE,
		SPEED,
		BOOST,
	};
}

using namespace std;
class BaseEquipment		//�v���C���[�̑����i
{
private:
	CSVReader *csv;		//�G�N�Z���ǂݍ��ݗp
protected:
	int			type;		//�����̎��
	string		name;
	int			def;		//�h��
	int			atk;		//�U��
	int			mat;		//���@�U��
	int			mdf;		//���@�h��
	int			hp;			//�̗͑�����
	float		spe;		//�X�s�[�h(�{���v�Z�̂���float)
	string		text;		//�t���[�o�[�e�L�X�g

	bool		extra;		//����\�͂������true,�������false

public:
	BaseEquipment();
	BaseEquipment(char* fileneme);
	virtual ~BaseEquipment();

	void Initialize();
	
	void	LoadData();

	void	Update();
	void	ExEffect();
};
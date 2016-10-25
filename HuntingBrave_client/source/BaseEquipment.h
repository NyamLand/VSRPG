

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "CSVReader.h"

using namespace std;
class BaseEquipment		//�v���C���[�̑����i
{
private:
protected:
	string		name;
	int			hp;			//�̗͑�����
	int			atk;		//�U��
	int			mat;		//���@�U��
	int			def;		//�h��
	int			mdf;		//���@�h��
	float		spe;		//�X�s�[�h(�{���v�Z�̂���float)
	bool		extra;		//����\�͂������true,�������false
	string		text;		//�t���[�o�[�e�L�X�g

	//�t�@�C���ǂݍ��ݗp
	static		CSVReader *csv;

public:
	BaseEquipment();
	virtual ~BaseEquipment();

	void Initialize();
	
	void	LoadData();

	void	Update();
	void	ExEffect();
};

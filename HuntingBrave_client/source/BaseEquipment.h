

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
class BaseEquipment		//プレイヤーの装備品
{
private:
	CSVReader *csv;		//エクセル読み込み用
protected:
	int			type;		//装備の種類
	string		name;
	int			def;		//防御
	int			atk;		//攻撃
	int			mat;		//魔法攻撃
	int			mdf;		//魔法防御
	int			hp;			//体力増加量
	float		spe;		//スピード(倍率計算のためfloat)
	string		text;		//フレーバーテキスト

	bool		extra;		//特殊能力があればtrue,無ければfalse

public:
	BaseEquipment();
	BaseEquipment(char* fileneme);
	virtual ~BaseEquipment();

	void Initialize();
	
	void	LoadData();

	void	Update();
	void	ExEffect();
};
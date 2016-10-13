

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "CSVReader.h"

using namespace std;
class BaseEquipment		//プレイヤーの装備品
{
private:
protected:
	string		name;
	int			hp;			//体力増加量
	int			atk;		//攻撃
	int			mat;		//魔法攻撃
	int			def;		//防御
	int			mdf;		//魔法防御
	float		spe;		//スピード(倍率計算のためfloat)
	bool		extra;		//特殊能力があればtrue,無ければfalse
	string		text;		//フレーバーテキスト

	//ファイル読み込み用
	static		CSVReader *csv;

public:
	BaseEquipment();
	virtual ~BaseEquipment();

	void Initialize();
	
	void	LoadData();

	void	Update();
	void	ExEffect();
};

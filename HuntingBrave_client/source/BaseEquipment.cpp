
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"BaseEquipment.h"
#include	"GameData.h"

//***************************************************************
//
//	BaseEquipmentクラス　　
//
//***************************************************************

//	定数値

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

//	コンストラクタ
//BaseEquipment::BaseEquipment(void) :type(NULL), name(""), 
//hp(0), atk(0), mat(0), def(0), mdf(0), spe(0),
//extra(false)
//{
//	name = "アイアンシールド";
//	LoadData();
//
//}

BaseEquipment::BaseEquipment(char* filename) :type(NULL), name(""),
hp(0), atk(0), mat(0), def(0), mdf(0), spe(0),
extra(false)
{
	fstream r(filename, ios::in);

	csv = new CSVReader(r);

	vector<string> tokens;

	bool flag = false;
	while (!csv->Read(tokens))
	{
		//初期値の次の行から読み込む
		if (tokens[0] == "初期値")
		{
			flag = true;
			continue;
		}

		if (flag == false) continue;
		equipmentData.Set(tokens);
	}
	csv->Close();
}

//	デストラクタ
BaseEquipment::~BaseEquipment(void)
{
	SafeDelete(csv);
}

void	BaseEquipment::Initialize()
{

}

//**********************************************この機能は後々マネージャーに移植する*************************************************
void	BaseEquipment::LoadData()
{


	//CSVReader csv(r);
	//vector<string> tokens;
	//while (!csv.Read(tokens))
	//{
	//	for (unsigned int i = 0; i<tokens.size(); i++)
	//	{
	//		if (tokens[0] == "HP")
	//		{
	//			hp = std::atoi(tokens[1].c_str());
	//		}
	//	}
	//}
	//csv.Close();
	//return 0;
}
//*******************************************************************************************************************************

//	解放

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

//	更新
void	BaseEquipment::Update(void)
{

}


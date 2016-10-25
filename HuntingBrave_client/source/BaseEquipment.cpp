
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"BaseEquipment.h"

//***************************************************************
//
//	BaseEquipmentクラス　　
//
//***************************************************************

//	定数値

CSVReader *BaseEquipment::csv = NULL;
//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

//	コンストラクタ
BaseEquipment::BaseEquipment(void) : name(""), 
hp(0), atk(0), mat(0), def(0), mdf(0), spe(0),
extra(false)
{
	name = "アイアンシールド";
	LoadData();

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
	fstream r("DATA\\player_data.csv", ios::in);

	csv = new CSVReader(r);

	vector<string> tokens;
	
	while (!csv->Read(tokens))
	{
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[0] == name)
			{
				atk = atoi(tokens[1].c_str());
				def = atoi(tokens[2].c_str());
				mat = atoi(tokens[3].c_str());
				mdf = atoi(tokens[4].c_str());
				hp = atoi(tokens[5].c_str());
				spe = atoi(tokens[6].c_str());
				text = tokens[7].c_str();
			}
		}
	}
	csv->Close();

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


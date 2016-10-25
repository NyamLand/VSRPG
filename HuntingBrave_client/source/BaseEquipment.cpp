
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"BaseEquipment.h"

//***************************************************************
//
//	BaseEquipment�N���X�@�@
//
//***************************************************************

//	�萔�l

CSVReader *BaseEquipment::csv = NULL;
//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

//	�R���X�g���N�^
BaseEquipment::BaseEquipment(void) : name(""), 
hp(0), atk(0), mat(0), def(0), mdf(0), spe(0),
extra(false)
{
	name = "�A�C�A���V�[���h";
	LoadData();

}

//	�f�X�g���N�^
BaseEquipment::~BaseEquipment(void)
{
	SafeDelete(csv);
}

void	BaseEquipment::Initialize()
{

}

//**********************************************���̋@�\�͌�X�}�l�[�W���[�ɈڐA����*************************************************
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

//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

//	�X�V
void	BaseEquipment::Update(void)
{

}


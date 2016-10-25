
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"BaseEquipment.h"
#include	"GameData.h"

//***************************************************************
//
//	BaseEquipment�N���X�@�@
//
//***************************************************************

//	�萔�l

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

//	�R���X�g���N�^
//BaseEquipment::BaseEquipment(void) :type(NULL), name(""), 
//hp(0), atk(0), mat(0), def(0), mdf(0), spe(0),
//extra(false)
//{
//	name = "�A�C�A���V�[���h";
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
		//�����l�̎��̍s����ǂݍ���
		if (tokens[0].c_str() == "�����l		")
		{
			flag = true;
			continue;
		}

		if (flag == false) continue;
		equipmentData.Set(tokens);
	}
	csv->Close();
}

//	�f�X�g���N�^
BaseEquipment::~BaseEquipment(void)
{
//	SafeDelete(csv);
}

void	BaseEquipment::Initialize()
{

}

//**********************************************���̋@�\�͌�X�}�l�[�W���[�ɈڐA����*************************************************
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

//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

//	�X�V
void	BaseEquipment::Update(void)
{

}


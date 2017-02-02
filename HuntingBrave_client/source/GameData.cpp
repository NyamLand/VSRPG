
#include	"iextreme.h"
#include	"GameData.h"

//*****************************************************************************************************************************
//
//	GameData
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	PlayerInfo�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PlayerInfo::PlayerInfo( bool active, const LPSTR& name, int frontTitle, int backTitle )
	{
		this->active = active;
		strcpy( this->name, name );
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
	}

	//	���ݒ�
	void	PlayerInfo::Set( bool active, const LPSTR& name, int frontTitle, int backTitle )
	{
		this->active = active;
		strcpy( this->name, name );
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
	}

//----------------------------------------------------------------------------------------------
//	PlayerParam�\����
//----------------------------------------------------------------------------------------------	

	//	�R���X�g���N�^
	PlayerParam::PlayerParam( const Vector3& pos, float angle, float effParam, int motion, int frame, int life )
	{
		Set( pos, angle, effParam, motion, frame, life );
	}

	//	���ݒ�
	void	PlayerParam::Set( const Vector3& pos, float angle, float effParam, int motion, int frame, int life )
	{
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
		this->effParam = effParam;
		this->frame = frame;
		this->life = life;
		this->maxLife = 100;
	}

//----------------------------------------------------------------------------------------------
//	PlayerStatus�\����
//----------------------------------------------------------------------------------------------	

	//	������
	void	PlayerStatus::Initialize( int power, int defense, int magicPower, int magicDefense, int maxLife, float speed )
	{
		this->power = power;
		this->defense = defense;
		this->magicPower = magicPower;
		this->magicDefense = magicDefense;
		this->maxLife = maxLife;
		this->speed = speed;
	}

	//	�U���͐ݒ�
	void	PlayerStatus::CulcPower( int power )
	{
		this->power = power;
		if ( this->power <= 0 )	this->power = 0;
	}

	//	�h��͐ݒ�
	void	PlayerStatus::CulcDefense( int defense )
	{
		this->defense = defense;
		if ( this->defense <= 0 )	this->defense = 0;
	}

	//	���@�U���͐ݒ�
	void	PlayerStatus::CulcMagicPower( int power )
	{
		this->magicPower = power;
		if ( this->magicPower <= 0 )	this->magicPower = 0;
	}

	//	���@�U���͐ݒ�
	void	PlayerStatus::CulcMagicDefense( int defense )
	{
		this->magicDefense = defense;
		if ( this->magicDefense <= 0 )	this->magicDefense = 0;
	}

	//	�ő�HP�ݒ�
	void	PlayerStatus::CulcMaxLife( int maxLife )
	{
		this->maxLife = maxLife;
	}

	//	�X�s�[�h�ݒ�
	void	PlayerStatus::DoubleSpeed( float param )
	{
		speed = param;
		if ( speed <= 0.0f )		speed = 0.0f;
	}

//----------------------------------------------------------------------------------------------
//	Matching�\����
//----------------------------------------------------------------------------------------------

	//	�f�t�H���g�R���X�g���N�^
	Matching::Matching( void ) : id( -1 ), isComplete( false )
	{

	}

	//	�R���X�g���N�^
	Matching::Matching( int id, bool isComplete )
	{
		this->id = id;
		this->isComplete = isComplete;
	}

//----------------------------------------------------------------------------------------------
//	SignUp�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	SignUp::SignUp( int id, int* name, int frontTitle, int backTitle )
	{
		this->id = id;
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
		
		for ( int i = 0; i < 4; i++ )
		{
			this->name[i] = name[i];
		}
	}

	//	���ݒ�
	void	SignUp::Set( int id, int* name, int frontTitle, int backTitle )
	{
		this->id = id;
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
		for ( int i = 0; i < 4; i++ )
		{
			this->name[i] = name[i];
		}
	}

//----------------------------------------------------------------------------------------------
//	EquipmentParam�\����
//----------------------------------------------------------------------------------------------

	//	��񂹂��Ă�
	void	EquipmentData::Set(vector<string> tokens)
	{
		EquipmentInfo temp;

		temp.name = tokens[0].c_str();
		temp.atk = ( float )atoi(tokens[1].c_str());
		temp.def = ( float )atoi(tokens[2].c_str());
		temp.mat = ( float )atoi(tokens[3].c_str());
		temp.mdf = ( float )atoi(tokens[4].c_str());
		temp.hp = ( float )atoi(tokens[5].c_str());
		temp.spe = ( float )atoi(tokens[6].c_str());
		temp.text = tokens[7].c_str();

		equipments.push_back(temp);
	}
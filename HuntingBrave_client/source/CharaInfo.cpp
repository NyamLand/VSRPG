
#include	"iextreme.h"
#include	"BaseChara.h"
#include	"CharaInfo.h"

//***************************************************************
//
//	Chara�p�\����
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
//	AttackInfo�\����
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	AttackInfo::AttackInfo( void ) : attackParam( NO_ATTACK ),
		power( power ), step( 0 ), timer( 0 ),
		initFlag( false )
	{
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

	//	���Z�b�g
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0; 
		timer = 0;
		initFlag = false;
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

//-------------------------------------------------------------------------------------
//	LifeInfo�\����
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	LifeInfo::LifeInfo( void ) : 
		life( 0 ), maxLife( 0 ), 
		isAlive( true )
	{

	}

	//	���C�t�v�Z
	void	LifeInfo::CulcLife( int param )
	{
		life += param;
		if ( life >= maxLife )	life = maxLife;
		if ( life <= 0 )
		{
			life = 0;
			isAlive = false;
		}
	}

	//	���Z�b�g
	void	LifeInfo::Reset( void )
	{
		life = maxLife;
	}

	//	���ݒ�
	void	LifeInfo::Initialize( int initLife )
	{
		life = initLife;
		maxLife = initLife;
		isAlive = true;
	}
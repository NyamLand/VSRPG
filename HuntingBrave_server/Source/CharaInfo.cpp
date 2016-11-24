
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
		power( 0 ), step( 0 )
	{
		timer.Initialize();
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

	//	���Z�b�g
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0;
		timer.Initialize();
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

//-------------------------------------------------------------------------------------
//	LifeInfo�\����
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	LifeInfo::LifeInfo( void ) :
		life( 0 ), maxLife( 0 ),
		isAlive( true ), active( true )
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
		active = true;
	}

//-------------------------------------------------------------------------------------
//	CollisionInfo�\����
//-------------------------------------------------------------------------------------

	//	�f�t�H���g�R���X�g���N�^
	CollisionInfo::CollisionInfo( void ) : height( 0.0f ), radius( 0.0f )
	{
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}
	 
	//	�R���X�g���N�^
	CollisionInfo::CollisionInfo( const CollisionShape& colShape, float hitHeight, float hitRadius )
	{
		collisionShape = colShape;
		height = hitHeight;
		radius = hitRadius;
	}

	//	�`��ݒ�
	void	CollisionInfo::SetCollisionShape( const CollisionShape& colShape )
	{
		collisionShape = colShape;
	}

	//	���ݒ�
	void	CollisionInfo::Set( SHAPE_TYPE shapeType, float hitHeight, float hitRadius )
	{
		collisionShape.shapeType = shapeType;
		height = hitHeight;
		radius = hitRadius;
	}
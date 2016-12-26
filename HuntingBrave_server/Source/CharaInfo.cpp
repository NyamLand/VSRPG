
#include	"iextreme.h"
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
		step( 0 ),
		shapeType( 0 ),
		vec1( 0.0f, 0.0f, 0.0f ), vec2( 0.0f, 0.0f, 0.0f ),
		radius( 0.0f )
	{
		
	}

	//	���Z�b�g
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0;
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

	//	���C�t�v�Z( ���񂾂�false�������� )
	bool	LifeInfo::CulcLife( int param )
	{
		life += param;
		if ( life >= maxLife )	life = maxLife;
		if ( life <= 0 )
		{
			life = 0;
			isAlive = false;
			active = false;
			return	false;
		}

		return	true;
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

	//	���C�t�ő�l���Z
	void	LifeInfo::AddMaxLife( int param )
	{
		maxLife += param;
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
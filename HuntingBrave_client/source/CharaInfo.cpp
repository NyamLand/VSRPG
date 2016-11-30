
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
//	LifeInfo�\����
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	LifeInfo::LifeInfo( void ) : 
		life( 0 ), maxLife( 0 ), 
		isAlive( true ), active( false )
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
		active = false;
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
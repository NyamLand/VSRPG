
#pragma once

//*****************************************************************************************************************************
//
//	EnemyManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"Enemy.h"
#include	"Timer.h"

//	class
class EnemyManager
{
private:
	std::vector<Enemy*>		enemyList;
	Timer*	timer;

public:
	//	�������E���
	EnemyManager( void );
	~EnemyManager( void );
	bool	Initialize( void );
	void	Release( void );
	
	//	�X�V
	void	Update( float deltaTime );
	void	SendErase( int index );
	void	SendAppend( const Vector3& pos, float angle );

	//	����֐�
	void	Append( const Vector3& pos, float angle );
	void	PosCheck( Enemy*	enemy );
	void	PlayerPosCheck( Enemy*	eneny );

	//	���ݒ�
	void	TimerStart( void );

	//	���擾
};

extern	EnemyManager* enemyManager;
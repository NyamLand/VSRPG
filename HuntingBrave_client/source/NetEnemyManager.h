
#pragma once

//****************************************************************
//
//	NetEnemyManager�N���X
//
//****************************************************************

//	include
#include	"Singleton.h"
#include	"NetEnemy.h"

//	class
class NetEnemyManager : public Singleton<NetEnemyManager>
{
	friend	class Singleton<NetEnemyManager>;
private:
	iex3DObj*	org;
	std::vector<NetEnemy*>	enemyList;
private:
	//	�������E���
	NetEnemyManager( void );
	~NetEnemyManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	//void	RenderHp(void);
	//	����֐�
	void	Erase( int index );
	void	Append( const Vector3& pos, float angle );

	//	��M�֐�
	void	Receive( const LPSTR& data );
	void	ReceiveEnemyInfo( const LPSTR& data );
	void	ReceiveMoveInfo( const LPSTR& data );
	void	ReceiveModeInfo( const LPSTR& data );
	void	ReceiveMotionInfo( const LPSTR& data );
	void	ReceiveDeadInfo( const LPSTR& data );
	void	ReceiveEraseInfo( const LPSTR& data );
	void	ReceiveAppendInfo( const LPSTR& data );

	//	���ݒ�
	void	SetInfo( int index, const Vector3& pos, float angle );
	

	//	���擾
	std::vector<NetEnemy*>&		GetList( void );
};

#define	netEnemyManager ( NetEnemyManager::GetInstance() )
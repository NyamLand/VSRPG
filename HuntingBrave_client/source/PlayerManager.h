
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Player.h"


namespace
{
	namespace PLAYER_MODEL_TYPE
	{
		enum
		{
			NORMAL,
			MAGICIAN,	//	�}�W�V����
			PRIEST,		//	�v���[�X�g
			FIGHTER,		//	�t�@�C�^�[
			KNIGHT,		//	�i�C�g
			ASSASSIN,	//	�A�T�V��
			MODEL_MAX
		};
	}
}

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;
public:


private:
	//	�����f��
	iex3DObj*	obj[PLAYER_MODEL_TYPE::MODEL_MAX];

	//	�p�����[�^
	Player*	player[PLAYER_MAX];

	//	�������E���
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );
	void	LoadModel( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	void	RenderHp( void );
	
	//	���ݒ�
	void	SetPlayer( int id );
	void	PlayerClassChange( char nextType );

	//	���擾
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )

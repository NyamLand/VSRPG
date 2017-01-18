
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Suppin.h"
#include	"Fighter.h"
#include	"Magician.h"
#include	"Player.h"


namespace
{
	namespace PLAYER_TYPE
	{
		enum
		{
			NORMAL,
			FIGHTER,		//	�t�@�C�^�[
			MAGICIAN,	//	�}�W�V����
			KNIGHT,		//	�i�C�g
			PRIEST,		//	�v���[�X�g
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
	iex3DObj*	obj[PLAYER_TYPE::MODEL_MAX];

	//	�p�����[�^
	std::vector<Player*>	playerList;

	//	�������E���
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	void	RenderHp( void );

	//	����֐�
	void	ClassChange( int id, char nextClass );
	
	//	���ݒ�
	void	SetPlayer( int id );

	//	���擾
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )

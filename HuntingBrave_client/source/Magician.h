
#pragma once

//***************************************************************
//
//	Magician�N���X
//
//***************************************************************

//	incude
#include	"Player.h"

//	class
class Magician : public Player
{
private:

public:
	//	�������E���
	Magician( void );
	~Magician( void );
	bool	Initialize( int id )override;

	//	�X�V�E�`��

	//	����֐�
	void	ChangeTexture( int colorNum )override;

	//	���ݒ�

	//	���擾
};


#pragma once

//***************************************************************
//
//	Fighter�N���X
//
//***************************************************************

//	incude
#include	"Player.h"

//	class
class Fighter : public Player
{
private:

public:
	//	�������E���
	Fighter( void );
	~Fighter( void );
	bool	Initialize( int id )override;

	//	�X�V�E�`��

	//	����֐�
	void	ChangeTexture( int colorNum )override;

	//	���ݒ�

	//	���擾
};

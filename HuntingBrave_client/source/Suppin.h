
#pragma once

//***************************************************************
//
//	Suppin�N���X
//
//***************************************************************

//	incude
#include	"Player.h"

//	class
class Suppin : public Player
{
private:

public:
	//	�������E���
	Suppin( void );
	~Suppin( void );
	bool	Initialize( int id )override;
	
	//	�X�V�E�`��

	//	����֐�
	void	ChangeTexture( int colorNum )override;

	//	���ݒ�
	
	//	���擾
};

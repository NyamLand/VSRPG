
#pragma once

//***************************************************************
//
//	Effect�N���X
//
//***************************************************************

//	include

//	class
class Effect
{
protected:
	bool	eraseFlag;

public:
	//	�������E���
	Effect( void ) : eraseFlag( false ){}
	virtual ~Effect( void ){};

	//	�X�V�E�`��
	virtual	void	Update( void ) = 0;
	virtual	void	Render( void ) = 0;

	//	�����t���O�擾
	bool	GetEraseFlag( void ){ return	eraseFlag; }
};

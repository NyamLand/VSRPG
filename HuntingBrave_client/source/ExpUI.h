
#pragma once

//***************************************************************
//
//	ExpUI�N���X
//
//***************************************************************

#define	EXP_DIGIT	4

namespace EXP_MAX
{
	enum
	{
		ICON_SIZE = 64,				//	�摜��
	};
}

#include	"NumberUI.h"


//	class
class ExpUI
{
protected:
	Image* icon;
	NumberUI*	number;
	int	posx, posy, size;

public:
	//	�������E���
	ExpUI( int x, int y, int w, int h );
	virtual	~ExpUI( void );

	//	�X�V�E�`��
	void	Update( void );
	void	ExpManager( void );
	void	SetParam( int x, int y, int w, int h );
	void	SetRenderFlag( bool c );
	void	SetExp( int e );
	void	NumberSet( Image* img, const int num, const int digit );
	Image*	GetImageExp( void ){ return icon; }
	void	Render( void );
};

//	�K�v�o���lUI
class NeedExpUI : public ExpUI
{
private:
public:
	//	�������E���
	NeedExpUI( int x, int y, int w, int h );
	~NeedExpUI( void );
};




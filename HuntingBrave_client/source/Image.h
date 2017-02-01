
#pragma once



//******************************************************************************
//
//	�O���[�o���֐�
//
//******************************************************************************

//----------------------------------------------------------------------
//	�萔
//----------------------------------------------------------------------
namespace IMAGE_MODE
{
	enum
	{
		NORMAL,				//	�I���W�i���`��
		ADOPTPARAM,			//	�p�����[�^�̗p
		ADD,				//	���Z����
		WAVE,				//	�g��
		FLASH,				//	�_��
		SCALING,			//	�g��k��
		END,				//	�I�[
	};
}

namespace IMAGE_SCALING
{
	enum
	{
		BIG,				//	�g��
		SMALL,				//	�k��
	};
}


//**********************************************************************
//
//	Image�N���X
//
//**********************************************************************

class Image
{
public:
	iex2DObj*	obj;

	//	�p�����[�^
	int		x, y, w, h;
	int		sx, sy, sw, sh;
	float	t;
	float	alpha;
	float	angle;
	POINT	p;
	Vector3 color;
	bool	renderflag;

	//	wave�Escaling���ʗp�p�����[�^
	int	 plusScaleX;
	int	 plusScaleY;

	//	wave�p�p�����[�^
	float	waveSpeed;
	bool	waveState;

	//	flashing�p�p�����[�^
	float	flashSpeed;
	float	flashParam;

	//	scaling�p�p�����[�^
	float	scalingSpeed;
	bool	scalingAlphaFlag;
	int		scalingState;
	bool	scalingFlag;


public:
	Image();
	~Image();
	void	Initialize(char* image, int x, int y, int w, int h, int sx, int sy, int sw, int sh);
	//	�X�V�E�`��
	void	Update();		//	�X�V
	void	Render(int mode, iexShader* shader = nullptr, LPSTR techique = nullptr );		//	�`��
	void	Render(int mode, int x, int y, int w, int h, int sx, int sy, int sw, int sh);

	//--------------------------------
	//	�g��
	//--------------------------------

	//	�g��̐ݒ�(�g��X�s�[�h)
	void	SetWave(float speed);

	//	�g��X�V�i�g��傫���A�X�^�[�g�������x�j�g��I����true��������
	bool	WaveUpdate(int max_scale, float start_alpha = 1.0f);

	//--------------------------------
	//	�_��
	//--------------------------------

	//	�_�ōX�V�i�j
	bool	FlashUpdate();

	//	�_�ł̐ݒ�(�_�ŃX�s�[�h)
	void	SetFlash(float speed);

	//--------------------------------
	//	�g��k��
	//--------------------------------

	//	�g��k���p�ݒ�(�g��X�s�[�h)
	void	SetScaling(float speed, int mode = IMAGE_SCALING::BIG);

	//	�g��k���X�V(�ő�T�C�Y)
	bool	ScalingUpdate(int max_scale);
	//	�g��
	bool	ScalingBigUpdate(int max_scale);
	bool	ScalingMinUpdate(int max_scale);
};
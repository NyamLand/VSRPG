
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
	float	waveAlpha;
	bool	waveState;
	bool	waveRenderflag;

	//	flashing�p�p�����[�^
	float	flashingSpeed;
	float	flashingAlpha;
	float	flashingRenderflag;
	float	flashingParam;

	//	scaling�p�p�����[�^
	float	scalingspeed;
	float	scalingAlpha;
	bool	scalingAlphaFlag;
	bool	scalingState;
	bool	scalingFlag;
	bool	scalingrenderflag;


public:
	Image();
	~Image();
	void	Initialize(char* image, int x, int y, int w, int h, int sx, int sy, int sw, int sh);
	//	�X�V�E�`��
	void	Update();		//	�X�V
	void	Render(int mode);		//	�`��
	void	Render(int mode, int x, int y, int w, int h, int sx, int sy, int sw, int sh);

	//	�g��̐ݒ�(�g��o�������I�u�W�F�N�g�A�g��X�s�[�h)
	void	SetWave(float speed);

	//	�g��X�V�i�g��o�������I�u�W�F�N�g�A�g��傫���A�X�^�[�g�������x�j�g��I����true��������
	bool	WaveUpdate(int max_scale = 140, float max_alpha = 1.0f);

	//	�_�ōX�V�i�_�ł��������I�u�W�F�N�g�A�_�ŃX�s�[�h�j
	void	FlashingUpdate(float speed = -1.0f);

};
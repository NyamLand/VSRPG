#include		"iextreme.h"
#include		"GlobalFunction.h"
#include		"Interpolation.h"
#include		"Image.h"

//***************************************************************
//
//	Image�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Image::Image()
	{

	}

	//	�f�X�g���N�^
	Image::~Image()
	{

	}

	//	������
	void	Image::Initialize(char *image, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
	{
		obj = new iex2DObj(image);
		this->x = x;		this->y = y;		this->w = w;		this->h = h;
		this->sx = sx;		this->sy = sy;		this->sw = sw;		this->sh = sh;
		this->alpha = 1.0f;
		this->angle = 0.0f;
		this->color = Vector3(1.0f, 1.0f, 1.0f);
		this->p = GetPoint(this->x, this->y);
		this->renderflag = true;
	}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------
	void	Image::Update()
	{

	}

	//	�������[�h�̂�
	void	Image::Render(int mode)
	{
		int width = this->w;
		int height = this->h;
		int posx = this->x - this->w / 2;
		int	posy = this->y - this->h / 2;

		if (renderflag){
			switch (mode)
			{
			case IMAGE_MODE::NORMAL:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh);
				break;

			case IMAGE_MODE::ADOPTPARAM:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
				break;

			case IMAGE_MODE::ADD:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_ADD, GetColor(color, alpha));
				break;

			case IMAGE_MODE::WAVE:
				width = this->w + this->plusScaleX;
				height = this->h + this->plusScaleY;
				posx = x - width / 2;
				posy = y - height / 2;
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, RS_COPY, GetColor(color, waveAlpha));
				break;

			case IMAGE_MODE::FLASH:
					//obj->Render(posx, posy, width, height, sx, sy, sw, sh, RS_COPY, GetColor(color, flashingAlpha));
				break;

			case IMAGE_MODE::SCALING:
				//width = image.w + image.plusScaleX;
				//height = image.h + image.plusScaleY;
				//posx = x - width / 2;
				//posy = y - height / 2;

					//obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
				break;
			}
		}

	}


	//	�����̒l���g�p
	void	Image::Render( int mode, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
	{
			int width = w;
			int height = h;
			int posx = x - w / 2;
			int	posy = y - h / 2;

			if (renderflag){
				switch (mode)
				{
				case IMAGE_MODE::NORMAL:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh);
					break;

				case IMAGE_MODE::ADOPTPARAM:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
					break;

				case IMAGE_MODE::ADD:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_ADD, GetColor(color, alpha));
					break;

				case IMAGE_MODE::WAVE:
					width = w + this->plusScaleX;
					height = h + this->plusScaleY;
					posx = x - width / 2;
					posy = y - height / 2;
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, RS_COPY, GetColor(color, waveAlpha));
					break;

				case IMAGE_MODE::FLASH:
					//obj->Render(posx, posy, width, height, sx, sy, sw, sh, RS_COPY, GetColor(color, flashingAlpha));
					break;

				case IMAGE_MODE::SCALING:
					//width = image.w + image.plusScaleX;
					//height = image.h + image.plusScaleY;
					//posx = x - width / 2;
					//posy = y - height / 2;

					//obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
					break;
				}
			}

		}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------
	//	�g��X�V�i�g��傫���A�X�^�[�g�������x�j�g��I����true��������
	bool	Image::WaveUpdate(int max_scale, float max_alpha)
	{
		if (waveState)
		{
			//	�p�����[�^���Z
			t += waveSpeed;

			//	�p�����[�^����ݒ�
			if (t >= 1.0f)
			{
				t = 1.0f;
				waveState = false;
				waveRenderflag = false;
			}

			Interpolation::LinearInterpolation(waveAlpha, max_alpha, 0.0f, t);
			Interpolation::LinearInterpolation(plusScaleX, 0, max_scale, t);
			Interpolation::LinearInterpolation(plusScaleY, 0, max_scale, t);

		}

		if (t >= 1.0f)		return	true;
		return	false;
	}

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------
	void	Image::SetWave(float speed)
	{
		plusScaleX = 0;
		plusScaleY = 0;
		t = 0;
		waveAlpha = 1.0f;
		waveState = true;
		waveSpeed = speed;
		waveRenderflag = true;
	}
//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------


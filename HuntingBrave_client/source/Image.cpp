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
	Image::Image() : x(0), y(0), w(0), h(0), sx(0), sy(0), sw(0), sh(0), alpha(1.0f), angle(0.0f), renderflag(true),
	waveSpeed(0.0f), waveState(false), flashSpeed(0.0f), flashParam(0.0f), scalingFlag(false), scalingSpeed(0.0f), scalingState(0)
	{
		this->color = Vector3(1.0f, 1.0f, 1.0f);
		this->p = GetPoint(this->x, this->y);
		this->obj = nullptr;
	}

	//	�f�X�g���N�^
	Image::~Image()
	{
		SafeDelete(obj);
	}

	//	������
	void	Image::Initialize(char *image, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
	{
		obj = new iex2DObj(image);
		this->x = x;		this->y = y;		this->w = w;		this->h = h;
		this->sx = sx;		this->sy = sy;		this->sw = sw;		this->sh = sh;
		this->p = GetPoint(this->x, this->y);
	}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------
	void	Image::Update()
	{

	}

	//	�������[�h�̂�
	void	Image::Render(int mode, iexShader* shader, LPSTR technique )
	{
		int width = this->w;
		int height = this->h;
		int posx = this->x - this->w / 2;
		int	posy = this->y - this->h / 2;

		if (renderflag){
			switch (mode)
			{
			case IMAGE_MODE::NORMAL:
				obj->Render(posx, posy, width, height, sx, sy, sw, sh );
				if ( shader != nullptr && technique != nullptr )
					obj->Render( posx, posy, width, height, sx, sy, sw, sh, shader, technique );
				break;

			case IMAGE_MODE::ADOPTPARAM:
				obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor( color, alpha ) );
				break;

			case IMAGE_MODE::ADD:
				obj->Render( posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_ADD, GetColor( color, alpha ) );
				break;

			case IMAGE_MODE::WAVE:
				width = this->w + this->plusScaleX;
				height = this->h + this->plusScaleY;
				posx = x - width / 2;
				posy = y - height / 2;
				obj->Render( posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor( color, alpha ) );
				break;

			case IMAGE_MODE::FLASH:
				obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor( color, alpha ) );
				break;

			case IMAGE_MODE::SCALING:
				width = w + plusScaleX;
				height = h + plusScaleY;
				posx = x - width / 2;
				posy = y - height / 2;

				obj->Render( posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor( color, alpha ) );
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
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
					break;

				case IMAGE_MODE::FLASH:
					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
					break;

				case IMAGE_MODE::SCALING:
					width = w + plusScaleX;
					height = h + plusScaleY;
					posx = x - width / 2;
					posy = y - height / 2;

					obj->Render(posx, posy, width, height, sx, sy, sw, sh, p, angle, RS_COPY, GetColor(color, alpha));
					break;
				}
			}

		}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------
	//	�g��X�V�i�g��傫���A�X�^�[�g�������x�j�g��I����true��������
	bool	Image::WaveUpdate(int max_scale, float start_alpha)
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
				renderflag = false;
				return	true;
			}

			Interpolation::LinearInterpolation(alpha, start_alpha, 0.0f, t);
			Interpolation::LinearInterpolation(plusScaleX, 0, max_scale, t);
			Interpolation::LinearInterpolation(plusScaleY, 0, max_scale, t);

		}

		//if (t >= 1.0f)		return	true;
		return	false;
	}

	//
	void	Image::FlashUpdate()
	{
		flashParam += flashSpeed;

		if (flashParam >= 6.0f)
		{
			flashParam = 0.0f;
		}

		alpha = 0.5f + 0.5f * sinf(flashParam);

	}

	//	�g��k���X�V
	void	Image::ScalingUpdate( int max_scale)
	{
		if (!scalingFlag) return;

		//	�p�����[�^���Z
		t += scalingSpeed;

		switch (scalingState)
		{
		//-------------------------
		//	�g��
		//-------------------------
		case IMAGE_SCALING::BIG:
			//	�p�����[�^����ݒ�
			if (t >= 1.0f)
			{
				t = 1.0f;
				scalingState = IMAGE_SCALING::SMALL;
			}

			Interpolation::LinearInterpolation(plusScaleX, 0, max_scale, t);
			Interpolation::LinearInterpolation(plusScaleY, 0, max_scale, t);

			break;

		//-------------------------
		//	�k��
		//-------------------------
		case IMAGE_SCALING::SMALL:
			//	�p�����[�^����ݒ�
			if (t >= 1.0f)
			{
				t = 1.0f;
				scalingState = IMAGE_SCALING::BIG;
			}

			Interpolation::LinearInterpolation(plusScaleX, max_scale, 0, t);
			Interpolation::LinearInterpolation(plusScaleY, max_scale, 0, t);

			break;
		}

		if (t >= 1.0f)		t = 0.0f;
	}


//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------
	void	Image::SetWave(float speed)
	{
		plusScaleX = 0;
		plusScaleY = 0;
		t = 0;
		waveState = true;
		waveSpeed = speed;
	}

	void	Image::SetFlash(float speed)
	{
		plusScaleX = 0;
		plusScaleY = 0;
		t = 0.0f;
		flashParam = 0.0f;
		flashSpeed = speed;
	}

	void	Image::SetScaling(float speed)
	{
		plusScaleX = 0;
		plusScaleY = 0;
		t = 0.0f;
		alpha = 1.0f;
		scalingFlag = true;
		scalingState = IMAGE_SCALING::BIG;
		scalingSpeed = speed;
	}
//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------


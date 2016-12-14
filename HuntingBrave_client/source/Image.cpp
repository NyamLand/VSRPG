#include		"iextreme.h"
#include		"GlobalFunction.h"
#include		"Interpolation.h"
#include		"Image.h"

//***************************************************************
//
//	Imageクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	Image::Image() : x(0), y(0), w(0), h(0), sx(0), sy(0), sw(0), sh(0), alpha(1.0f), angle(0.0f), renderflag(true),
	waveSpeed(0.0f), waveState(false), flashSpeed(0.0f), flashParam(0.0f), scalingFlag(false), scalingSpeed(0.0f), scalingState(0)
	{
		this->color = Vector3(1.0f, 1.0f, 1.0f);
		this->p = GetPoint(this->x, this->y);
		this->obj = nullptr;
	}

	//	デストラクタ
	Image::~Image()
	{
		SafeDelete(obj);
	}

	//	初期化
	void	Image::Initialize(char *image, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
	{
		obj = new iex2DObj(image);
		this->x = x;		this->y = y;		this->w = w;		this->h = h;
		this->sx = sx;		this->sy = sy;		this->sw = sw;		this->sh = sh;
		this->p = GetPoint(this->x, this->y);
	}

//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------
	void	Image::Update()
	{

	}

	//	引数モードのみ
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


	//	引数の値を使用
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
//	動作関数
//---------------------------------------------------------------------------------------
	//	波紋更新（波紋大きさ、スタート時透明度）波紋終了時trueをかえす
	bool	Image::WaveUpdate(int max_scale, float start_alpha)
	{
		if (waveState)
		{
			//	パラメータ加算
			t += waveSpeed;

			//	パラメータ上限設定
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

	//	拡大縮小更新
	void	Image::ScalingUpdate( int max_scale)
	{
		if (!scalingFlag) return;

		//	パラメータ加算
		t += scalingSpeed;

		switch (scalingState)
		{
		//-------------------------
		//	拡大
		//-------------------------
		case IMAGE_SCALING::BIG:
			//	パラメータ上限設定
			if (t >= 1.0f)
			{
				t = 1.0f;
				scalingState = IMAGE_SCALING::SMALL;
			}

			Interpolation::LinearInterpolation(plusScaleX, 0, max_scale, t);
			Interpolation::LinearInterpolation(plusScaleY, 0, max_scale, t);

			break;

		//-------------------------
		//	縮小
		//-------------------------
		case IMAGE_SCALING::SMALL:
			//	パラメータ上限設定
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
//	情報設定
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
//	情報取得
//---------------------------------------------------------------------------------------


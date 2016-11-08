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
	Image::Image()
	{

	}

	//	デストラクタ
	Image::~Image()
	{

	}

	//	初期化
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
//	更新・描画
//---------------------------------------------------------------------------------------
	void	Image::Update()
	{

	}

	//	引数モードのみ
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
//	動作関数
//---------------------------------------------------------------------------------------
	//	波紋更新（波紋大きさ、スタート時透明度）波紋終了時trueをかえす
	bool	Image::WaveUpdate(int max_scale, float max_alpha)
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
//	情報設定
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
//	情報取得
//---------------------------------------------------------------------------------------



#pragma once



//******************************************************************************
//
//	グローバル関数
//
//******************************************************************************

//----------------------------------------------------------------------
//	定数
//----------------------------------------------------------------------
namespace IMAGE_MODE
{
	enum
	{
		NORMAL,				//	オリジナル描画
		ADOPTPARAM,			//	パラメータ採用
		ADD,				//	加算合成
		WAVE,				//	波紋
		FLASH,				//	点滅
		SCALING,			//	拡大縮小
		END,				//	終端
	};
}

namespace IMAGE_SCALING
{
	enum
	{
		BIG,				//	拡大
		SMALL,				//	縮小
	};
}


//**********************************************************************
//
//	Imageクラス
//
//**********************************************************************

class Image
{
public:
	iex2DObj*	obj;

	//	パラメータ
	int		x, y, w, h;
	int		sx, sy, sw, sh;
	float	t;
	float	alpha;
	float	angle;
	POINT	p;
	Vector3 color;
	bool	renderflag;

	//	wave・scaling共通用パラメータ
	int	 plusScaleX;
	int	 plusScaleY;

	//	wave用パラメータ
	float	waveSpeed;
	bool	waveState;

	//	flashing用パラメータ
	float	flashSpeed;
	float	flashParam;

	//	scaling用パラメータ
	float	scalingSpeed;
	bool	scalingAlphaFlag;
	int		scalingState;
	bool	scalingFlag;


public:
	Image();
	~Image();
	void	Initialize(char* image, int x, int y, int w, int h, int sx, int sy, int sw, int sh);
	//	更新・描画
	void	Update();		//	更新
	void	Render(int mode, iexShader* shader = nullptr, LPSTR techique = nullptr );		//	描画
	void	Render(int mode, int x, int y, int w, int h, int sx, int sy, int sw, int sh);

	//--------------------------------
	//	波紋
	//--------------------------------

	//	波紋の設定(波紋スピード)
	void	SetWave(float speed);

	//	波紋更新（波紋大きさ、スタート時透明度）波紋終了時trueをかえす
	bool	WaveUpdate(int max_scale, float start_alpha = 1.0f);

	//--------------------------------
	//	点滅
	//--------------------------------

	//	点滅更新（）
	bool	FlashUpdate();

	//	点滅の設定(点滅スピード)
	void	SetFlash(float speed);

	//--------------------------------
	//	拡大縮小
	//--------------------------------

	//	拡大縮小用設定(拡大スピード)
	void	SetScaling(float speed, int mode = IMAGE_SCALING::BIG);

	//	拡大縮小更新(最大サイズ)
	bool	ScalingUpdate(int max_scale);
	//	拡大
	bool	ScalingBigUpdate(int max_scale);
	bool	ScalingMinUpdate(int max_scale);
};
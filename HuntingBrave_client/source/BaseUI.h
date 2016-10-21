
#pragma once



//**********************************************************************
//
//	BaseUIクラス
//
//**********************************************************************

class BaseUI
{
private:
	iex2DObj*	obj;

	//	パラメータ
	int		x, y, w, h;
	int		sx, sy, sw, sh;
	float	alpha;
	float	angle;
	POINT	p;
	Vector3 color;

};
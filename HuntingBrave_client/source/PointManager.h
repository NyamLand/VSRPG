
#pragma once

//****************************************************************
//
//	PointManagerクラス
//
//****************************************************************

//	include
#include	"Singleton.h"

struct PointInfo
{
	int	id;
	int	point;
	bool	operator<( const PointInfo& another )const
	{
		return ( id < another.id );
	}
	bool	operator==( int another )const
	{
		return	( id == another );
	}
};

//	class
class PointManager : public Singleton<PointManager>
{
	friend	class Singleton<PointManager>;
private:
	std::vector<PointInfo>	pointList;

private:
	//	初期化・解放
	PointManager( void );
	~PointManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );

	//	動作関数
	void	Receive( const LPSTR& data );
	void	Sort( void );

	//	情報取得
	int	GetRank( int player );
	int	GetPlayer( int rank );
	int	GetPoint( int player );
};

#define	pointManager ( PointManager::GetInstance() )

#pragma once

//****************************************************************
//
//	PointManager�N���X
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
	//	�������E���
	PointManager( void );
	~PointManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update( void );

	//	����֐�
	void	Receive( const LPSTR& data );
	void	Sort( void );

	//	���擾
	int	GetRank( int player );
	int	GetPlayer( int rank );
	int	GetPoint( int player );
};

#define	pointManager ( PointManager::GetInstance() )
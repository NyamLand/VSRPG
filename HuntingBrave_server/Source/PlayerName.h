
#pragma once

//**************************************************************************
//
//	PlayerNameクラス
//
//**************************************************************************

//	include
struct NameInfo
{
	char	name[17];		//	名前
	int	nameIndex[4];	//	名前インデックス
};

//	class
class PlayerName
{
private:
	NameInfo	nameInfo[PLAYER_MAX];

public:
	//	初期化・解放
	PlayerName( void );
	~PlayerName( void );
	void	Initialize( void );

	//	動作関数
	char*	SrcCharFromIndex( int* nameIndex );
	void		SetName( int id, int* nameIndex );

	//	情報取得
	int*		GetNameIndex( int id );
	char*	GetName( int id );
};
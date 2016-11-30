
#pragma once

//****************************************************************
//
//	MagicManagerクラス
//
//****************************************************************

//	include
#include	"Singleton.h"
#include	"Magic.h"

//	class
class MagicManager : public Singleton<MagicManager>
{
	friend	class Singleton<MagicManager>;
private:
	iexMesh*	org;
	std::vector<Magic*>	magicList;

private:
	//	初期化・解放
	MagicManager( void );
	~MagicManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数
	void	Erase( int index );
	void	Append( int id, const Vector3& pos, float angle );

	//	情報設定
	void	SetPos( int index, const Vector3& pos );

	//	情報取得
	std::vector<Magic*>&		GetList( void );

};

#define	magicManager ( MagicManager::GetInstance() )
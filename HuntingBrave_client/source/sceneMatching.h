
//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

#include	"GameData.h"
#include	"NameInput.h"
#include	"ItemSelect.h"
#include	<memory>
using namespace std;

class	sceneMatching : public Scene
{
private:
	iex3DObj*	obj[PLAYER_MAX];
	int step;
	char	nextScene;
	char name[17];
	char	addr[64];
	iex2DObj*	back;
	NameInput*	nameInput;
	ItemSelect*	itemSelect;

public:
	~sceneMatching( void );
	//	初期化
	bool Initialize( void );
	
	//	更新・描画
	void Update( void );	//	更新
	void Render( void );	//	描画

	//	動作関数
	void	ObjUpdate( void );
	void	CheckComplete( void );
	void	DebugRender( void );
	void	MyInfoRender( void );
};



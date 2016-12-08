
//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

#include	"GameData.h"
#include	"NameInput.h"
#include	"ItemSelect.h"
#include	"GameWait.h"
#include	<memory>
using namespace std;

class	sceneMatching : public Scene
{
private:
	int step;
	char	nextScene;
	char name[17];
	char	addr[64];
	NameInput*	nameInput;
	ItemSelect*	itemSelect;
	GameWait*	gameWait;

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



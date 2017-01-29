
//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

#include	"GameData.h"
#include	"WaitLoad.h"
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
	WaitLoad*	waitLoad;
	NameInput*	nameInput;
	ItemSelect*	itemSelect;
	GameWait*	gameWait;
	static	bool	threadState;

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

	//	thread
	static	void	ThreadFunc( void* ptr );
	static	void	WaitThread( void );
	static	void	ServerInitThread( bool& out, char* addr, int* name );
};



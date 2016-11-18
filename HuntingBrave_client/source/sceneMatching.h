
//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

#include	<memory>
using namespace std;

//	クラス前方宣言
class GameParam;

class	sceneMatching : public Scene
{
private:
	unique_ptr<iex3DObj>	obj[PLAYER_MAX];
public:
	~sceneMatching(void);
	//	初期化
	bool Initialize(void);
	//	更新・描画
	void Update(void);	//	更新
	void Render(void);	//	描画

	//	動作関数
	void	ObjUpdate(void);
	void	CheckComplete(void);
	void	DebugRender(void);
	void	MyInfoRender(void);
};



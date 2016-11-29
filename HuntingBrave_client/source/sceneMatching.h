
//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

#include	"GameData.h"
#include	<memory>
using namespace std;

class	sceneMatching : public Scene
{
private:
	unique_ptr<iex3DObj>	obj[PLAYER_MAX];
	int step;
	char name[17];
	char	addr[64];
public:
	~sceneMatching(void);
	//	������
	bool Initialize(void);
	//	�X�V�E�`��
	void Update(void);	//	�X�V
	void Render(void);	//	�`��

	//	����֐�
	void	ObjUpdate(void);
	void	CheckComplete(void);
	void	DebugRender(void);
	void	MyInfoRender(void);
};




//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

#include	<memory>
using namespace std;

//	�N���X�O���錾
class GameParam;

class	sceneMatching : public Scene
{
private:
	unique_ptr<iex3DObj>	obj[PLAYER_MAX];
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



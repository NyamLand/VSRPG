//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

//	�N���X�O���錾
class GameParam;

class	sceneMain : public Scene
{
private:
	iexView*	view;
	static	GameParam*	gameParam;
	
public:
	~sceneMain();
	//	������
	bool Initialize();
	//	�X�V�E�`��
	void Update();	//	�X�V
	void Render();	//	�`��

	//	thread test
	static void	ThreadFunc( int& client );
	static	void	ThreadFunc2( int client );
};



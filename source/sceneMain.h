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
	static	GameParam*	m_GameParam;

public:
	~sceneMain( void );
	//	������
	bool Initialize( void );
	//	�X�V�E�`��
	void Update( void );	//	�X�V
	void Render( void );	//	�`��

	//	���擾
	void	MyInfoRender( void );
	static	void	ThreadFunc1( void );
	static	void	ThreadFunc2( void );
};



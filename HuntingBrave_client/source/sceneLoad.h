//***************************************************************
//
//	sceneLoad�N���X
//
//***************************************************************

//	include	

//	class
class sceneLoad : public Scene
{
private:
public:
	//	�������E���
	bool	Initialize( void )override;
	~sceneLoad( void )override;

	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( void )override;
};


#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	<vector>
#include	<algorithm>
#include	"PointManager.h"

//***************************************************************
//
//	PointManager�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

	namespace
	{
		//	�_�����
		struct ReceivePointData
		{
			char	com = RECEIVE_COMMAND::POINT_INFO;
			int		id;
			int		point;
		};
	}

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PointManager::PointManager( void )
	{
		pointList.clear();
	}

	//	�f�X�g���N�^
	PointManager::~PointManager( void )
	{
		Release();
	}

	//	������
	bool	PointManager::Initialize( void )
	{
		pointList.clear();

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			PointInfo	pointInfo{ i, 0 };
			pointList.push_back( pointInfo );
		}
		return	true;
	}

	//	���
	void	PointManager::Release( void )
	{
		pointList.clear();
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	��M
	void	PointManager::Receive( const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;

		Sort();
		int index = GetRank( receivePointData->id );
		pointList[index].point = receivePointData->point;
	}

	//	�\�[�g
	void	PointManager::Sort( void )
	{
		std::sort( pointList.begin(), pointList.end() );
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	�v���C���[�����N�擾( ���ʂ��w�肵�āA���̏��ʂ̃v���C���[�ԍ����擾 )
	int	PointManager::GetRank( int player )
	{
		//	�����ɍ����C�e���[�^���擾
		auto	result = std::find( pointList.begin(), pointList.end(), player );

		//	�C���f�b�N�X���擾
		int	index = std::distance( pointList.begin(), result );

		return	index;
	}

	//	�_���擾
	int	PointManager::GetPoint( int player )
	{
		int index = GetRank( player );
		int point = pointList[index].point;
		return	point;
	}

	//	�w�肵�������N�̃v���C���[�擾
	int	PointManager::GetPlayer( int rank )
	{
		//	�\�[�g������
		Sort();
		
		//	�w�肵�������N��ID�擾
		int index = pointList[rank].id;
		return	index;
	}
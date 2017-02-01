
#include	"iextreme.h"
#include	"GameParam.h"
#include	"PointManager.h"

//****************************************************************
//
//	PointManager�N���X
//
//****************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//	����
PointManager*	pointManager = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PointManager::PointManager( void )
	{

	}

	//	�f�X�g���N�^
	PointManager::~PointManager( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�|�C���g�v�Z
	void	PointManager::CalcPoint( int id, int point )
	{
		this->point[id] += point;

		if ( this->point[id] <= 0 )	this->point[id] = 0;
	}

	//	�|�C���g���M
	void	PointManager::SendPoint( int id )
	{
		SendPointData	sendPointData( id, point[id] );

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendPointData, sizeof( sendPointData ) );
		}
	}

	//	��������M
	void	PointManager::ReceiveHuntInfo( int client, const LPSTR& data )
	{
		//	�\���̐錾
		static	struct HuntInfo
		{
			char com;
			char infoType;
			char enemyType;
		} *huntInfo;
		
		//	�ϊ�
		huntInfo = ( HuntInfo* )data;

		//	�v�Z�A�ԐM
		CalcPoint( client, 100 );
		SendPoint( client );
	}

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------



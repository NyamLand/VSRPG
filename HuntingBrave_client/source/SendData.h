
#pragma once

//****************************************************************
//
//	SendData
//
//****************************************************************

#include	"iextreme.h"

	//	送信コマンド
	namespace
	{
		namespace SEND_COMMAND
		{
			enum 
			{
				NO_COMMAND = -1,
				PLAYER_INFO = 1,
				ATTACK_INFO,
				POINT_INFO,
				INPUT_INFO,
			};
		}
	}

//----------------------------------------------------------------------------------------------
//	送信用構造体
//----------------------------------------------------------------------------------------------

	//	プレイヤーデータ送信用
	struct SendPlayerData
	{
		char	com = SEND_COMMAND::PLAYER_INFO;	//1byte
		float	axisX, axisY;	//	8byte
		int 	frame;			//	4byte
		//	13byte
		SendPlayerData( float axisX, float axisY, int frame ) : 
			axisX( axisX ), axisY( axisY ), frame( frame ){}
	};

	//	攻撃情報
	struct SendAttackData
	{
		char			com = SEND_COMMAND::ATTACK_INFO;		//	1byte
		char			shape;
		float			radius;		//	4byte
		Vector3	attackPos1;		//	12byte
		Vector3	attackPos2;		//	12byte
		SendAttackData( char shape, const Vector3& attackPos1, const Vector3& attackPos2, float radius ) :
			attackPos1( attackPos1 ), attackPos2( attackPos2 ), radius( radius ) {}
	};

	//	点数情報
	struct SendPointData
	{
		char		com = SEND_COMMAND::POINT_INFO;
		int		addPoint;
		SendPointData( int addPoint ) : addPoint( addPoint ){};
	};

	//	入力情報
	struct SendInputData
	{
		char		com = SEND_COMMAND::INPUT_INFO;
		int		keyType;
		int		keyState;
		SendInputData( void ){};
		SendInputData( int keyType, int keyState ) :
			keyType( keyType ), keyState( keyState ){}
	};
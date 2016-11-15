
#pragma once

//****************************************************************
//
//	SendData
//
//****************************************************************

	//	送信コマンド
	namespace
	{
		namespace SEND_COMMAND
		{
			enum 
			{
				NO_COMMAND = -1,
				PLAYER_INFO = 1,
				POINT_INFO,
				INPUT_INFO,
			};
		}
	}

//----------------------------------------------------------------------------------------------
//	送信用構造体
//----------------------------------------------------------------------------------------------

	//	キャラクターデータ送信用
	struct SendPlayerData
	{
		char	com = SEND_COMMAND::PLAYER_INFO;
		int		id;
		float	axisX, axisY;
		int 	frame;
		SendPlayerData( int myIndex, float axisX, float axisY, int frame ) : 
			id( myIndex ), axisX( axisX ), axisY( axisY ), frame( frame ){};
	};

	//	点数情報
	struct SendPointData
	{
		char	com = SEND_COMMAND::POINT_INFO;
		int		id;
		int		addPoint;
		SendPointData( int myIndex, int addPoint ) : id( myIndex ), addPoint( addPoint ){};
	};

	//	入力情報
	struct SendInputData
	{
		char com = SEND_COMMAND::INPUT_INFO;
		int		id;
		int		buttonType;
		int		inputType;
		SendInputData( void ){};
		SendInputData( int myIndex, int buttonType, int inputType ) :
			id( myIndex ), buttonType( buttonType ), inputType( inputType ){}
	};
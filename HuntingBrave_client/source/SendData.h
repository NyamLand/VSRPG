
#pragma once

//****************************************************************
//
//	SendData
//
//****************************************************************

#include	"iextreme.h"

	//	���M�R�}���h
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
//	���M�p�\����
//----------------------------------------------------------------------------------------------

	//	�v���C���[�f�[�^���M�p
	struct SendPlayerData
	{
		char	com = SEND_COMMAND::PLAYER_INFO;	//1byte
		float	axisX, axisY;	//	8byte
		char	button;			//	1byte
		char	inputType;	//	1byte
		int 	frame;			//	4byte
		//	15byte
		SendPlayerData( float axisX, float axisY, char button, char inputType, int frame ) : 
			axisX( axisX ), axisY( axisY ), 
			button( button ), inputType( inputType ), 
			frame( frame ){}
	};

	//	�U�����
	struct SendAttackData
	{
		char			com = SEND_COMMAND::ATTACK_INFO;		//	1byte
		float			radius;		//	4byte
		Vector3	attackPos1;		//	12byte
		Vector3	attackPos2;		//	12byte
		SendAttackData( const Vector3& attackPos1, const Vector3& attackPos2, float radius ) :
			attackPos1( attackPos1 ), attackPos2( attackPos2 ), radius( radius ) {}
	};

	//	�_�����
	struct SendPointData
	{
		char		com = SEND_COMMAND::POINT_INFO;
		int		addPoint;
		SendPointData( int addPoint ) : addPoint( addPoint ){};
	};

	//	���͏��
	struct SendInputData
	{
		char		com = SEND_COMMAND::INPUT_INFO;
		int		buttonType;
		int		inputType;
		SendInputData( void ){};
		SendInputData( int buttonType, int inputType ) :
			buttonType( buttonType ), inputType( inputType ){}
	};
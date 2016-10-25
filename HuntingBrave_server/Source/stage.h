
#pragma once

class iexRayMesh {
private:
protected:
	u32			NumVertex;
	u32			NumFace;

	Vector		*Vertices;
	u16			*Faces;

	Vector		*Normals;
	Vector3		*Positions;

public:
	bool	bflag;

	iexRayMesh( char* filename );
	~iexRayMesh();

	bool LoadIMO( char* filename );

	int	RayPick( Vector3* out, Vector3* pos, Vector3* vec, float *Dist );
	int	RayPickUD( Vector3* out, Vector3* pos, Vector3* vec, float *Dist );
};
//*****************************************************************************
//
//		�X�e�[�W�N���X
//
//*****************************************************************************
class cStage {
private:
	iexRayMesh*	objX;

public:
	//------------------------------------------------------
	//	�������E���
	//------------------------------------------------------
	cStage();
	~cStage();

	//------------------------------------------------------
	//	����
	//------------------------------------------------------
	float GetHeight( Vector3& pos );
	float Wall( Vector3& pos, Vector3& v );

	Vector3	MoveCheck( Vector3& pos, Vector3& move );
};

extern	cStage* stage;
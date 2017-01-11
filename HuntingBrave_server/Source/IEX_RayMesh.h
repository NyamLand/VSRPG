
#pragma once

//*****************************************************************************************************************************
//
//	IEX_RayMeshƒNƒ‰ƒX
//
//*****************************************************************************************************************************

//	class
class iexRayMesh 
{
protected:
	u32			NumVertex;
	u32			NumFace;

	Vector		*Vertices;
	u16			*Faces;

	Vector		*Normals;
	Vector3		*Positions;

public:
	bool	bflag;

	iexRayMesh(char* filename);
	~iexRayMesh();

	bool LoadIMO(char* filename);

	int	RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist);
	int	RayPickUD(Vector3* out, Vector3* pos, Vector3* vec, float *Dist);
};
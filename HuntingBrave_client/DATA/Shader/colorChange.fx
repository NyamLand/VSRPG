
//********************************************************************
//
//		��{�R�c�V�F�[�_�[		
//
//********************************************************************

//------------------------------------------------------
//		�F���蓮�ݒ�p
//------------------------------------------------------

float3	color = float3( 1.0f, 1.0f, 1.0f );
float		alpha = 1.0f;

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------
float4 PS_ColorChange( VS_OUTPUT In ) : COLOR
{
	float4	OUT;

	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	//	�F�K�p
	OUT.rgb += color;
	OUT.a = alpha;

	return OUT;
}

//	�����o�[�g�g�U�Ɩ�

//------------------------------------------------------
//		�ʏ�`��e�N�j�b�N
//------------------------------------------------------
technique colorChange
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_2_0 VS_Basic();
		PixelShader = compile ps_2_0 PS_ColorChange();
	}
}

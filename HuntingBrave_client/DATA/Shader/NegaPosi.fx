//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------

//	����
float4 PS_NegaPosi( VS_2D In ) : COLOR
{
	//	�o��
	float4	OUT;

	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	//	������
	OUT.rgb = 1.0f - OUT.rgb;

	return OUT;
}

//------------------------------------------------------
//		�e�N�j�b�N
//------------------------------------------------------

//	����
technique negaPosi
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = None;
		ZEnable = false;

		PixelShader = compile ps_2_0 PS_NegaPosi();
	}
}
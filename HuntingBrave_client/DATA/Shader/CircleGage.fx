
//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------

float3	center = float3( 0.0f, 0.0f, 0.0f );	//	�摜�̒��S
float		radian = 0.0f;	//	�p�x( -PI ~ PI )
float		shadow = 0.5f;	//	�e�̔���

//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------

//	����
float4 PS_CircleShadow( VS_2D In, float2 pPos : VPOS ) : COLOR
{
	//	�o��
	float4	OUT;

	//	�s�N�Z���F����
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	//	�p�x���擾
	float r = atan2( pPos.x - center.x, pPos.y - center.y );

	//	�ݒ肵���p�x�ȏ�̓_���Â�����( y���������Ȃ̂�-r )
	if ( -r > radian ) OUT.rgb *= shadow;

	return OUT;
}

//------------------------------------------------------
//		�e�N�j�b�N
//------------------------------------------------------

//	����
technique circleShadow
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = None;
		ZEnable = false;

		PixelShader = compile ps_3_0 PS_CircleShadow();
	}
}
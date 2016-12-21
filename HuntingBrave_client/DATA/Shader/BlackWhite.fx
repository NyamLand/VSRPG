//------------------------------------------------------
//		�s�N�Z���V�F�[�_�[	
//------------------------------------------------------

	//	����
	float4 PS_BlackWhite( VS_2D In ) : COLOR
	{
		//	�o��
		float4	OUT;

		//	�s�N�Z���F����
		OUT = In.Color * tex2D( DecaleSamp, In.Tex );

		//	������
		OUT.rgb = ( OUT.r + OUT.g + OUT.b ) * 0.3333f;

		return OUT;
	}

//------------------------------------------------------
//		�e�N�j�b�N
//------------------------------------------------------

	//	����
	technique blackWhite
	{
		pass P0
		{
			AlphaBlendEnable = true;
			BlendOp = Add;
			SrcBlend = SrcAlpha;
			DestBlend = InvSrcAlpha;
			CullMode = None;
			ZEnable = false;

			PixelShader = compile ps_2_0 PS_BlackWhite();
		}
	}
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

	//	�O���ݒ�p
	float	percentage = 0.0f;

	float4	PS_BlackWhiteOutSet( VS_2D In ) : COLOR
	{
		//	�o��
		float4	OUT;

		//	�s�N�Z���F����
		OUT = In.Color * tex2D( DecaleSamp, In.Tex );

		//	������
		float3 start = float3( OUT.r, OUT.g, OUT.b );
		float3 end = ( OUT.r + OUT.g + OUT.b ) * 0.333f;
		float3 sub = start - end;

		OUT.rgb = start - ( sub * percentage );

		return	OUT;
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

	//	����(�O���ݒ�)
	technique blackWhiteOutSet
	{
		pass P0
		{
			AlphaBlendEnable = true;
			BlendOp = Add;
			SrcBlend = SrcAlpha;
			DestBlend = InvSrcAlpha;
			CullMode = None;
			ZEnable = false;

			PixelShader = compile ps_2_0 PS_BlackWhiteOutSet();
		}
	}
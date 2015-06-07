// globals
float4x4	gWVP;
float4		cola;
float4		gCol;
texture		tex1;

sampler TexS = sampler_state
{
	Texture = <tex1>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
// texture address modes (WRAP, MIRROR, BORDER, and CLAMP)
	AddressU  = WRAP;
	AddressV  = WRAP;
};

// Define a vertex shader output structure;
struct OutputVS
{
    float4 posH:POSITION0;
    float4 color:COLOR0;
    float2 tex0:TEXCOORD0;
};



// Vertex shader -------------------------------------------------------------------------------------
OutputVS TransformVS(float3 position:POSITION0, float4 col:COLOR0, float2 uv0:TEXCOORD0)
{
	// output structure
	OutputVS outVS;
	
	outVS.posH = mul(float4(position, 1.0f), gWVP);	
	outVS.color = cola;
	outVS.tex0 = uv0;
	
    return outVS;
}



// random color Pixel Shader ---------------------------------------------------------------------------
float4 TransformPS(OutputVS outVS):COLOR
{
	
	float4 texcolor = tex2D(TexS,outVS.tex0);
	//float4 texcolor = tex1.Sample(TexS,outVS.tex0);	

    return texcolor;
}


technique Multi
{
    pass P0
    {
        vertexShader = compile vs_2_0 TransformVS();
        pixelShader  = compile ps_2_0 TransformPS();
      
		ShadeMode = Flat;
        //FillMode = Wireframe;
        //CullMode = NONE;
    }
}

technique Basic
{
    pass P0
	{
        vertexShader = compile vs_2_0 TransformVS();
        pixelShader = compile ps_2_0 TransformPS();

		ShadeMode = Flat;
    }

}
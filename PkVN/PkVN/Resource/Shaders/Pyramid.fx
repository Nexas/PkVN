// globals
float4x4	gWVP;
float4		cola;
float4		gCol;
	
// Define a vertex shader output structure;
struct OutputVS
{
    float4 posH:POSITION0;
    float4 color:COLOR0;
};

// Vertex shader -------------------------------------------------------------------------------------
OutputVS TransformVS(float3 position:POSITION0, float4 col:COLOR0)
{
	// output structure
	OutputVS outVS;
	
	outVS.posH = mul(float4(position, 1.0f), gWVP);	
	outVS.color = cola;
	
    return outVS;
}

// random color Pixel Shader ---------------------------------------------------------------------------
float4 TransformPS(float4 c:COLOR0):COLOR
{
	//return c;
    return float4(cola);
}

// ----------------------------------------------------------------------------------------
float4 NormalPS(float4 c:COLOR0):COLOR
{
	return gCol;
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
        pixelShader = compile ps_2_0 NormalPS();

		ShadeMode = Flat;
    }

}
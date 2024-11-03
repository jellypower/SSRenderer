

cbuffer cbNeverChanges : register(b0)
{
    matrix WVPTransform; // cbNeverChanges -> ���� ������ �ʴ� �ܽ�źƮ ���۶�� ��
};

cbuffer cbChangesEveryFrame : register(b1)
{
    float4 vMeshColor; // �� ������ ��ȭ�� ��
};

cbuffer cbLighSettings : register(b2)
{
    float4 vLightDir[8];
    float4 vLightColor[8];
    
};


struct VS_INPUT
{
    float4 Pos : POSITION;
    float4 Nor : NORMAL;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Nor : TEXCOORD7;
    // TEXCOORD �ø�ƽ�� �ؽ��� ��ǥ �� �ƴ϶� ���е� �ִ� float���� ���ڸ� ������ ���� ���� ��
    // -> Normal ���� ��쿡�� ������ Semantics�� ���� ������ �����
};

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.Pos = mul(input.Pos, WVPTransform);
    output.Nor = mul(input.Nor, WVPTransform);
    
    return output;
}


float4 PS(PS_INPUT input) : SV_Target
{
    float4 color = input.Nor;
    return color;
    
}

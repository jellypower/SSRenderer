

cbuffer cbNeverChanges : register(b0)
{
    matrix WVPTransform; // cbNeverChanges -> 절대 변하지 않는 콘스탄트 버퍼라는 뜻
};

cbuffer cbChangesEveryFrame : register(b1)
{
    float4 vMeshColor; // 매 프레임 변화는 색
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
    // TEXCOORD 시멘틱은 텍스쳐 좌표 뿐 아니라 정밀도 있는 float단위 숫자를 전달할 때도 많이 씀
    // -> Normal 같은 경우에도 별도의 Semantics가 없기 때문에 사용함
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

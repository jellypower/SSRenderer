#include "SSStaticMath.h"


XMMATRIX SS::InverseRigid(XMMATRIX InMatrix)
{
	XMMATRIX InverseRigid;
	InverseRigid.r[0].m128_f32[0] = InMatrix.r[0].m128_f32[0];
	InverseRigid.r[0].m128_f32[1] = InMatrix.r[1].m128_f32[0];
	InverseRigid.r[0].m128_f32[2] = InMatrix.r[2].m128_f32[0];
	InverseRigid.r[0].m128_f32[3] = 0;
	InverseRigid.r[1].m128_f32[0] = InMatrix.r[0].m128_f32[1];
	InverseRigid.r[1].m128_f32[1] = InMatrix.r[1].m128_f32[1];
	InverseRigid.r[1].m128_f32[2] = InMatrix.r[2].m128_f32[1];
	InverseRigid.r[1].m128_f32[3] = 0;
	InverseRigid.r[2].m128_f32[0] = InMatrix.r[0].m128_f32[2];
	InverseRigid.r[2].m128_f32[1] = InMatrix.r[1].m128_f32[2];
	InverseRigid.r[2].m128_f32[2] = InMatrix.r[2].m128_f32[2];
	InverseRigid.r[2].m128_f32[3] = 0;
	InverseRigid.r[3] = { 0,0,0,1 };


	XMVECTOR translation = InMatrix.r[3];
	translation = XMVector4Transform(translation, InverseRigid);
	InverseRigid.r[3].m128_f32[0] = -translation.m128_f32[0];
	InverseRigid.r[3].m128_f32[1] = -translation.m128_f32[1];
	InverseRigid.r[3].m128_f32[2] = -translation.m128_f32[2];
	InverseRigid.r[3].m128_f32[3] = 1;

	return InverseRigid;
}

Quaternion SS::Slerp(Quaternion lhs, Quaternion rhs, float alpha)
{
	return Quaternion(XMQuaternionSlerp(lhs.SimdVec, rhs.SimdVec, alpha));
}

Vector4f SS::Lerp(Vector4f lhs, Vector4f rhs, float alpha)
{
	return (rhs.SimdVec - lhs.SimdVec) * alpha + rhs.SimdVec;
}

Transform SS::Lerp(Transform lhs, Transform rhs, float alpha)
{
	return Transform(
		Lerp(lhs.Position, rhs.Position, alpha),
		Slerp(lhs.Rotation, rhs.Rotation, alpha),
		Lerp(lhs.Scale, rhs.Scale, alpha));
}

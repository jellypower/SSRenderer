#include "SSVector.h"
#include "SSStaticMath.h"

Vector4f const Vector4f::Forward = Vector4f(0, 0, 1, 0);
Vector4f const Vector4f::Back = Vector4f(0, 0, -1, 0);
Vector4f const Vector4f::Up = Vector4f(0, 1, 0, 0);
Vector4f const  Vector4f::Down = Vector4f(0, -1, 0, 0);
Vector4f const Vector4f::Left = Vector4f(-1, 0, 0, 0);
Vector4f const Vector4f::Right = Vector4f(1, 0, 0, 0);
Vector4f const Vector4f::Zero = Vector4f(0, 0, 0, 0);
Vector4f const Vector4f::One = Vector4f(1, 1, 1, 1);
Vector4f const Vector4f::Half = Vector4f(.5f, .5f, .5f, .5f);

Vector2i32 const Vector2i32::Zero = Vector2i32(0, 0);

Vector2f const Vector2f::Zero = Vector2f(0, 0);
Vector2f const Vector2f::One = Vector2f(1, 1);

Transform const Transform::Identity = Transform();


Vector4f::Vector4f()
	: SimdVec({ 0 })
{ }

Vector4f::Vector4f(XMVECTOR InXMVECTOR)
	: SimdVec(InXMVECTOR)
{ }

Vector4f::Vector4f(float InX, float InY, float InZ, float InW)
	: X(InX), Y(InY), Z(InZ), W(InW)
{ }

Vector4f Vector4f::Rotate(Quaternion Rotation) const
{
	return XMVector3Rotate(SimdVec, Rotation.SimdVec);
}


Vector2i32::Vector2i32()
	: X(0), Y(0)
{
}

Vector2i32::Vector2i32(int32 InX, int32 InY)
	: X(InX), Y(InY)
{
}

Vector2ui32::Vector2ui32()
	: X(0), Y(0)
{
}

Vector2ui32::Vector2ui32(uint32 InX, uint32 InY)
	: X(InX), Y(InY)
{
}

Transform::Transform()
	: Position(), Rotation(), Scale(1, 1, 1, 0)
{
}

Transform::Transform(Vector4f InPos, Quaternion InRot, Vector4f InScale)
	: Position(InPos), Rotation(InRot), Scale(InScale)
{
}


XMMATRIX Transform::AsMatrix() const
{
	return
		XMMatrixAffineTransformation(
			Scale.SimdVec,		// 스케일
			{ 0 },	// 피벗
			Rotation.SimdVec,	// 회전
			Position.SimdVec	// 위치
		);
}

XMMATRIX Transform::AsInverseMatrix() const
{
	XMMATRIX MScaling = XMMatrixScalingFromVector(Scale.SimdVec);

	XMMATRIX M = XMMatrixRotationQuaternion(Rotation.SimdVec);
	M.r[3] = XMVectorAdd(M.r[3], Position.SimdVec);
	M = SS::InverseRigid(M);
	M = XMMatrixMultiply(M, MScaling);
	return M;
}

Transform Transform::Inverse() const
{
	Transform inverse = Transform::Identity;
	const Quaternion InverseRot = Rotation.Inverse();
	const Vector4f InverseScale = Vector4f(1 / Scale.X, 1 / Scale.Y, 1 / Scale.Z, 0);

	inverse.Position = (-Position).Rotate(InverseRot) * InverseScale;
	inverse.Rotation = InverseRot;
	inverse.Scale = InverseScale;

	return inverse;
}

Transform Transform::operator*(const Transform& other) const
{
	Transform Result = Transform::Identity;

	Result.Rotation = Rotation * other.Rotation;
	Result.Scale = Scale * other.Scale;
	Result.Position = (Position * other.Scale).Rotate(other.Rotation) + other.Position;

	return Result;
}

Vector2f::Vector2f()
	: X(0), Y(0)
{
}

Vector2f::Vector2f(float InX, float InY)
	: X(InX), Y(InY)
{
}

float Vector2f::GetSqrLength() const
{
	return (X * X) + (Y * Y);
}

Quaternion::Quaternion()
	: X(0), Y(0), Z(0), W(1)
{
}

Quaternion::Quaternion(__m128 InSimdVector)
	: SimdVec(InSimdVector)
{
}

Quaternion Quaternion::Inverse() const
{
	return Quaternion(XMQuaternionInverse(SimdVec));
}



Quaternion Quaternion::FromEulerRotation(Vector4f eulerRotation)
{
	//	<Pitch, Yaw, Roll, 0>
	return XMQuaternionRotationRollPitchYawFromVector(eulerRotation.SimdVec);
}

Quaternion Quaternion::FromLookDirect(Vector4f lookDirection, Vector4f upDirection)
{
	return XMQuaternionRotationMatrix(
		XMMatrixLookToLH(Vector4f::Zero.SimdVec, lookDirection.SimdVec, upDirection.SimdVec));
}

Quaternion Quaternion::RotateAxisAngle(Quaternion CurRotation, Vector4f Axis, float angle)
{
	return XMQuaternionMultiply(CurRotation.SimdVec, XMQuaternionRotationAxis(Axis.SimdVec, angle));
}


Matrix3x3 Matrix4x4::getMatrix3x3()
{
	return Matrix3x3(
		c0r0, c1r0, c2r0,
		c0r1, c1r1, c2r1,
		c0r2, c1r2, c2r2);
}

Matrix4x4 Matrix4x4::scale(const Vector3& scale)
{
	return Matrix4x4(Matrix3x3::scale(scale));
}

Matrix4x4 Matrix4x4::rotate(const Vector3& eulerAngles)
{
	return Matrix4x4(Matrix3x3::rotate(eulerAngles));
}

Matrix4x4 Matrix4x4::rotate(float degreesX, float degreesY, float degreesZ)
{
	return Matrix4x4(Matrix3x3::rotate(degreesX, degreesY, degreesZ));
}

Matrix4x4 Matrix4x4::translate(const Vector3& translation)
{
	return Matrix4x4(
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1);
}

Matrix4x4 Matrix4x4::translate(const Vector4& translation)
{
	return Matrix4x4(
		1, 0, 0, translation.x,
		0, 1, 0, translation.y,
		0, 0, 1, translation.z,
		0, 0, 0, 1);
}


//The difference between Matrix3x3::lookAt() and Matrix4x4::lookAt() is that Matrix4x4 applies a transformation to negate the camera's position
Matrix4x4 Matrix4x4::lookAt(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up)
{
	Matrix3x3 lookAt3 = Matrix3x3::lookAt(position, target, up);
	Matrix4x4 translation;
	translation = Matrix4x4::translate(-1.0f * position);

	//The transformation gets applied first, and then the rotation. So the rotation is put on the left
	return Matrix4x4(lookAt3) * translation;
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspectRatio, float zNear, float zFar)
{
	return Matrix4x4(
		1.0f / (aspectRatio * tan(fov / 2.0f)), 0, 0, 0,
		0, 1.0f / tan(fov / 2.0f), 0, 0,
		0, 0, (-zNear - zFar) / (zFar - zNear), (-2.0f * zFar * zNear) / (zFar - zNear),
		0, 0, -1, 0);
}

Matrix4x4 operator+(const Matrix4x4& left, const Matrix4x4& right)
{
	return Matrix4x4(
		left.c0r0 + right.c0r0, left.c1r0 + right.c1r0, left.c2r0 + right.c2r0, left.c3r0 + right.c3r0,
		left.c0r1 + right.c0r1, left.c1r1 + right.c1r1, left.c2r1 + right.c2r1, left.c3r1 + right.c3r1,
		left.c0r2 + right.c0r2, left.c1r2 + right.c1r2, left.c2r2 + right.c2r2, left.c3r2 + right.c3r2,
		left.c0r3 + right.c0r3, left.c1r3 + right.c1r3, left.c2r3 + right.c2r3, left.c3r3 + right.c3r3);
}

Matrix4x4 operator-(const Matrix4x4& left, const Matrix4x4& right)
{
	return Matrix4x4(
		left.c0r0 - right.c0r0, left.c1r0 - right.c1r0, left.c2r0 - right.c2r0, left.c3r0 - right.c3r0,
		left.c0r1 - right.c0r1, left.c1r1 - right.c1r1, left.c2r1 - right.c2r1, left.c3r1 - right.c3r1,
		left.c0r2 - right.c0r2, left.c1r2 - right.c1r2, left.c2r2 - right.c2r2, left.c3r2 - right.c3r2,
		left.c0r3 - right.c0r3, left.c1r3 - right.c1r3, left.c2r3 - right.c2r3, left.c3r3 - right.c3r3);
}

Vector4 operator*(const Matrix4x4& op, const Vector4& vec)
{
	return Vector4(
		vec.x * op.c0r0 + vec.y * op.c1r0 + vec.z * op.c2r0 + vec.w * op.c3r0,
		vec.x * op.c0r1 + vec.y * op.c1r1 + vec.z * op.c2r1 + vec.w * op.c3r1,
		vec.x * op.c0r2 + vec.y * op.c1r2 + vec.z * op.c2r2 + vec.w * op.c3r2,
		vec.x * op.c0r3 + vec.y * op.c1r3 + vec.z * op.c2r3 + vec.w * op.c3r3);
}

Matrix4x4 operator*(float op, const Matrix4x4& matrix)
{
	return Matrix4x4(
		op * matrix.c0r0, op * matrix.c1r0, op * matrix.c2r0, op * matrix.c3r0,
		op * matrix.c0r1, op * matrix.c1r1, op * matrix.c2r1, op * matrix.c3r1,
		op * matrix.c0r2, op * matrix.c1r2, op * matrix.c2r2, op * matrix.c3r2,
		op * matrix.c0r3, op * matrix.c1r3, op * matrix.c2r3, op * matrix.c3r3);
}

Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right)
{
	Matrix4x4 ret;
	ret = Matrix4x4(
		left.c0r0 * right.c0r0 + left.c1r0 * right.c0r1 + left.c2r0 * right.c0r2 + left.c3r0 * right.c0r3,
		left.c0r0 * right.c1r0 + left.c1r0 * right.c1r1 + left.c2r0 * right.c1r2 + left.c3r0 * right.c1r3,
		left.c0r0 * right.c2r0 + left.c1r0 * right.c2r1 + left.c2r0 * right.c2r2 + left.c3r0 * right.c2r3,
		left.c0r0 * right.c3r0 + left.c1r0 * right.c3r1 + left.c2r0 * right.c3r2 + left.c3r0 * right.c3r3,

		left.c0r1 * right.c0r0 + left.c1r1 * right.c0r1 + left.c2r1 * right.c0r2 + left.c3r1 * right.c0r3,
		left.c0r1 * right.c1r0 + left.c1r1 * right.c1r1 + left.c2r1 * right.c1r2 + left.c3r1 * right.c1r3,
		left.c0r1 * right.c2r0 + left.c1r1 * right.c2r1 + left.c2r1 * right.c2r2 + left.c3r1 * right.c2r3,
		left.c0r1 * right.c3r0 + left.c1r1 * right.c3r1 + left.c2r1 * right.c3r2 + left.c3r1 * right.c3r3,

		left.c0r2 * right.c0r0 + left.c1r2 * right.c0r1 + left.c2r2 * right.c0r2 + left.c3r2 * right.c0r3,
		left.c0r2 * right.c1r0 + left.c1r2 * right.c1r1 + left.c2r2 * right.c1r2 + left.c3r2 * right.c1r3,
		left.c0r2 * right.c2r0 + left.c1r2 * right.c2r1 + left.c2r2 * right.c2r2 + left.c3r2 * right.c2r3,
		left.c0r2 * right.c3r0 + left.c1r2 * right.c3r1 + left.c2r2 * right.c3r2 + left.c3r2 * right.c3r3,

		left.c0r3 * right.c0r0 + left.c1r3 * right.c0r1 + left.c2r3 * right.c0r2 + left.c3r3 * right.c0r3,
		left.c0r3 * right.c1r0 + left.c1r3 * right.c1r1 + left.c2r3 * right.c1r2 + left.c3r3 * right.c1r3,
		left.c0r3 * right.c2r0 + left.c1r3 * right.c2r1 + left.c2r3 * right.c2r2 + left.c3r3 * right.c2r3,
		left.c0r3 * right.c3r0 + left.c1r3 * right.c3r1 + left.c2r3 * right.c3r2 + left.c3r3 * right.c3r3);
	return ret;
}
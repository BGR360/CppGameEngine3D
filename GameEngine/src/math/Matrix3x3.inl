Matrix2x2 Matrix3x3::getMatrix2x2()
{
	return Matrix2x2(
		c0r0, c1r0,
		c0r1, c1r1);
}

Matrix3x3 Matrix3x3::adjugate(const Matrix3x3& matrix)
{
	return Matrix3x3::transpose(Matrix3x3::cofactor(matrix));
}

Matrix3x3 Matrix3x3::cofactor(const Matrix3x3& matrix)
{
	return Matrix3x3(
		matrix.c1r1 * matrix.c2r2 - matrix.c2r1 * matrix.c1r2,
		-1 * (matrix.c0r1 * matrix.c2r2 - matrix.c2r1 * matrix.c0r2),
		matrix.c0r1 * matrix.c1r2 - matrix.c1r1 * matrix.c0r2,

		-1 * (matrix.c1r0 * matrix.c2r2 - matrix.c2r0 * matrix.c1r2),
		matrix.c0r0 * matrix.c2r2 - matrix.c2r0 * matrix.c0r2,
		-1 * (matrix.c0r0 * matrix.c1r2 - matrix.c1r0 * matrix.c0r2),

		matrix.c1r0 * matrix.c2r1 - matrix.c2r0 * matrix.c1r1,
		-1 * (matrix.c0r0 * matrix.c2r1 - matrix.c2r0 * matrix.c0r1),
		matrix.c0r0 * matrix.c1r1 - matrix.c1r0 * matrix.c0r1);
}


float Matrix3x3::determinant(const Matrix3x3& matrix)
{
	return matrix.c0r0 * matrix.c1r1 * matrix.c2r2
		+ matrix.c1r0 * matrix.c2r1 * matrix.c0r2
		+ matrix.c2r0 * matrix.c0r1 * matrix.c1r2
		- matrix.c2r0 * matrix.c1r1 * matrix.c0r2
		- matrix.c0r0 * matrix.c2r1 * matrix.c1r2
		- matrix.c1r0 * matrix.c0r1 * matrix.c2r2;
}

Matrix3x3 Matrix3x3::inverse(const Matrix3x3& matrix)
{
	return (1.0f / Matrix3x3::determinant(matrix)) * Matrix3x3::adjugate(matrix);
}

Matrix3x3 Matrix3x3::tilde(const Vector3& vec)
{
	return Matrix3x3(
		0, -vec.z, vec.y,
		vec.z, 0, -vec.x,
		-vec.y, vec.x, 0);
}

Matrix3x3 Matrix3x3::transpose(const Matrix3x3& matrix)
{
	return Matrix3x3(
		matrix.c0r0, matrix.c0r1, matrix.c0r2,
		matrix.c1r0, matrix.c1r1, matrix.c1r2,
		matrix.c2r0, matrix.c2r1, matrix.c2r2);
}

Matrix3x3 Matrix3x3::scale(const Vector3& scale)
{
	return Matrix3x3(
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, scale.z);
}

Matrix3x3 Matrix3x3::rotate(float angleDegrees, const Vector3& axis)
{
	Matrix3x3 I;
	float c = cos(toRadians(angleDegrees));
	float s = sin(toRadians(angleDegrees));
	float t = 1.0f - c;
	Vector3 a = Vector3::normalize(axis);
	Matrix3x3 tildeAxis = Matrix3x3::tilde(a);


	return I + s * tildeAxis + t * (tildeAxis * tildeAxis);
}

Matrix3x3 Matrix3x3::rotate(const Vector3& eulerAngles)
{
	return Matrix3x3::rotate(eulerAngles.x, eulerAngles.y, eulerAngles.z);
}

Matrix3x3 Matrix3x3::rotate(float degreesX, float degreesY, float degreesZ)
{
	Matrix3x3 rotateX = rotate(degreesX, Vector3(1, 0, 0));
	Matrix3x3 rotateY = rotate(degreesY, Vector3(0, 1, 0));
	Matrix3x3 rotateZ = rotate(degreesZ, Vector3(0, 0, 1));

	return rotateZ * rotateY * rotateX;
}

//Matrix3x3 Matrix3x3::rotateX(float thetaRadians)
//{
//	return Matrix3x3(
//		1, 0, 0,
//		0, cos(thetaRadians), -1 * sin(thetaRadians),
//		0, sin(thetaRadians), cos(thetaRadians));
//}
//
//Matrix3x3 Matrix3x3::rotateY(float thetaRadians)
//{
//	return Matrix3x3(
//		cos(thetaRadians), 0, sin(thetaRadians),
//		0, 1, 0,
//		-1 * sin(thetaRadians), 0, cos(thetaRadians));
//}
//
//Matrix3x3 Matrix3x3::rotateZ(float thetaRadians)
//{
//	return Matrix3x3(
//		cos(thetaRadians), -1 * sin(thetaRadians), 0,
//		sin(thetaRadians), cos(thetaRadians), 0,
//		0, 0, 1);
//}

Matrix3x3 Matrix3x3::translate(const Vector2& translation)
{
	return Matrix3x3(
		1, 0, translation.x,
		0, 1, translation.y,
		0, 0, 1);
}

Matrix3x3 Matrix3x3::translate(const Vector3& translation)
{
	return Matrix3x3(
		1, 0, translation.x,
		0, 1, translation.y,
		0, 0, 1);
}

Matrix3x3 Matrix3x3::lookAt(
	const Vector3& position,
	const Vector3& target,
	const Vector3& up)
{
	//N: lookAt vector
	Vector3 N = Vector3::normalize(target - position);
	//U: right vector
	Vector3 U = Vector3::normalize(Vector3::cross(N, up));
	//V: up vector
	Vector3 V = Vector3::cross(U, N);

	//Construct the matrix
	return Matrix3x3(
		U.x, U.y, U.z,
		V.x, V.y, V.z,
		-N.x, -N.y, -N.z);
}

Matrix3x3 operator+(const Matrix3x3& left, const Matrix3x3& right)
{
	return Matrix3x3(
		left.c0r0 + right.c0r0, left.c1r0 + right.c1r0, left.c2r0 + right.c2r0,
		left.c0r1 + right.c0r1, left.c1r1 + right.c1r1, left.c2r1 + right.c2r1,
		left.c0r2 + right.c0r2, left.c1r2 + right.c1r2, left.c2r2 + right.c2r2);
}

Matrix3x3 operator-(const Matrix3x3& left, const Matrix3x3& right)
{
	return Matrix3x3(
		left.c0r0 - right.c0r0, left.c1r0 - right.c1r0, left.c2r0 - right.c2r0,
		left.c0r1 - right.c0r1, left.c1r1 - right.c1r1, left.c2r1 - right.c2r1,
		left.c0r2 - right.c0r2, left.c1r2 - right.c1r2, left.c2r2 - right.c2r2);
}

Vector3 operator*(const Matrix3x3& op, const Vector3& vec)
{
	return Vector3(
		vec.x * op.c0r0 + vec.y * op.c1r0 + vec.z * op.c2r0,
		vec.x * op.c0r1 + vec.y * op.c1r1 + vec.z * op.c2r1,
		vec.x * op.c0r2 + vec.y * op.c1r2 + vec.z * op.c2r2);
}

Matrix3x3 operator*(float op, const Matrix3x3& matrix)
{
	return Matrix3x3(
		op * matrix.c0r0, op * matrix.c1r0, op * matrix.c2r0,
		op * matrix.c0r1, op * matrix.c1r1, op * matrix.c2r1,
		op * matrix.c0r2, op * matrix.c1r2, op * matrix.c2r2);
}

Matrix3x3 operator*(const Matrix3x3& left, const Matrix3x3& right)
{
	return Matrix3x3(
		left.c0r0 * right.c0r0 + left.c1r0 * right.c0r1 + left.c2r0 * right.c0r2,
		left.c0r0 * right.c1r0 + left.c1r0 * right.c1r1 + left.c2r0 * right.c1r2, 
		left.c0r0 * right.c2r0 + left.c1r0 * right.c2r1 + left.c2r0 * right.c2r2,
		
		left.c0r1 * right.c0r0 + left.c1r1 * right.c0r1 + left.c2r1 * right.c0r2,
		left.c0r1 * right.c1r0 + left.c1r1 * right.c1r1 + left.c2r1 * right.c1r2,
		left.c0r1 * right.c2r0 + left.c1r1 * right.c2r1 + left.c2r1 * right.c2r2, 
		
		left.c0r2 * right.c0r0 + left.c1r2 * right.c0r1 + left.c2r2 * right.c0r2,
		left.c0r2 * right.c1r0 + left.c1r2 * right.c1r1 + left.c2r2 * right.c1r2,
		left.c0r2 * right.c2r0 + left.c1r2 * right.c2r1 + left.c2r2 * right.c2r2);
}

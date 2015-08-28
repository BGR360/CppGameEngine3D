Matrix2x2 Matrix2x2::adjugate(const Matrix2x2& matrix)
{
	return Matrix2x2(
		matrix.c1r1			,	-1 * matrix.c1r0,
		-1 * matrix.c0r1	,	matrix.c0r0);
}

float Matrix2x2::determinant(const Matrix2x2& matrix)
{
	return matrix.c0r0 * matrix.c1r1 - matrix.c1r0 * matrix.c0r1;
}

Matrix2x2 Matrix2x2::inverse(const Matrix2x2& matrix)
{
	return (1.0f / Matrix2x2::determinant(matrix)) * Matrix2x2::adjugate(matrix);
}

Matrix2x2 Matrix2x2::transpose(const Matrix2x2& matrix)
{
	return Matrix2x2(
		matrix.c0r0, matrix.c0r1,
		matrix.c1r0, matrix.c1r1);
}

Matrix2x2 Matrix2x2::scale(const Vector2& scale)
{
	return Matrix2x2(
		scale.x, 0,
		0, scale.y);
}

Matrix2x2 Matrix2x2::rotate(float thetaDegrees)
{
	float thetaRadians = toRadians(thetaDegrees);
	return Matrix2x2(
		cos(thetaRadians), -1 * sin(thetaRadians),
		sin(thetaRadians), cos(thetaRadians));
}


Matrix2x2 operator+(const Matrix2x2& left, const Matrix2x2& right)
{
	return Matrix2x2(
		left.c0r0 + right.c0r0,		left.c1r0 + right.c1r0,
		left.c0r1 + right.c0r1,		left.c1r1 + right.c1r1);
}

Matrix2x2 operator-(const Matrix2x2& left, const Matrix2x2& right)
{
	return Matrix2x2(
		left.c0r0 - right.c0r0, left.c1r0 - right.c1r0,
		left.c0r1 - right.c0r1, left.c1r1 - right.c1r1);
}

Vector2 operator*(const Matrix2x2& op, const Vector2& vec)
{
	return Vector2(
		vec.x * op.c0r0 + vec.y * op.c1r0,
		vec.x * op.c0r1 + vec.y * op.c1r1);
}

Matrix2x2 operator*(float op, const Matrix2x2& matrix)
{
	return Matrix2x2(
		op * matrix.c0r0, op * matrix.c1r0,
		op * matrix.c0r1, op * matrix.c1r1);
}

Matrix2x2 operator*(const Matrix2x2& left, const Matrix2x2& right)
{
	return Matrix2x2(
		left.c0r0 * right.c0r0 + left.c1r0 * right.c0r1,	left.c0r0 * right.c1r0 + left.c1r0 * right.c1r1,
		
		left.c0r1 * right.c0r0 + left.c1r1 * right.c0r1,	left.c0r1 * right.c1r0 + left.c1r1 * right.c1r1);
}

float Vector2::magnitude() const
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const
{
	float mag = magnitude();
	return *this / mag;
}

Vector2 Vector2::normalize()
{
	float mag = magnitude();
	*this /= mag;
	return *this;
}

float Vector2::dot(const Vector2& left, const Vector2& right)
{
	return left.x * right.x + left.y * right.y;
}

Vector2 Vector2::normalize(Vector2& vec)
{
	return vec.normalize();
}

Vector2 Vector2::normalize(const Vector2& vec)
{
	return vec.normalized();
}

Vector2& Vector2::operator+=(const Vector2& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& right)
{
	x *= right.x;
	y *= right.y;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& right)
{
	x /= right.x;
	y /= right.y;
	return *this;
}

float& Vector2::operator[](const int nIndex)
{
	assert(nIndex >= 0 && nIndex < 2);

	if (nIndex == 0)
	{
		return x;
	}
	else if (nIndex == 1)
	{
		return y;
	}
}


Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x + rhs.x,
		lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x - rhs.x,
		lhs.y - rhs.y);
}

Vector2 operator*(float scalar, const Vector2& vector)
{
	return Vector2(
		scalar * vector.x,
		scalar * vector.y);
}

Vector2 operator*(const Vector2& vector, float scalar)
{
	return Vector2(
		scalar * vector.x,
		scalar * vector.y);
}

Vector2 operator*(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x * rhs.x,
		lhs.y * rhs.y);
}

Vector2 operator/(const Vector2& vector, float scalar)
{
	return Vector2(
		vector.x / scalar,
		vector.y / scalar);
}

Vector2 operator/(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(
		lhs.x / rhs.x,
		lhs.y / rhs.y);
}
float Vector4::magnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::normalized() const
{
	float mag = magnitude();
	return *this / mag;
}

Vector4 Vector4::normalize()
{
	float mag = magnitude();
	*this /= mag;
	return *this;
}

float Vector4::dot(const Vector4& left, const Vector4& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

Vector4 Vector4::normalize(Vector4& vec)
{
	return vec.normalize();
}

Vector4 Vector4::normalize(const Vector4& vec)
{
	return vec.normalized();
}

Vector4& Vector4::operator+=(const Vector4& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	w += right.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
	w -= right.w;
	return *this;
}

Vector4& Vector4::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector4& Vector4::operator*=(const Vector4& right)
{
	x *= right.x;
	y *= right.y;
	z *= right.z;
	w += right.w;
	return *this;
}

Vector4& Vector4::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4& Vector4::operator/=(const Vector4& right)
{
	x /= right.x;
	y /= right.y;
	z /= right.z;
	w /= right.w;
	return *this;
}

float& Vector4::operator[](const int nIndex)
{
	assert(nIndex >= 0 && nIndex < 4);

	if (nIndex == 0)
	{
		return x;
	}
	else if (nIndex == 1)
	{
		return y;
	}
	else if (nIndex == 2)
	{
		return z;
	}
	else if (nIndex == 3)
	{
		return w;
	}
}


Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(
		lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z,
		lhs.w + rhs.w);
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z,
		lhs.w - rhs.w);
}

Vector4 operator*(float scalar, const Vector4& vector)
{
	return Vector4(
		scalar * vector.x,
		scalar * vector.y,
		scalar * vector.z,
		scalar * vector.w);
}

Vector4 operator*(const Vector4& vector, float scalar)
{
	return scalar * vector;
}

Vector4 operator*(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(
		lhs.x * rhs.x,
		lhs.y * rhs.y,
		lhs.z * rhs.z,
		lhs.w * rhs.w);
}

Vector4 operator/(const Vector4& vector, float scalar)
{
	return Vector4(
		vector.x / scalar,
		vector.y / scalar,
		vector.z / scalar,
		vector.w / scalar);
}

Vector4 operator/(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(
		lhs.x / rhs.x,
		lhs.y / rhs.y,
		lhs.z / rhs.z,
		lhs.w / rhs.w);
}
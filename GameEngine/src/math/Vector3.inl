float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() const
{
	float mag = magnitude();
	return *this / mag;
}

Vector3 Vector3::normalize()
{
	float mag = magnitude();
	*this /= mag;
	return *this;
}

float Vector3::dot(const Vector3& left, const Vector3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3 Vector3::cross(const Vector3& left, const Vector3& right)
{
	return Vector3(
		left.y * right.z - right.y * left.z,
		-1 * (left.x * right.z - right.x * left.z),
		left.x * right.y - right.x * left.y);
}

Vector3 Vector3::normalize(Vector3& vec)
{
	return vec.normalize();
}

Vector3 Vector3::normalize(const Vector3& vec)
{
	return vec.normalized();
}

Vector3& Vector3::operator+=(const Vector3& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
	return *this;
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& right)
{
	x *= right.x;
	y *= right.y;
	z *= right.z;
	return *this;
}

Vector3& Vector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& right)
{
	x /= right.x;
	y /= right.y;
	z /= right.z;
	return *this;
}

float& Vector3::operator[](const int nIndex)
{
	assert(nIndex >= 0 && nIndex < 3);

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
}


Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z);
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z);
}

Vector3 operator*(float scalar, const Vector3& vector)
{
	return Vector3(
		scalar * vector.x,
		scalar * vector.y,
		scalar * vector.z);
}

Vector3 operator*(const Vector3& vector, float scalar)
{
	return Vector3(
		scalar * vector.x,
		scalar * vector.y,
		scalar * vector.z);
}

Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.x * rhs.x,
		lhs.y * rhs.y,
		lhs.z * rhs.z);
}

Vector3 operator/(const Vector3& vector, float scalar)
{
	return Vector3(
		vector.x / scalar,
		vector.y / scalar,
		vector.z / scalar);
}

Vector3 operator/(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.x / rhs.x,
		lhs.y / rhs.y,
		lhs.z / rhs.z);
}
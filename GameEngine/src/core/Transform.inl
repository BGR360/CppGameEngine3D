Vector3& Transform::getPosition()
{
	return m_position;
}

Vector3& Transform::getRotation()
{
	return m_rotation;
}

Vector3& Transform::getScale()
{
	return m_scale;
}

Vector3 Transform::getPosition() const
{
	return m_position;
}

Vector3 Transform::getRotation() const
{
	return m_rotation;
}

Vector3 Transform::getScale() const
{
	return m_scale;
}

Transform* Transform::getParent() const
{
	return m_parent;
}

GameObject* Transform::getGameObject() const
{
	return m_gameObject;
}

Matrix4x4 Transform::toModelMatrix() const
{
	Matrix4x4 mine = Matrix4x4::translate(m_position) * Matrix4x4::rotate(m_rotation) * Matrix4x4::scale(m_scale);

	if (m_parent == 0)
	{
		return mine;
	}
	else
	{
		//return m_parent->toModelMatrix() * mine;
		return mine;
	}
}

void Transform::setPosition(const Vector3& position)
{
	m_position = position;
}

void Transform::setRotation(const Vector3& rotation)
{
	m_rotation = rotation;
}

void Transform::setScale(const Vector3& scale)
{
	m_scale = scale;
}

void Transform::setParent(Transform* parent)
{
	m_parent = parent;
}

void Transform::clearParent()
{
	m_parent = 0;
}

void Transform::attachToGameObject(GameObject* gameObject)
{
	m_gameObject = gameObject;
}
Vector3 Camera::getPosition() const
{
	return m_position;
}

Vector3& Camera::getPosition()
{
	return m_position;
}

Vector3 Camera::getForward() const
{
	return m_forward;
}

Vector3& Camera::getForward()
{
	return m_forward;
}

Vector3 Camera::getUp() const
{
	return m_up;
}

Vector3& Camera::getUp()
{
	return m_up;
}

float Camera::getFov() const
{
	return m_fov;
}

float& Camera::getFov()
{
	return m_fov;
}

float Camera::getAspectRatio() const
{
	return m_aspectRatio;
}

float& Camera::getAspectRatio()
{
	return m_aspectRatio;
}

float Camera::getNear() const
{
	return m_zNear;
}

float& Camera::getNear()
{
	return m_zNear;
}

float Camera::getFar() const
{
	return m_zFar;
}

float& Camera::getFar()
{
	return m_zFar;
}

Vector3 Camera::getTarget() const
{
	return m_position + m_forward;
}

Vector3 Camera::getRight() const
{
	return Vector3::cross(this->getForward(), m_up);
}

void Camera::setPosition(const Vector3& pos)
{
	m_position = pos;
}

void Camera::setTarget(const Vector3& target)
{
	m_forward = target - m_position;
}

void Camera::setViewDirection(const Vector3& direction)
{
	m_forward = direction;
}

void Camera::setUp(const Vector3& up)
{
	m_up = up;
}

void Camera::setFov(float fov)
{
	m_fov = fov;
}

void Camera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}

void Camera::setNear(float zNear)
{
	m_zNear = zNear;
}

void Camera::setFar(float zFar)
{
	m_zFar = zFar;
}

void Camera::rotateX(float angle)
{
	Matrix3x3 rotateM = Matrix3x3::rotate(angle, this->getRight());

	Vector3 newForward = rotateM * m_forward;
	m_forward = newForward;
}

void Camera::rotateY(float angle)
{
	Matrix3x3 rotateM = Matrix3x3::rotate(angle, m_up);

	Vector3 newForward = rotateM * m_forward;
	m_forward = newForward;
}

Matrix4x4 Camera::toViewMatrix() const
{
	return Matrix4x4::lookAt(m_position, m_position + m_forward, m_up);
}

Matrix4x4 Camera::toProjectionMatrix() const
{
	return Matrix4x4::perspective(m_fov, m_aspectRatio, m_zNear, m_zFar);
}

Matrix4x4 Camera::toViewProjectionMatrix() const
{
	return this->toProjectionMatrix() * this->toViewMatrix();
}
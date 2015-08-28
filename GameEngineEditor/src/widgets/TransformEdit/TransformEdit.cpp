#include "TransformEdit.h"

#include <qt/QtGui/qfont.h>

const QString TransformEdit::styleSheet =
"QGroupBox"
"{"
"	font-size: 14px;"
"}";

TransformEdit::TransformEdit(Transform* trans, QWidget * parent) 
	: QGroupBox("Transform", parent)
{
	setTransform(trans);

	setStyleSheet(styleSheet);

	setLayout(m_mainLayout = new QVBoxLayout);
	m_mainLayout->addWidget(m_positionEdit = new Vector3Edit("Position"));
	m_mainLayout->addWidget(m_rotationEdit = new Vector3Edit("Rotation"));
	m_mainLayout->addWidget(m_scaleEdit = new Vector3Edit("Scale"));
	m_mainLayout->setContentsMargins(QMargins(5, 5, 5, 5));
	m_mainLayout->setSpacing(2);

	m_positionEdit->setRange(-10.0f, 10.0f);
	m_rotationEdit->setRange(-360.0f, 360.0f);
	m_scaleEdit->setRange(-4.0f, 6.0f);

	m_positionEdit->setGranularity(250);
	m_rotationEdit->setGranularity(250);
	m_scaleEdit->setGranularity(250);

	connect(m_positionEdit, SIGNAL(valueChanged(Vector3)), this, SLOT(setPosition(Vector3)));
	connect(m_rotationEdit, SIGNAL(valueChanged(Vector3)), this, SLOT(setRotation(Vector3)));
	connect(m_scaleEdit, SIGNAL(valueChanged(Vector3)), this, SLOT(setScale(Vector3)));
}

void TransformEdit::setTransform(Transform* trans)
{
	m_transform = trans;

	if (trans != 0)
	{
		m_positionEdit->setValue(trans->getPosition());
		m_rotationEdit->setValue(trans->getRotation());
		m_scaleEdit->setValue(trans->getScale());
	}
}

void TransformEdit::setPosition(const Vector3& position)
{
	if (m_transform != 0)
	{
		m_transform->setPosition(position);
		emit transformChanged();
	}
}

void TransformEdit::setRotation(const Vector3& rotation)
{
	if (m_transform != 0)
	{
		m_transform->setRotation(rotation);
		emit transformChanged();
	}
}

void TransformEdit::setScale(const Vector3& scale)
{
	if (m_transform != 0)
	{
		m_transform->setScale(scale);
		emit transformChanged();
	}
}


Transform* TransformEdit::transform()
{
	return m_transform;
}

TransformEdit::~TransformEdit()
{

}
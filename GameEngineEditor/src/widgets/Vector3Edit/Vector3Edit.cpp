#include "Vector3Edit.h"

#include <qt/QtGui/qfont.h>

Vector3Edit::Vector3Edit(const QString& label, float min, float max, int gran, QWidget* parent) 
	: QWidget(parent),
	m_isReseting(false)
{
	setLayout(m_mainLayout = new QVBoxLayout);
	m_mainLayout->addWidget(m_label = new QLabel(label));
	QFont font = m_label->font();
	font.setPointSize(10);
	m_label->setFont(font);
	m_mainLayout->addLayout(m_vectorLayout = new QHBoxLayout);
	m_mainLayout->setContentsMargins(QMargins(1, 0, 1, 0));
	m_mainLayout->setSpacing(5);
	m_vectorLayout->addWidget(m_xEdit = new FloatBoxEdit);
	m_vectorLayout->addWidget(m_yEdit = new FloatBoxEdit);
	m_vectorLayout->addWidget(m_zEdit = new FloatBoxEdit);
	m_vectorLayout->setContentsMargins(QMargins(0, 0, 0, 0));
	m_vectorLayout->setSpacing(8);

	m_xEdit->setLabel("x:");
	m_yEdit->setLabel("y:");
	m_zEdit->setLabel("z:");

	setRange(min, max);
	setGranularity(gran);

	float startingValue = minimum() + (maximum() - minimum()) / 2;
	setValue(Vector3(startingValue, startingValue, startingValue));

	connect(m_xEdit, SIGNAL(valueChanged(float)), this, SLOT(notifyValueChanged()));
	connect(m_yEdit, SIGNAL(valueChanged(float)), this, SLOT(notifyValueChanged()));
	connect(m_zEdit, SIGNAL(valueChanged(float)), this, SLOT(notifyValueChanged()));
}

Vector3Edit::~Vector3Edit()
{

}



Vector3 Vector3Edit::value() const
{
	return Vector3(
		m_xEdit->value(),
		m_yEdit->value(),
		m_zEdit->value());
}

float Vector3Edit::minimum() const
{
	return m_xEdit->minimum();
}

float Vector3Edit::maximum() const
{
	return m_xEdit->maximum();
}

int Vector3Edit::granularity() const
{
	return m_xEdit->granularity();
}

QString Vector3Edit::label() const
{
	return m_label->text();
}

QString Vector3Edit::xLabel() const
{
	return m_xEdit->label();
}

QString Vector3Edit::yLabel() const
{
	return m_yEdit->label();
}

QString Vector3Edit::zLabel() const
{
	return m_zEdit->label();
}



void Vector3Edit::notifyValueChanged()
{
	if (!m_isReseting)
	{
		emit valueChanged(value());
	}
}



void Vector3Edit::setValue(const Vector3& val)
{
	m_isReseting = true;
	m_xEdit->setValue(val.x);
	m_yEdit->setValue(val.y);
	m_zEdit->setValue(val.z);
	m_isReseting = false;
}

void Vector3Edit::setMinimum(float min)
{
	m_xEdit->setMinimum(min);
	m_yEdit->setMinimum(min);
	m_zEdit->setMinimum(min);
}

void Vector3Edit::setMaximum(float max)
{
	m_xEdit->setMaximum(max);
	m_yEdit->setMaximum(max);
	m_zEdit->setMaximum(max);
}

void Vector3Edit::setRange(float min, float max)
{
	setMinimum(min);
	setMaximum(max);
}

void Vector3Edit::setGranularity(int gran)
{
	m_xEdit->setGranularity(gran);
	m_yEdit->setGranularity(gran);
	m_zEdit->setGranularity(gran);
}

void Vector3Edit::setLabel(const QString& label)
{
	m_label->setText(label);
}

void Vector3Edit::setxLabel(const QString& label)
{
	m_xEdit->setLabel(label);
}

void Vector3Edit::setyLabel(const QString& label)
{
	m_yEdit->setLabel(label);
}

void Vector3Edit::setzLabel(const QString& label)
{
	m_zEdit->setLabel(label);
}

void Vector3Edit::setComponentLabels(
	const QString& xLabel,
	const QString& yLabel,
	const QString& zLabel)
{
	setxLabel(xLabel);
	setyLabel(yLabel);
	setzLabel(zLabel);
}

void Vector3Edit::setLabels(
	const QString& mainLabel,
	const QString& xLabel,
	const QString& yLabel,
	const QString& zLabel)
{
	setLabel(mainLabel);
	setComponentLabels(xLabel, yLabel, zLabel);
}
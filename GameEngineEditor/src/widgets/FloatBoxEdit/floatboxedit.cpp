#include "floatboxedit.h"

FloatBoxEdit::FloatBoxEdit(const QString &label, float min, float max, int gran, QWidget *parent) :
    QWidget(parent)
{
    setLayout(m_mainLayout = new QVBoxLayout);
    m_mainLayout->addLayout(m_topLayout = new QHBoxLayout);
    m_mainLayout->addWidget(m_slider = new FloatingPointSlider);
	m_slider->setContentsMargins(QMargins(0, 0, 0, 0));
	m_mainLayout->setContentsMargins(QMargins(1, 1, 1, 1));
	m_mainLayout->setSpacing(1);
    m_topLayout->addWidget(m_label = new QLabel(label));
	m_label->setContentsMargins(QMargins(0, 0, 0, 0));
    m_topLayout->addWidget(m_lineEdit = new FloatingPointLineEdit);
	m_topLayout->setContentsMargins(QMargins(1, 1, 1, 0));
	m_topLayout->setSpacing(5);

	setContentsMargins(QMargins(0, 0, 0, 0));

    connect(m_lineEdit, SIGNAL(valueChanged(float)), m_slider, SLOT(setValue(float)));
    connect(m_slider, SIGNAL(valueChanged(float)), m_lineEdit, SLOT(setValue(float)));
    connect(m_slider, SIGNAL(valueChanged(float)), this, SIGNAL(valueChanged(float)));

    setRange(min, max);
    setGranularity(gran);
}

FloatBoxEdit::~FloatBoxEdit()
{

}

QSize FloatBoxEdit::sizeHint() const
{
	return QSize(72, 44);
}

float FloatBoxEdit::value() const
{
    return m_slider->value();
}

float FloatBoxEdit::minimum() const
{
    return m_slider->minimum();
}

float FloatBoxEdit::maximum() const
{
    return m_slider->maximum();
}

int FloatBoxEdit::granularity() const
{
    return m_slider->granularity();
}

QString FloatBoxEdit::label() const
{
    return m_label->text();
}

void FloatBoxEdit::setValue(float val)
{
    m_slider->setValue(val);
    m_lineEdit->setValue(val);
}

void FloatBoxEdit::setMinimum(float min)
{
    m_slider->setMinimum(min);
    m_lineEdit->setMinimum(min);
}

void FloatBoxEdit::setMaximum(float max)
{
    m_slider->setMaximum(max);
    m_lineEdit->setMaximum(max);
}

void FloatBoxEdit::setRange(float min, float max)
{
    setMinimum(min);
    setMaximum(max);
}

void FloatBoxEdit::setGranularity(int gran)
{
    m_slider->setGranularity(gran);
}

void FloatBoxEdit::setLabel(const QString &label)
{
    m_label->setText(label);
}
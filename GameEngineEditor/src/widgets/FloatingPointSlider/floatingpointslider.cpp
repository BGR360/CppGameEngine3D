#include "floatingpointslider.h"

FloatingPointSlider::FloatingPointSlider(Qt::Orientation orientation, float min, float max, int granularity, QWidget* parent) :
    QWidget(parent),
    m_mainLayout(new QVBoxLayout),
    m_slider(new QSlider(orientation, this)),
    m_min(min),
    m_max(max),
    m_granularity(granularity)
{
    Q_ASSERT(max >= min);
    Q_ASSERT(granularity > 0);

    m_mainLayout->addWidget(m_slider);
	m_mainLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    setLayout(m_mainLayout);
	
	m_slider->setMaximumHeight(m_slider->sizeHint().height() * HOW_MUCH_SMALLER);
	m_slider->setContentsMargins(QMargins(0, 0, 0, 0));

    m_slider->setMinimum(0);
    m_slider->setMaximum(granularity);

    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(notifyValueChanged()));
}


void FloatingPointSlider::notifyValueChanged()
{
    emit valueChanged(value());
}


//Calculates the value
float FloatingPointSlider::value() const
{
    return m_min + ((float)m_slider->value() / m_granularity) * (m_max - m_min);
}

float FloatingPointSlider::minimum() const
{
    return m_min;
}

float FloatingPointSlider::maximum() const
{
    return m_max;
}

int FloatingPointSlider::granularity() const
{
    return m_granularity;
}



void FloatingPointSlider::setMinimum(float min)
{
    m_min = min;
}

void FloatingPointSlider::setMaximum(float max)
{
    m_max = max;
}

void FloatingPointSlider::setRange(float min, float max)
{
    setMinimum(min);
    setMaximum(max);
}

void FloatingPointSlider::setGranularity(int gran)
{
    m_granularity = gran;
	m_slider->setMaximum(gran);
}

void FloatingPointSlider::setValue(float value)
{
    m_slider->setValue((int)(((value - m_min) / (m_max - m_min)) * m_granularity));
}



FloatingPointSlider::~FloatingPointSlider()
{

}

#include "floatingpointlineedit.h"

FloatingPointLineEdit::FloatingPointLineEdit(float min, float max, QWidget *parent) :
    QLineEdit(parent)
{
    setValidator(m_validator = new FloatValidator(this));
    setRange(min, max);

    connect(this, SIGNAL(returnPressed()), this, SLOT(notifyValueChanged()));
}

FloatingPointLineEdit::~FloatingPointLineEdit()
{

}

float FloatingPointLineEdit::value() const
{
    return m_validator->value(text());
}

float FloatingPointLineEdit::minimum() const
{
    return (float)m_validator->bottom();
}

float FloatingPointLineEdit::maximum() const
{
    return (float)m_validator->top();
}

int FloatingPointLineEdit::decimals() const
{
    return m_validator->decimals();
}


void FloatingPointLineEdit::notifyValueChanged()
{
    emit valueChanged(value());
}


void FloatingPointLineEdit::setValue(float val)
{
    setText(m_validator->locale().toString(val));
}

void FloatingPointLineEdit::setMinimum(float min)
{
    m_validator->setBottom(min);
}

void FloatingPointLineEdit::setMaximum(float max)
{
    m_validator->setTop(max);
}

void FloatingPointLineEdit::setRange(float min, float max)
{
    setMinimum(min);
    setMaximum(max);
}

void FloatingPointLineEdit::setDecimals(int dec)
{
    m_validator->setDecimals(dec);
}

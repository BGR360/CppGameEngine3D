#include "floatvalidator.h"

FloatValidator::FloatValidator(QObject *parent) : QDoubleValidator(parent)
{

}

FloatValidator::FloatValidator(float bottom, float top, int decimals, QObject *parent) :
    QDoubleValidator((double)bottom, (double)top, decimals, parent)
{

}

FloatValidator::~FloatValidator()
{

}

QValidator::State FloatValidator::validate(QString &input, int &pos) const
{
    State result = QDoubleValidator::validate(input, pos);

    if(result == State::Acceptable)
    {
        m_previousValue = value(input);
    }

    return result;
}

void FloatValidator::fixup(QString &input) const
{
    input = locale().toString(previousValue());
}

float FloatValidator::value(const QString &text) const
{
    float ret = locale().toFloat(text);
    return ret;
}

float FloatValidator::previousValue() const
{
    return m_previousValue;
}


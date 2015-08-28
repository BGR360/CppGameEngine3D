#ifndef FLOATVALIDATOR_H
#define FLOATVALIDATOR_H

#include <QtCore/qobject.h>
#include <QtGui/qvalidator.h>

class FloatValidator : public QDoubleValidator
{
    Q_OBJECT

public:
    FloatValidator(QObject * parent = 0);
    FloatValidator(float bottom, float top, int decimals, QObject * parent = 0);
    virtual ~FloatValidator();

    virtual State validate(QString & input, int & pos) const Q_DECL_OVERRIDE;
    virtual void fixup(QString & input) const Q_DECL_OVERRIDE;

    float value(const QString& text) const;

    float previousValue() const;

private:
    mutable float m_previousValue;
};

#endif // FLOATVALIDATOR_H

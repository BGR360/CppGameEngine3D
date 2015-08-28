#ifndef FLOATINGPOINTLINEEDIT_H
#define FLOATINGPOINTLINEEDIT_H

#include <QtGui/qevent.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlineedit.h>

#include "floatvalidator.h"

class FloatingPointLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    FloatingPointLineEdit(
        float min = -10000.0f,
        float max = 10000.0f,
        QWidget *parent = 0);
    virtual ~FloatingPointLineEdit();

    float value() const;
    float minimum() const;
    float maximum() const;
    int decimals() const;

signals:
    void valueChanged(float newValue);

protected slots:
    void notifyValueChanged();

public slots:
    void setValue(float val);

    void setMinimum(float min);
    void setMaximum(float max);
    void setRange(float min, float max);
    void setDecimals(int dec);

private:
    FloatValidator* m_validator;
};

#endif // FLOATINGPOINTLINEEDIT_H

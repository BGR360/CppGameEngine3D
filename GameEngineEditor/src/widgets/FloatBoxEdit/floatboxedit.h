#ifndef FLOATBOXEDIT_H
#define FLOATBOXEDIT_H

#include <QtCore/qstring.h>
#include <QtGui/qevent.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

#include <widgets/FloatingPointSlider/floatingpointslider.h>
#include <widgets/FloatingPointLineEdit/floatingpointlineedit.h>

class FloatBoxEdit : public QWidget
{
    Q_OBJECT

public:
    FloatBoxEdit(
            const QString& label = "Value:",
            float min = 0.0f,
            float max = 1.0f,
            int granularity = 40,
            QWidget *parent = 0);
    virtual ~FloatBoxEdit();

	virtual QSize sizeHint() const;

    float value() const;
    float minimum() const;
    float maximum() const;
    int granularity() const;
    QString label() const;

signals:
    void valueChanged(float newValue);

public slots:
    void setValue(float val);
    void setMinimum(float min);
    void setMaximum(float max);
    void setRange(float min, float max);
    void setGranularity(int gran);
    void setLabel(const QString& label);

private:
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_topLayout;
    QLabel* m_label;
    FloatingPointLineEdit* m_lineEdit;
    FloatingPointSlider* m_slider;
};

#endif // FLOATBOXEDIT_H

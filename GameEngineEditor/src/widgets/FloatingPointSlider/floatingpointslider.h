#ifndef FLOATINGPOINTSLIDER_H
#define FLOATINGPOINTSLIDER_H

#include <QtGui/qevent.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qslider.h>

class FloatingPointSlider : public QWidget
{
    Q_OBJECT

public:
    FloatingPointSlider(
        Qt::Orientation orientation = Qt::Orientation::Horizontal,
        float min = 0.0f,
        float max = 1.0f,
        int granularity = 40,
        QWidget* parent = 0);
    virtual ~FloatingPointSlider();

    //Calculates the value
    float value() const;

    float minimum() const;
    float maximum() const;
    int granularity() const;

signals:
    void valueChanged(float newValue);

protected slots:
    void notifyValueChanged();

public slots:
    void setValue(float val);

    void setMinimum(float min);
    void setMaximum(float max);
    void setRange(float min, float max);
    void setGranularity(int gran);

private:
    QVBoxLayout* m_mainLayout;

    float m_min;
    float m_max;
    int m_granularity;

	QSlider* m_slider;
	const double HOW_MUCH_SMALLER = (7.0 / 8.0);
};

#endif // FLOATINGPOINTSLIDER_H

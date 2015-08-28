#ifndef BENGINE_EDITOR_VECTOR3_EDIT_H
#define BENGINE_EDITOR_VECTOR3_EDIT_H

#include <qt/QtCore/qstring.h>
#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qlabel.h>

#include <widgets/FloatBoxEdit/floatboxedit.h>

#include <math/Vector3.h>
using Math::Vector3;

class Vector3Edit : public QWidget
{
	Q_OBJECT

public:
	Vector3Edit(
		const QString& label = "Vector:",
		float min = 0.0f,
		float max = 1.0f,
		int gran = 100,
		QWidget* parent = 0);
	virtual ~Vector3Edit();

	Vector3 value() const;
	float minimum() const;
	float maximum() const;
	int granularity() const;
	QString label() const;
	QString xLabel() const;
	QString yLabel() const;
	QString zLabel() const;

signals:
	void valueChanged(const Vector3& newValue);

protected slots:
	void notifyValueChanged();

public slots:
	void setValue(const Vector3& val);

	void setMinimum(float min);
	void setMaximum(float max);
	void setRange(float min, float max);
	void setGranularity(int gran);
	void setLabel(const QString& label);
	void setxLabel(const QString& label);
	void setyLabel(const QString& label);
	void setzLabel(const QString& label);
	void setComponentLabels(
		const QString& xLabel,
		const QString& yLabel,
		const QString& zLabel);
	void setLabels(
		const QString& mainLabel,
		const QString& xLabel,
		const QString& yLabel,
		const QString& zLabel);

private:
	QVBoxLayout* m_mainLayout;
	QLabel* m_label;
	QHBoxLayout* m_vectorLayout;
	FloatBoxEdit* m_xEdit;
	FloatBoxEdit* m_yEdit;
	FloatBoxEdit* m_zEdit;

	bool m_isReseting;
};

#endif //BENGINE_EDITOR_VECTOR3_EDIT_H
#ifndef BENGINE_EDITOR_TRANSFORM_EDIT_H
#define BENGINE_EDITOR_TRANSFORM_EDIT_H

#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qdialog.h>
#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qgroupbox.h>

#include <core/Transform.h>
using Core::Transform;

#include <widgets/Vector3Edit/Vector3Edit.h>

class TransformEdit : public QGroupBox
{
	Q_OBJECT

public:
	TransformEdit(Transform* trans = 0, QWidget * parent = 0);
	virtual ~TransformEdit();

	Transform* transform();

signals:
	void transformChanged();

public slots:
	void setTransform(Transform* trans);
	void setPosition(const Vector3& position);
	void setRotation(const Vector3& rotation);
	void setScale(const Vector3& scale);

private:
	Transform* m_transform;

	QVBoxLayout* m_mainLayout;
	Vector3Edit* m_positionEdit;
	Vector3Edit* m_rotationEdit;
	Vector3Edit* m_scaleEdit;

	static const QString styleSheet;
};

#endif //BENGINE_EDITOR_TRANSFORM_EDIT_H
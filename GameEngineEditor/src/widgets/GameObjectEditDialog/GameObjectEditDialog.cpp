#include "GameObjectEditDialog.h"

GameObjectEditDialog::GameObjectEditDialog(GameObject* gameObject, QWidget* parent)
	: QDialog(parent)
{
	setModal(false);
	setLayout(m_mainLayout = new QVBoxLayout);
	m_mainLayout->addWidget(m_transformEdit = new TransformEdit);

	Transform* transform = gameObject->getTransform();
	m_transformEdit->setTransform(transform);

	connect(m_transformEdit, SIGNAL(transformChanged()), this, SIGNAL(gameObjectChanged()));
}

GameObjectEditDialog::~GameObjectEditDialog()
{

}
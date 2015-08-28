#include "ActionButton.h"

#include <qt/QtWidgets/qaction.h>

ActionButton::ActionButton(QWidget* parent)
	: QPushButton(parent),
	m_action(0)
{
	this->registerType();
}

ActionButton::ActionButton(const QString & text, QWidget * parent)
	: QPushButton(text, parent)
{
	this->registerType();
}

ActionButton::ActionButton(const QIcon & icon, const QString & text, QWidget * parent)
	: QPushButton(icon, text, parent)
{
	this->registerType();
}

ActionButton::ActionButton(const ActionButton& other)
{
	m_action = other.action();
}

bool ActionButton::setAction(const QAction* action)
{
	bool ret = true;

	if (m_action != 0)
	{
		ret &= disconnect(this, SIGNAL(clicked()), m_action, SLOT(trigger()));
	}

	m_action = action;

	if (!connect(this, SIGNAL(clicked()), m_action, SLOT(trigger())))
	{
		ret = false;
	}

	return ret;
}

const QAction* ActionButton::action() const
{
	return m_action;
}

void ActionButton::registerType()
{
	if (!QMetaType::isRegistered(QMetaType::type("ActionButton")))
	{
		qRegisterMetaType<ActionButton>("ActionButton");
	}
}

ActionButton::~ActionButton() {}
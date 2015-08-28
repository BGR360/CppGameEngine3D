#ifndef BENGINE_EDITOR_ACTION_BUTTON_H
#define BENGINE_EDITOR_ACTION_BUTTON_H

#include <qt/QtWidgets/qpushbutton.h>
#include <qt/QtGui/qicon.h>

class QAction;

class ActionButton : public QPushButton
{
public:
	ActionButton(QWidget* parent = 0);
	ActionButton(const QString & text, QWidget * parent = 0);
	ActionButton(const QIcon & icon, const QString & text, QWidget * parent = 0);
	ActionButton(const ActionButton& other);
	virtual ~ActionButton();

	bool setAction(const QAction* action);
	const QAction* action() const;

private:
	const QAction* m_action;

	void registerType();
};

#endif //BENGINE_EDITOR_ACTION_BUTTON_H
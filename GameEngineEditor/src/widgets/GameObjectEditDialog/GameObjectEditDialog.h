#ifndef BENGINE_EDITOR_GAME_OBJECT_EDIT_DIALOG_H
#define BENGINE_EDITOR_GAME_OBJECT_EDIT_DIALOG_H

#include <qt/QtWidgets/qwidget.h>
#include <qt/QtWidgets/qboxlayout.h>
#include <qt/QtWidgets/qdialog.h>

#include <widgets/TransformEdit/TransformEdit.h>
#include <modelview/GameObjectItem.h>

class GameObjectEditDialog : public QDialog
{
	Q_OBJECT

public:
	GameObjectEditDialog(GameObject* gameObject, QWidget* parent = 0);
	virtual ~GameObjectEditDialog();

signals:
	void gameObjectChanged();

private:
	QVBoxLayout* m_mainLayout;
	TransformEdit* m_transformEdit;
};

#endif //BENGINE_EDITOR_GAME_OBJECT_EDIT_DIALOG_H
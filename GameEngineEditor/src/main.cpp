#include <iostream>

#include <qt/QtCore/qdebug.h>
#include <qt/QtCore/qsettings.h>
#include <qt/QtWidgets/qapplication.h>

#include "BengineEditor.h"
#include <widgets/Vector3Edit/Vector3Edit.h>
#include <widgets/FloatBoxEdit/floatboxedit.h>
#include <widgets/TransformEdit/TransformEdit.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	BengineEditor editor;
	editor.setWindowTitle("Bengine Editor");
	editor.show();

	return app.exec();
}
#include <qt/QtCore/qstring.h>

#define GAME_FILE_VERSION "1.0"
#define SCENE_FILE_VERSION "1.0"

QString DEFAULT_GAME_FILE_CONTENTS(const QString& gameName, const QString& defaultSceneFilePath)
{
	return QString(
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<game name = \"") + gameName + QString("\" version = \"") + QString(GAME_FILE_VERSION) + QString("\">\n"
		"  <systems></systems>\n"
		"  <scenes>\n"
		"    <scene name=\"Scene\" id=\"0\" src=\"") + defaultSceneFilePath + QString("\"/>\n"
		"    <default>0</default>\n"
		"  </scenes>\n"
		"  <editor>\n"
		"    <activeScene>0</activeScene>\n"
		"  </editor>\n"
		"</game>\n");
}

QString DEFAULT_SCENE_FILE_CONTENTS(const QString& sceneName)
{
	return QString(
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<scene name=\"") + sceneName + QString("\" version=\"") + QString(SCENE_FILE_VERSION) + QString("\">\n"
		"  <resources>\n"
		"    <shaders></shaders>\n"
		"    <meshes></meshes>\n"
		"    <images></images>\n"
		"    <textures></textures>\n"
		"  </resources>\n"

		"  <camera>\n"
		"    <position>\n"
		"      <x>0.0</x>\n"
		"      <y>0.0</y>\n"
		"      <z>0.0</z>\n"
		"    </position>\n"
		"    <forward>\n"
		"      <x>0.0</x>\n"
		"      <y>0.0</y>\n"
		"      <z>-1.0</z>\n"
		"    </forward>\n"
		"    <up>\n"
		"      <x>0.0</x>\n"
		"      <y>1.0</y>\n"
		"      <z>0.0</z>\n"
		"    </up>\n"
		"    <fov>120</fov>\n"
		"    <near>0.1</near>\n"
		"    <far>100.0</far>\n"
		"  </camera>\n"

		"  <gameObject name=\"Root\">\n"
		"    <transform>\n"
		"      <position>\n"
		"        <x>0.0</x>\n"
		"        <y>0.0</y>\n"
		"        <z>0.0</z>\n"
		"      </position>\n"
		"      <rotation>\n"
		"        <x>0.0</x>\n"
		"        <y>0.0</y>\n"
		"        <z>0.0</z>\n"
		"      </rotation>\n"
		"      <scale>\n"
		"        <x>1.0</x>\n"
		"        <y>1.0</y>\n"
		"        <z>1.0</z>\n"
		"      </scale>\n"
		"    </transform>\n"
		"    <components/>\n"
		"    <children>\n"

		"    </children>\n"
		"  </gameObject>\n"
		"</scene>\n");
}
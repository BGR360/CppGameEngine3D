#ifndef BENGINE_EDITOR_SCENE_GRAPH_MODEL_H
#define BENGINE_EDITOR_SCENE_GRAPH_MODEL_H

#include <qt/QtCore/qabstractitemmodel.h>
#include <qt/QtCore/qmap.h>

#include <modelview/GameObjectItem.h>

class SceneGraphModel : public QAbstractItemModel
{
public:
	SceneGraphModel(GameObjectItem* root, QObject* parent = 0);
	virtual ~SceneGraphModel();

	virtual QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;
	virtual QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	virtual QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

	GameObjectItem* getItem(const QModelIndex& index);

	virtual bool insertRows(int position, int rows,
		const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
	virtual bool removeRows(int position, int rows,
		const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
	
private:
	uint currentID;

	GameObjectItem* m_root;

	void getNames();
	void getName(GameObjectItem* current);
};

#endif //BENGINE_EDITOR_SCENE_GRAPH_MODEL_H
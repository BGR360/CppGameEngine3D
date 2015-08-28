#include "SceneGraphModel.h"

#include <qt/QtCore/qdebug.h>

#include "GameObjectItem.h"

#include <core/GameObject.h>
#include <core/Scene.h>

SceneGraphModel::SceneGraphModel(GameObjectItem* root, QObject* parent)
	: QAbstractItemModel(parent),
	m_root(root)
{
	getNames();
	currentID = 0;
}

QVariant SceneGraphModel::data(const QModelIndex& index, int role) const
{
	QVariant ret;

	if (role == Qt::DisplayRole && index.isValid())
	{
		GameObjectItem* indexedObject;
		indexedObject = static_cast<GameObjectItem*>(index.internalPointer());

		ret = indexedObject->getName();
	}
	else if (role == Qt::DecorationRole)
	{
		ret = QVariant();
	}
	else
	{
		ret = QVariant();
	}
	return ret;
}

Qt::ItemFlags SceneGraphModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QModelIndex SceneGraphModel::index(int row, int column, const QModelIndex &parent) const
{
	QModelIndex ret;

	if (!hasIndex(row, column, parent))
	{
		ret = QModelIndex();
	}

	//We don't use any column greater than 0
	if (column > 0)
	{
		ret = QModelIndex();
	}

	//Get parent object from parent index
	GameObjectItem* parentObject;

	if (parent.isValid())
	{
		parentObject = static_cast<GameObjectItem*>(parent.internalPointer());
	}
	else
	{
		parentObject = m_root;
	}

	//Get the proper child object from the parent object
	if ((uint)row < parentObject->getNumChildren() && row > -1)
	{
		ret = createIndex(row, column, parentObject->getChild(row));
	}
	else
	{
		ret = QModelIndex();
	}

	return ret;
}

QModelIndex SceneGraphModel::parent(const QModelIndex &index) const
{
	QModelIndex ret = QModelIndex();

	if (index.isValid() && index.column() == 0)
	{
		GameObjectItem* indexedObject;
		indexedObject = dynamic_cast<GameObjectItem*>(static_cast<GameObject*>(index.internalPointer()));
		
		if (indexedObject == 0)
		{
			qWarning() << "indexedObject is not of type GameObjectItem";
		}

		GameObjectItem* parentObject;
		parentObject = static_cast<GameObjectItem*>(indexedObject->getTransform()->getParent()->getGameObject());

		if (parentObject != 0 && parentObject != m_root)
		{
			ret = createIndex(parentObject->row(), 0, parentObject);
		}
		else
		{
			ret = QModelIndex();
		}
	}
	else
	{
		ret = QModelIndex();
	}

	return ret;
}

int SceneGraphModel::rowCount(const QModelIndex &parent) const
{
	int ret = 0;

	if (parent.column() <= 0)
	{
		GameObjectItem* parentObject;

		if (parent.isValid())
		{
			parentObject = static_cast<GameObjectItem*>(parent.internalPointer());
		}
		else
		{
			parentObject = m_root;
		}

		ret = (int)parentObject->getNumChildren();
	}
	else
	{
		ret = 0;
	}

	return ret;
}

int SceneGraphModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}


GameObjectItem* SceneGraphModel::getItem(const QModelIndex& index)
{
	GameObjectItem* ret = 0;
	if (index.isValid())
	{
		ret = static_cast<GameObjectItem*>(index.internalPointer());
	}
	return ret;
}


bool SceneGraphModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	beginInsertRows(parent, position, position + rows - 1);

	GameObjectItem* parentObject;
	if (parent.isValid())
	{
		parentObject = static_cast<GameObjectItem*>(parent.internalPointer());
	}
	else
	{
		parentObject = m_root;
	}

	for (int row = 0; row < rows; row++)
	{
		GameObjectItem* newObject = new GameObjectItem;

		uint id = currentID++;
		newObject->setID(id);

		newObject->setName(newObject->getName() + QString(" %1").arg(id));

		parentObject->insertChild(newObject, position + row);
	}

	endInsertRows();

	return true;
}

bool SceneGraphModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	GameObjectItem* parentObject;
	if (parent.isValid())
	{
		parentObject = static_cast<GameObjectItem*>(parent.internalPointer());
	}
	else
	{
		parentObject = m_root;
	}

	for (int row = position; row < position + rows; row++)
	{
		beginRemoveRows(parent, row, row);
		parentObject->removeChild(row);
		endRemoveRows();
	}

	return true;
}


void SceneGraphModel::getNames()
{
	//getName(m_root);
}

void SceneGraphModel::getName(GameObjectItem* current)
{
	/*uint id = current->getID();
	if (id != -1)
	{
		current->setName(QVariant(id).toString());
	}

	for (uint i = 0; i < current->getNumChildren(); i++)
	{
		getName(static_cast<GameObjectItem*>(current->getChild(i)));
	}*/
}

SceneGraphModel::~SceneGraphModel() {}
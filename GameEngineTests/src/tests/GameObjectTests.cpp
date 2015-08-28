#include <Testing.h>

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

#include <core/GameObject.h>
#include <math/RandomGenerator.h>

using std::string;
using std::stringstream;
using std::vector;

using Math::RandomGenerator;
using Core::GameObject;
using Core::GameComponent;
using Core::Transform;

//For use in the GameObject.UpdateHierarchy test
vector<int> updateOrder;

TEST(GameObject, DefaultConstruction)
{
	GameObject gameObject;

	int numComponents = gameObject.getNumComponents();
	int numChildren = gameObject.getNumChildren();

	EXPECT_EQ(0, numComponents);
	EXPECT_EQ(0, numChildren);
}

TEST(GameObject, AddComponent)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	int numComponentsToAdd = rng->irand(1, 10);
	int numTimes = rng->irand(1, 10);

	for (int i = 0; i < numTimes; i++)
	{
		GameObject gameObject;

		for (int j = 0; j < numComponentsToAdd; j++)
		{
			gameObject.addComponent(new GameComponent);
		}

		int numComponents = gameObject.getNumComponents();
		int numChildren = gameObject.getNumChildren();

		EXPECT_EQ(numComponentsToAdd, numComponents);
		EXPECT_EQ(0, numChildren);
	}
}

TEST(GameObject, AddChildren)
{
	GameObject parent;
	GameObject* child1, *child2, *child3, *child4, *child5;
	child1 = new GameObject;
	child2 = new GameObject;
	child3 = new GameObject;
	child4 = new GameObject;
	child5 = new GameObject;

	parent.addChild(child1);
	parent.addChild(child2);
	parent.addChild(child3);
	parent.addChild(child4);
	parent.addChild(child5);

	EXPECT_EQ(5, parent.getNumChildren());
}

TEST(GameObject, ChildHierarchy)
{
	GameObject root;
	GameObject* child1, *child2, *child3;
	GameObject* child1_child1, *child1_child2, *child3_child1;
	GameObject* child1_child2_child1;

	child1 = new GameObject;
	child2 = new GameObject;
	child3 = new GameObject;
	child1_child1 = new GameObject;
	child1_child2 = new GameObject;
	child3_child1 = new GameObject;
	child1_child2_child1 = new GameObject;

	root.addChild(child1);
	root.addChild(child2);
	root.addChild(child3);
	child1->addChild(child1_child1);
	child1->addChild(child1_child2);
	child3->addChild(child3_child1);
	child1_child2->addChild(child1_child2_child1);

	EXPECT_EQ(3, root.getNumChildren());
	EXPECT_EQ(2, child1->getNumChildren());
	EXPECT_EQ(1, child3->getNumChildren());
	EXPECT_EQ(1, child1_child2->getNumChildren());
}

TEST(GameObject, UpdateHierarchy)
{
	updateOrder = vector<int>();

	class UpdateComponent : public GameComponent
	{
		int m_id;
	public:
		UpdateComponent(int id) : m_id(id) {}
		virtual void update()
		{
			updateOrder.push_back(m_id);
		}
	};

	class UpdateObject : public GameObject
	{
	public:
		UpdateObject(int id)
		{
			this->addComponent(new UpdateComponent(id));
		}
	};

	GameObject root;
	UpdateObject* child1 = new UpdateObject(1);
	UpdateObject* child2 = new UpdateObject(2);
	UpdateObject* child3 = new UpdateObject(3);
	UpdateObject* child1_child1 = new UpdateObject(11);
	UpdateObject* child1_child2 = new UpdateObject(12);
	UpdateObject* child3_child1 = new UpdateObject(31);
	UpdateObject* child1_child2_child1 = new UpdateObject(121);

	root.addChild(child1);
	root.addChild(child2);
	root.addChild(child3);
	child1->addChild(child1_child1);
	child1->addChild(child1_child2);
	child3->addChild(child3_child1);
	child1_child2->addChild(child1_child2_child1);

	root.update();

	int expectedOrder[] = { 1, 11, 12, 121, 2, 3, 31 };
	int size = sizeof(expectedOrder) / sizeof(int);
	EXPECT_EQ(size, updateOrder.size());

	if (size == updateOrder.size())
	{
		for (int i = 0; i < size; i++)
		{
			EXPECT_EQ(expectedOrder[i], updateOrder[i]);
		}
	}
}



class ComponentA : public GameComponent
{
	int m_number;
public:
	ComponentA(int number) : m_number(number) {}
	string identify()
	{
		stringstream ret;
		ret << "ComponentA #" << m_number;
		return ret.str();
	}
};
class ComponentB : public GameComponent
{
public:
	string identify() { return "ComponentB"; }
};
class ComponentC : public GameComponent
{
public:
	string identify() { return "ComponentC"; }
};

TEST(GameObject, GetComponent)
{
	GameObject object;
	object.addComponent(new GameComponent);
	object.addComponent(new ComponentA(1));
	object.addComponent(new ComponentC);
	object.addComponent(new GameComponent);
	object.addComponent(new ComponentA(2));
	object.addComponent(new GameComponent);
	object.addComponent(new ComponentB);

	ComponentA* a = object.getComponent<ComponentA>();
	ComponentB* b = object.getComponent<ComponentB>();
	ComponentC* c = object.getComponent<ComponentC>();

	string a_id = a->identify();
	string b_id = b->identify();
	string c_id = c->identify();

	EXPECT_EQ("ComponentA #1", a_id);
	EXPECT_EQ("ComponentB", b_id);
	EXPECT_EQ("ComponentC", c_id);
}

TEST(GameComponent, GetGameObject)
{
	GameObject object1;
	GameObject object2;

	object1.addComponent(new ComponentB);
	object1.addComponent(new ComponentC);
	object2.addComponent(new ComponentC);

	ComponentB* b1 = object1.getComponent<ComponentB>();
	ComponentC* c1 = object1.getComponent<ComponentC>();
	ComponentC* c2 = object2.getComponent<ComponentC>();

	GameObject* b1_object = b1->getGameObject();
	GameObject* c1_object = c1->getGameObject();
	GameObject* c2_object = c2->getGameObject();

	EXPECT_EQ(&object1, b1_object);
	EXPECT_EQ(&object1, c1_object);
	EXPECT_EQ(&object2, c2_object);
}

TEST(GameObject, TransformHierarchy)
{
	GameObject root;
	GameObject* child = new GameObject;

	root.addChild(child);

	Transform* root_t = root.getTransform();
	Transform* child_t = child->getTransform();

	EXPECT_EQ(root_t, child_t->getParent());
}

TEST(GameObject, FindingParent)
{
	GameObject parent;
	GameObject* child = new GameObject;

	parent.addChild(child);

	GameObject* foundParent = child->getTransform()->getParent()->getGameObject();
	GameObject* expected = &parent;

	EXPECT_EQ(expected, foundParent);

	Transform* foundParent_t = parent.getTransform()->getParent();
	EXPECT_EQ(0, foundParent_t);
}
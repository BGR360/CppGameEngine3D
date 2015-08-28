#include <Testing.h>

#include <core/Transform.h>

using Core::Transform;

TEST(Transform, Constrution)
{
	Transform transform;

	Vector3 expectedPosition(0.0f, 0.0f, 0.0f);
	Vector3 expectedRotation(0.0f, 0.0f, 0.0f);
	Vector3 expectedScale(1.0f, 1.0f, 1.0f);

	EXPECT_VEC3_EQ(expectedPosition, transform.getPosition());
	EXPECT_VEC3_EQ(expectedRotation, transform.getRotation());
	EXPECT_VEC3_EQ(expectedScale, transform.getScale());
}

TEST(Transform, SetPosition)
{
	Transform transform;

	Vector3 position(1.0f, 2.0f, -42928.06968f);
	transform.setPosition(position);

	EXPECT_VEC3_EQ(position, transform.getPosition());
}

TEST(Transform, SetRotation)
{
	Transform transform;

	Vector3 rotation(1.0f, 2.0f, -42928.06968f);
	transform.setRotation(rotation);

	EXPECT_VEC3_EQ(rotation, transform.getRotation());
}

TEST(Transform, SetScale)
{
	Transform transform;

	Vector3 scale(1.0f, 2.0f, -42928.06968f);
	transform.setScale(scale);

	EXPECT_VEC3_EQ(scale, transform.getScale());
}

TEST(Transform, SetParent)
{
	Transform parent;
	Transform child;
	Transform child_child;

	child_child.setParent(&child);
	child.setParent(&parent);

	Transform* p_null = parent.getParent();
	Transform* p_parent = child.getParent();
	Transform* p_child = child_child.getParent();

	EXPECT_EQ(0, p_null);
	EXPECT_EQ(&parent, p_parent);
	EXPECT_EQ(&child, p_child);
}

TEST(Transform, ClearParent)
{
	Transform parent;
	Transform child;

	child.setParent(&parent);
	EXPECT_EQ(&parent, child.getParent());

	child.clearParent();
	EXPECT_EQ(0, child.getParent());
}

//TEST(Transform, GetAggregate)
//{
//	Transform first(
//		Vector3(0.0f, 0.0f, 0.0f),
//		Vector3(45.0f, 0.0f, 90.0f),
//		Vector3(1.0f, 1.0f, 1.0f));
//
//	Transform second(
//		Vector3(1.0f, -2.0f, 3.0f),
//		Vector3(45.0f, -90.0f, 0.0f),
//		Vector3(0.25f, 2.0f, 2.0f));
//
//	Transform third(
//		Vector3(-2.0f, -2.0f, -2.0f),
//		Vector3(0.0f, 0.0f, 0.0f),
//		Vector3(1.0f, 1.0f, 0.5f));
//
//	Transform expected(
//		Vector3(-1.0f, -4.0f, 1.0f),
//		Vector3(90.0f, -90.0f, 90.0f),
//		Vector3(0.25f, 2.0f, 1.0f));
//
//	third.setParent(&second);
//	second.setParent(&first);
//
//	Transform result = third.getAggregate();
//
//	EXPECT_VEC3_EQ(expected.getPosition(), result.getPosition());
//	EXPECT_VEC3_EQ(expected.getRotation(), result.getRotation());
//	EXPECT_VEC3_EQ(expected.getScale(), result.getScale());
//}

TEST(Transform, ToModelMatrix)
{
	Vector3 position(1, 2, 3);
	Vector3 rotation(45, 45, 0);
	Vector3 scale(1, 1, 1);

	Transform transform(position, rotation, scale);

	Matrix4x4 translationMatrix = Matrix4x4::translate(position);
	Matrix4x4 rotationMatrix = Matrix4x4::rotate(rotation);
	Matrix4x4 scaleMatrix = Matrix4x4::scale(scale);

	Matrix4x4 expectedModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	Matrix4x4 modelMatrix = transform.toModelMatrix();

	EXPECT_MAT4_EQ(expectedModelMatrix, modelMatrix);
}
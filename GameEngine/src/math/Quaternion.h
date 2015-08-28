#ifndef BENGINE_QUATERNION_H
#define BENGINE_QUATERNION_H

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

#endif //BENGINE_QUATERNION_H
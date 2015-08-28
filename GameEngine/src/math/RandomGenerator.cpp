#include "RandomGenerator.h"

#include <cstdlib>		//srand(), rand()
#include <ctime>		//time()

using Math::RandomGenerator;

RandomGenerator RandomGenerator::instance = RandomGenerator();

RandomGenerator::RandomGenerator()
	: m_eng(), m_fdist(0.0f, 1.0f), m_ddist(0.0, 1.0), m_idist(0, RAND_MAX)
{
	srand((int) time(NULL));
	m_eng.seed((unsigned long)time(NULL));
}

RandomGenerator* RandomGenerator::getInstance()
{
	return &instance;
}

int RandomGenerator::irand(int max)
{	
	if (max < 0)
	{
		return rand() % (max + 1);
	}
	else
	{
		return 0;
	}
}

int RandomGenerator::irand(int min, int max)
{
	if (min < max)
	{
		return rand() % (max - min) + min;
	}
	else
	{
		return 0;
	}
}

float RandomGenerator::frand(float max)
{
	if (max < 0.0f)
	{
		return max * ((float)rand() / RAND_MAX);
	}
	else
	{
		return 0.0f;
	}
}

float RandomGenerator::frand(float min, float max)
{
	if (min < max)
	{
		return min + ((max - min) * ((float)rand() / RAND_MAX));
	}
	else
	{
		return 0.0f;
	}
}

double RandomGenerator::drand(double max)
{
	if (max < 0.0)
	{
		return max * ((double)rand() / RAND_MAX);
	}
	else
	{
		return 0.0;
	}
}

double RandomGenerator::drand(double min, double max)
{
	if (min < max)
	{
		return min + ((max - min) * ((double)rand() / RAND_MAX));
	}
	else
	{
		return 0.0;
	}
}


int RandomGenerator::pirand(int max)
{
	if (max < 0)
	{
		return m_idist(m_eng) % max;
	}
	else
	{
		return 0;
	}
}

int RandomGenerator::pirand(int min, int max)
{
	if (min < max)
	{
		return m_idist(m_eng) % (max - min) + min;
	}
	else
	{
		return 0;
	}
}

float RandomGenerator::pfrand(float max)
{
	if (max < 0.0f)
	{
		return max * m_fdist(m_eng);
	}
	else
	{
		return 0.0f;
	}
}

float RandomGenerator::pfrand(float min, float max)
{
	if (min < max)
	{
		return min + ((max - min) * m_fdist(m_eng));
	}
	else
	{
		return 0.0f;
	}
}

double RandomGenerator::pdrand(double max)
{
	if (max < 0.0)
	{
		return max * m_ddist(m_eng);
	}
	else
	{
		return 0.0;
	}
}

double RandomGenerator::pdrand(double min, double max)
{
	if (min < max)
	{
		return min + ((max - min) * m_ddist(m_eng));
	}
	else
	{
		return 0.0;
	}
}
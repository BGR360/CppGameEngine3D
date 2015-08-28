#ifndef BENGINE_RANDOM_GENERATOR_H
#define BENGINE_RANDOM_GENERATOR_H

#include <Engine.h>

#include <random>

using std::default_random_engine;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

namespace Math
{
	class ENGINE_DLL_EXPORT_IMPORT RandomGenerator
	{
		static RandomGenerator instance;

		default_random_engine m_eng;

		uniform_int_distribution<int> m_idist;
		uniform_real_distribution<float> m_fdist;
		uniform_real_distribution<double> m_ddist;

	public:
		RandomGenerator();

		static RandomGenerator* getInstance();

		int irand(int max);
		int irand(int min, int max);

		float frand(float max);
		float frand(float min, float max);

		double drand(double max);
		double drand(double min, double max);

		//Precise functions with uniform distributions
		int pirand(int max);
		int pirand(int min, int max);

		float pfrand(float max);
		float pfrand(float min, float max);

		double pdrand(double max);
		double pdrand(double min, double max);
	};
}

#endif //BENGINE_RANDOM_GENERATOR_H
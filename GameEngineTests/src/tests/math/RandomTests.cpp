#include<Testing.h>

#include <math/RandomGenerator.h>

using Math::RandomGenerator;

#ifdef MATH_TESTS

#define NUM_RANDOMS_TO_GENERATE_PER_TEST 20

#ifdef RANDOM_TESTS

TEST(Random, irand)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	int random;

	for (int i = 0; i < NUM_RANDOMS_TO_GENERATE_PER_TEST; i++)
	{
		random = rng->irand(-10, 10);
		std::cout << random << std::endl;
	}
}

TEST(Random, frand)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	float random;
	
	for (int i = 0; i < NUM_RANDOMS_TO_GENERATE_PER_TEST; i++)
	{
		random = rng->frand(0.0f, 1.0f);
		std::cout << random << std::endl;
	}
}

TEST(Random, drand)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	double random;

	for (int i = 0; i < NUM_RANDOMS_TO_GENERATE_PER_TEST; i++)
	{
		random = rng->drand(-1000., 1000.);
		std::cout << random << std::endl;
	}
}


TEST(Random, pirand)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	int random;

	for (int i = 0; i < NUM_RANDOMS_TO_GENERATE_PER_TEST; i++)
	{
		random = rng->pirand(-10, 10);
		std::cout << random << std::endl;
	}
}

TEST(Random, pfrand)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	float random;

	for (int i = 0; i < NUM_RANDOMS_TO_GENERATE_PER_TEST; i++)
	{
		random = rng->pfrand(0.0f, 1.0f);
		std::cout << random << std::endl;
	}
}

TEST(Random, pdrand)
{
	RandomGenerator* rng = RandomGenerator::getInstance();
	double random;

	for (int i = 0; i < NUM_RANDOMS_TO_GENERATE_PER_TEST; i++)
	{
		random = rng->pdrand(-1000., 1000.);
		std::cout << random << std::endl;
	}
}

#endif //RANDOM_TESTS

#endif //MATH_TESTS
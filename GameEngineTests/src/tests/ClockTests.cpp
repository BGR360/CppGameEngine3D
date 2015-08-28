#include <Testing.h>

#include <Windows.h>

//#include <qt/QtTest/qtest.h>

#include <core/GameClock.h>
#include <math/RandomGenerator.h>

using Core::GameClock;
using Math::RandomGenerator;

#define FLOAT_THRESHOLD 0.02f
#define DOUBLE_THRESHOLD 0.02
#define PRINT_CLOSE_ENOUGH() cout << "."
#define PRINT_NOT_CLOSE_ENOUGH(expected, actual) \
	cout << "Difference: " << abs(expected - actual) << endl; \
	cout << "Expected: " << expected << endl; \
	cout << "Actual: " << actual << endl

void sleep(int millis)
{
	return Sleep(millis);
}

TEST(Clock, Construction)
{
	GameClock clock;
	double time = clock.getTime();
	double expectedTime = 0.0;
	float delta = clock.getDelta();
	float expectedDelta = 0.0f;

	EXPECT_DOUBLE_EQ(expectedTime, time);
	EXPECT_FLOAT_EQ(expectedDelta, delta);

	expectedTime = 0.0;
	expectedDelta = 0.0f;
	clock.start();
	time = clock.getTime();
	delta = clock.getDelta();

	EXPECT_DOUBLE_CLOSE_ENOUGH(expectedTime, time);
	EXPECT_FLOAT_CLOSE_ENOUGH(expectedDelta, delta);

	cout << endl;
}

TEST(Clock, WaitOneSecond)
{
	GameClock clock;
	double expectedTime = 1.0;
	float expectedDelta = 1.0f;

	clock.start();
	sleep(1000);
	clock.newFrame();
	double time = clock.getTime();
	float delta = clock.getDelta();

	EXPECT_DOUBLE_CLOSE_ENOUGH(expectedTime, time);
	EXPECT_FLOAT_CLOSE_ENOUGH(expectedDelta, delta);

	cout << endl;
}

TEST(Clock, ShortTimes)
{
	GameClock clock;
	RandomGenerator* rng = RandomGenerator::getInstance();

	int numTimesToTest = rng->irand(1, 50);

	float expectedDelta;
	float delta;
	int randomSleepTimeMs;
	double totalTimeSlept = 0.0;

	clock.start();

	for (int i = 0; i < numTimesToTest; i++)
	{
		randomSleepTimeMs = rng->irand(1, 100);
		expectedDelta = randomSleepTimeMs / 1000.0f;
		sleep(randomSleepTimeMs);
		clock.newFrame();
		delta = clock.getDelta();
		EXPECT_FLOAT_CLOSE_ENOUGH(expectedDelta, delta);

		totalTimeSlept += delta;
	}

	double expectedTime = totalTimeSlept;
	double time = clock.getTime();

	EXPECT_DOUBLE_CLOSE_ENOUGH(expectedTime, time);

	cout << endl;
}

#ifdef OVERNIGHT_TESTS

TEST(Clock, LongTimes)
{
	GameClock clock;
	RandomGenerator* rng = RandomGenerator::getInstance();

	int numTimesToTest = rng->irand(500, 1000);

	float expectedDelta;
	float delta;
	int randomSleepTimeMs;
	double totalTimeSlept = 0.0;

	clock.start();

	for (int i = 0; i < numTimesToTest; i++)
	{
		randomSleepTimeMs = rng->irand(100, 10000);
		expectedDelta = randomSleepTimeMs / 1000.0f;
		sleep(randomSleepTimeMs);
		clock.newFrame();
		delta = clock.getDelta();
		EXPECT_FLOAT_CLOSE_ENOUGH(expectedDelta, delta);

		totalTimeSlept += delta;
	}

	double expectedTime = totalTimeSlept;
	double time = clock.getTime();

	EXPECT_DOUBLE_CLOSE_ENOUGH(expectedTime, time);

	cout << endl;
}

#endif //OVERNIGHT_TESTS
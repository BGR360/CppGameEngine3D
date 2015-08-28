#include "GameClock.h"

#include <exceptions/BengineException.h>

using Exceptions::BengineException;

namespace Core
{
	GameClock::GameClock()
	{
		m_startTime.QuadPart = -1;
		m_timeLastFrame.QuadPart = -1;
		m_frequency.QuadPart = -1;
	}

	void GameClock::start()
	{
		LARGE_INTEGER frequency;
		LARGE_INTEGER time;

		this->queryPerformanceFrequency(&frequency);
		m_frequency.QuadPart = frequency.QuadPart;

		this->queryPerformanceCounter(&time);
		m_startTime.QuadPart = time.QuadPart;

		m_timeLastFrame.QuadPart = m_startTime.QuadPart;
		this->newFrame();
	}

	double GameClock::getTime()
	{
		if (m_startTime.QuadPart == (LONGLONG)(-1))
		{
			return 0.0;
		}
		else
		{
			LARGE_INTEGER time;
			this->queryPerformanceCounter(&time);
			time.QuadPart -= m_startTime.QuadPart;

			return (double)time.QuadPart / m_frequency.QuadPart;
		}
	}

	void GameClock::newFrame()
	{
		LARGE_INTEGER thisTime;
		this->queryPerformanceCounter(&thisTime);
		m_deltaLastFrame.QuadPart = thisTime.QuadPart - m_timeLastFrame.QuadPart;
		m_timeLastFrame.QuadPart = thisTime.QuadPart;
	}

	float GameClock::getDelta()
	{
		if (m_startTime.QuadPart == (LONGLONG)(-1))
		{
			return 0.0;
		}
		else
		{
			return (float)m_deltaLastFrame.QuadPart / m_frequency.QuadPart;
		}
	}

	void GameClock::queryPerformanceFrequency(LARGE_INTEGER* frequency)
	{
		if (!QueryPerformanceFrequency(frequency))
		{
			throw BengineException("Failed to query performance frequency.");
		}
	}

	void GameClock::queryPerformanceCounter(LARGE_INTEGER* counter)
	{
		if (!QueryPerformanceCounter(counter))
		{
			throw BengineException("Failed to query performance counter.");
		}
	}

	GameClock::~GameClock()	{}
}
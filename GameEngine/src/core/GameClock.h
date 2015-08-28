#ifndef BENGINE_GAME_CLOCK_H
#define BENGINE_GAME_CLOCK_H

#include <Engine.h>

#include <Windows.h>

namespace Core
{
	class ENGINE_DLL_EXPORT_IMPORT GameClock
	{
		LARGE_INTEGER m_startTime;
		LARGE_INTEGER m_timeLastFrame;
		LARGE_INTEGER m_deltaLastFrame;
		LARGE_INTEGER m_frequency;

	public:
		GameClock();
		virtual ~GameClock();

		void start();
		double getTime();

		void newFrame();
		float getDelta();

	private:
		void queryPerformanceFrequency(LARGE_INTEGER* frequency);
		void queryPerformanceCounter(LARGE_INTEGER* counter);
	};
}

#endif //BENGINE_GAME_CLOCK_H
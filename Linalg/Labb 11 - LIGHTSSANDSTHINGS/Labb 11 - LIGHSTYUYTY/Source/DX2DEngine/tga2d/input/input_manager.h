#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include "tga2d/math/Vector2.h"

namespace DX2D
{
	class CInputManager
	{
	public:
		CInputManager(void);
		~CInputManager(void);
		void Init();
		bool IsKeyDown(unsigned char aKey);
		Vector2f GetMousePositionNormalized() const {return myMouseNormalizedPosition;}
		void Update();
	private:
		static void ThreadedPollUpdate();
		static std::vector<unsigned char> previous;
		static std::vector<unsigned char> current;
		std::thread myThreadPoller;
		static bool myRunThreadedUpdate;
		std::mutex myMutex;
		Vector2<unsigned int> myMousePosition;
		Vector2f myMouseNormalizedPosition;

		static POINT myThreadedMouseAbsPos;
		static Vector2f myThreadedMouseNormalizedPos;
	};


}

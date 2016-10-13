#ifndef TIME_HANDLER_HEADER
#define TIME_HANDLER_HEADER

#include "namespaces.h"
#include "..\hgelibs\include\hgefont.h"

namespace FroggerGame
{
	class Frog;

    class TimeHandler
    {

    public:

        TimeHandler();
        ~TimeHandler();
        void Init(Frog* aFrog);
        void ResetTime();
        void Update();
        void Render();

    private:

        float myDeltaTime;
		float myTimer;
		hgeFont* myFont;
		Frog* myFrog;

    };
};

#endif
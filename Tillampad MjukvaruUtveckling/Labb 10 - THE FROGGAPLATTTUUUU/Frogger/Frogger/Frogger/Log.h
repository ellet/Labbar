#ifndef FROGGER_LOG_HEADER
#define FROGGER_LOG_HEADER

#include "WaterEntity.h"
#include "namespaces.h"

namespace FroggerGame
{
    class Log : public WaterEntity
    {

    public:

        Log();
        ~Log();
        void Init(CU::Vector2f aPosition, WaterEntityTypes aWaterEntityType, float aSpeed);

    private:

    };
};

#endif

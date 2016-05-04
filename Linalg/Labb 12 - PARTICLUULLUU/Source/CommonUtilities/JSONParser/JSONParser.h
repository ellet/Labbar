#pragma once
#include "picojson-master/picojson.h"
#include "../DLDebug/DL_Debug.h"
#include <fstream>
#include "../Vectors/vector2.h"
#include "../Vectors/vector3.h"

class JSONParser
{
public:
	static void Create();
	static void Destroy();

	static inline picojson::value GetDaObject(const std::string & aNameOfValue);
	static inline picojson::array GetDaArray(const std::string & aNameOfValue);

	static inline float GetFloatFromValue(const picojson::value & aValue);
	static inline Vector2f GetVector2FromValue(picojson::value & aValue);
	static inline Vector3f GetVector3FromValue(picojson::value & aValue);
	
	static inline void GetSphereData(picojson::value & aValue, Vector3f & aPositionToSet, float & aRadiusToSet);

	static inline void GetMinMaxRangeVectors(picojson::value & aValue, Vector3f & aMinValues, Vector3f & aMaxValues);

private:
	static JSONParser* ourInstance;

	std::ifstream myFileReader;

	picojson::object myRoot;
	//picojson::object * myActiveObject;

	inline static JSONParser & GetInstance();

	JSONParser();
	~JSONParser();
};

inline picojson::value JSONParser::GetDaObject(const std::string & aNameOfValue)
{
	return GetInstance().myRoot[aNameOfValue];
}

float JSONParser::GetFloatFromValue(const picojson::value & aValue)
{
	return static_cast<float>(aValue.get<double>());
}

inline Vector2f JSONParser::GetVector2FromValue(picojson::value & aValue)
{
	picojson::object objectWithVector = aValue.get<picojson::object>();
	picojson::object tempVector = objectWithVector["Vector2"].get<picojson::object>();

	float tempX = GetFloatFromValue(tempVector["x"]);
	float tempY = GetFloatFromValue(tempVector["y"]);

	return Vector2f(tempX, tempY);
}

inline Vector3f JSONParser::GetVector3FromValue(picojson::value & aValue)
{
	picojson::object objectWithVector = aValue.get<picojson::object>();
	picojson::object tempVector = objectWithVector["Vector3"].get<picojson::object>();

	float tempX = GetFloatFromValue(tempVector["x"]);
	float tempY = GetFloatFromValue(tempVector["y"]);
	float tempZ = GetFloatFromValue(tempVector["z"]);

	return Vector3f(tempX, tempY, tempZ);
}

void JSONParser::GetMinMaxRangeVectors(picojson::value & aValue, Vector3f & aMinValues, Vector3f & aMaxValues)
{
	picojson::object objectWithMinMax = aValue.get<picojson::object>();

	aMinValues = GetVector3FromValue(objectWithMinMax["Min"]);
	aMaxValues = GetVector3FromValue(objectWithMinMax["Max"]);
}

inline JSONParser & JSONParser::GetInstance()
{
	DL_ASSERT(ourInstance != nullptr, "JSONParser is nullptr");
	return *ourInstance;
}

picojson::array JSONParser::GetDaArray(const std::string & aNameOfValue)
{
	return GetInstance().myRoot[aNameOfValue].get<picojson::array>();
}

inline void JSONParser::GetSphereData(picojson::value & aValue, Vector3f & aPositionToSet, float & aRadiusToSet)
{
	aPositionToSet = GetVector3FromValue(aValue.get<picojson::object>()["Position"]);
	aRadiusToSet = GetFloatFromValue(aValue.get<picojson::object>()["Radius"]);
}
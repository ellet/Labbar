#pragma once

#define SERIALIZE(aStream, aType) serialize(aType, aStream)
#define DESERIALIZE(aStream, aType) aType = deserialize<decltype(aType)>(aStream)


#pragma once
#include "Engine/Resources/Resource.h"

namespace ENGINE_NAMESPACE
{
	class AsynchronousResource : public Resource
	{
	public:
		AsynchronousResource(const std::string & aFilePath);
		~AsynchronousResource();
		
		virtual bool Prepare(bool aLoadAsynchronously);
		virtual void Load() = 0;

		virtual void PrepareRemoval() override;

	private:
		std::atomic_bool myFinishedLoadingFlag;
		std::thread *myLoadThread;
	};
}

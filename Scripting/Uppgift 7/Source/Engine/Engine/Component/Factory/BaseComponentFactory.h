#pragma once

namespace SB
{
	class Camera;
	class Time;

	class BaseComponentFactory
	{
	public:
		BaseComponentFactory();
		virtual ~BaseComponentFactory() = 0;

		virtual void BeginUpdate(const Time & aDeltaTime);
		virtual void Update(const Time & aDeltaTime);
		virtual void EndUpdate(const Time & aDeltaTime);

		virtual void Render(const Camera & aCamera) const;

		virtual void DebugUpdate(const Time & aDeltaTime);
		virtual void DebugRender(const Camera & aCamera) const;

		virtual void ReturnMemory(unsigned short aIndex) = 0;
		virtual bool Prepare(bool aLoadAsynchronously) = 0;
	};

	inline BaseComponentFactory::BaseComponentFactory()
	{
	}

	inline BaseComponentFactory::~BaseComponentFactory()
	{
	}

	inline void BaseComponentFactory::BeginUpdate(const Time & aDeltaTime)
	{
	}

	inline void BaseComponentFactory::Update(const Time & aDeltaTime)
	{
	}

	inline void BaseComponentFactory::EndUpdate(const Time & aDeltaTime)
	{
	}

	inline void BaseComponentFactory::Render(const Camera & aCamera) const
	{
	}

	inline void BaseComponentFactory::DebugUpdate(const Time & aDeltaTime)
	{
	}

	inline void BaseComponentFactory::DebugRender(const Camera & aCamera) const
	{
	}
}

#pragma once

namespace ENGINE_NAMESPACE
{
	class Time;

	class BaseComponentFactory
	{
	public:
		BaseComponentFactory();
		virtual ~BaseComponentFactory() = 0;

		virtual void Update(const Time & aDeltaTime);
		virtual void Render() const;

		virtual void DebugUpdate(const Time & aDeltaTime);
		virtual void DebugRender() const;

		virtual void ReturnMemory(unsigned short aIndex) = 0;
		virtual bool Prepare(bool aLoadAsynchronously) = 0;
	};

	inline BaseComponentFactory::BaseComponentFactory()
	{
	}

	inline BaseComponentFactory::~BaseComponentFactory()
	{
	}

	inline void BaseComponentFactory::Update(const Time & aDeltaTime)
	{
	}

	inline void BaseComponentFactory::Render() const
	{
	}

	inline void BaseComponentFactory::DebugUpdate(const Time & aDeltaTime)
	{
	}

	inline void BaseComponentFactory::DebugRender() const
	{
	}
}

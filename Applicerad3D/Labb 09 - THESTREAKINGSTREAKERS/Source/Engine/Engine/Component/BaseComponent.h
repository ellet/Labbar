#pragma once

namespace ENGINE_NAMESPACE
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent() = 0;

		virtual void Update(const Time & aDeltaTime);

		virtual void Render() const;

		virtual void Initialize();

		GameObject & GetGameObject();

		void SetGameObject(GameObject & anObject);

	protected:
		GameObject * myObject;
	};
}

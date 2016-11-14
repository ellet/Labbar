#pragma once

namespace ENGINE_NAMESPACE
{
	class GameObject;

	class ObjectPtr
	{
	public:
		ObjectPtr(const ObjectPtr &aOtherPointer);
		ObjectPtr(std::nullptr_t aNullptr);
		//ObjectPtr(ObjectPtr && aOtherPointer);
		ObjectPtr(GameObject *aPointer, std::atomic<int> * aRefCounter);
		ObjectPtr(const GameObject *aPointer, std::atomic<int> * aRefCounter);
		ObjectPtr();
		~ObjectPtr();

		//ObjectPtr & operator=(ObjectPtr && aOtherPointer);
		ObjectPtr & operator=(const ObjectPtr & aOtherPointer);
		bool operator==(std::nullptr_t aNullptr) const;
		bool operator!=(std::nullptr_t aNullptr) const;
		bool operator==(const ObjectPtr & aOtherPointer) const;
		bool operator!=(const ObjectPtr & aOtherPointer) const;
		bool operator==(const GameObject * aOtherPointer) const;
		bool operator!=(const GameObject * aOtherPointer) const;

		GameObject *operator->();
		GameObject *operator->() const;
		GameObject &operator*();
		GameObject &operator*() const;

	private:
		void ReturnObject();

		std::atomic<int> * myReferenceCounter;
		GameObject *myPointer;
	};
}

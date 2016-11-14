#pragma once

namespace ENGINE_NAMESPACE
{
	enum class ResourceStatus
	{
		eNotStartedLoading,
		ePreparing,
		eRemoved,
		eReady,
	};

	class Resource
	{
	public:
		virtual ~Resource();

		virtual void Reload() = 0;
		const std::string & GetPath() const;

		const ResourceStatus& GetStatus() const;

		virtual void PrepareRemoval();

	protected:
		Resource(const std::string & aFilePath);
		void SetStatus(const ResourceStatus & aStatus);

	private:
		std::string myPath;
		ResourceStatus myStatus;
	};

	inline const ResourceStatus& Resource::GetStatus() const
	{
		return myStatus;
	}
}

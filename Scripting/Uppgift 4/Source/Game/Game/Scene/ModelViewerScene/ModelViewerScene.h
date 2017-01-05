#pragma once

namespace SB
{
	struct WindowMessage;

	class ModelViewerScene : 
		public Scene, public Subscriber<WindowMessage>
	{
	public:
		ModelViewerScene(SB::PostMasterState & aPostMasterState);
		~ModelViewerScene();

		virtual void Update(const Time & aDeltaTime) override;

		virtual void Render() override;
		virtual void DebugRender() override;

		virtual void OnEnter() override;


		//virtual ReceiveResult Receive(const WindowMessage & aMessage) override;

		ReceiveResult Receive(const WindowMessage& aMessage);

	private:
		void LoadModel(const std::string & aPathToFileToLoad, const bool aFixScaleFlag = true);

		ObjectPtr myModelGameObject;

		GrowingArray<std::string> myMeshNames;
		std::shared_ptr<Subscription<WindowMessage>> myFileDropListener;
	};
}

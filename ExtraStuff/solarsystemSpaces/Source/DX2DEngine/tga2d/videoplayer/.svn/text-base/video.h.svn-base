/*
This class will store a texture bound to DX11
*/
#pragma once

namespace Tga2D
{
	enum VideoStatus
	{
		VideoStatus_Idle,
		VideoStatus_Playing,
		VideoStatus_ReachedEnd
	};
	class CVideo
	{
	public:
		CVideo();
		~CVideo();
		bool Init(const char* aPath);
		void Play(bool aLoop = false);
		void Pause();
		void Stop();

		void Update(float aDelta);

		/* Will return false if there was something wrong with the load of the video */
		bool Render();
		void Restart();
		
		class CSprite* GetSprite() const { return mySprite; }

		Tga2D::Vector2<int> GetVideoSize() const { return mySize; }
	private:
		class CSprite* mySprite;
		class CVideoPlayer* myPlayer;

		struct ID3D11ShaderResourceView* myShaderResource;
		struct ID3D11Texture2D *myTexture;
		
		int *myBuffer;

		Tga2D::Vector2<int> mySize;

		float myUpdateTime;
		VideoStatus myStatus;
		bool myWantsToPlay;
		bool myIsLooping;
	};
}

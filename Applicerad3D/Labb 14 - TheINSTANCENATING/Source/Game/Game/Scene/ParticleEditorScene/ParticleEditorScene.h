#pragma once
//#include <Engine\Scene\JsonScene.h>


namespace SB
{
	class ParticleEmitter;
	struct EmitterSettings;
	class Scene;
	class Texture;
}

class ParticleEditorScene : public SB::Scene
{
public:
	ParticleEditorScene(SB::PostMasterState & aPostMasterState);
	virtual ~ParticleEditorScene();

	virtual void Update(const SB::Time & aDeltaTime) override;

	virtual void OnEnter() override;

	virtual void Render() override;

private:
	bool ErrorCheckMinMax(const SB::Vector2f & aVector, const SB::Vector2f & aMinMax = SB::Vector2f(0.f, 1.f));
	bool HasErrors();
	void SetEmitterToEditor();

	void HandleExternal();

	void AddCurrentEmitter();
	void SaveEmitters();

	std::string myEmitterName;
	float myEmitCD;
	int myParticleAmount;
	std::shared_ptr<SB::Texture> myAtlasTexture;
	std::shared_ptr<SB::EmitterSettings> myEmitterSettings;
	std::shared_ptr<SB::ParticleEmitter> myEmitter;
};


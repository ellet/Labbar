#pragma once
//#include <Engine\Scene\JsonScene.h>


namespace SB
{
	struct ParticleForceField;
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
	void ForceFieldWindow();
	void AddLocalForceField();
	void HelpingWindow();
	void MakeWorldGrid();
	void RenderForceFields();
	void HandleActionTextAndAutosave(const SB::Time & aDeltaTime);
	bool ErrorCheckMinMax(const SB::Vector2f & aVector, const SB::Vector2f & aMinMax = SB::Vector2f(0.f, 1.f));
	bool HasErrors();
	void SetEmitterToEditor();
	void SetupEmitterNames();

	void HandleExternal();

	void ChangeForceFields();
	void ChooseEmitterToEdit();
	void ApplyChangesToEmitter();
	void AddCurrentEmitter();
	void RemoveSelectedEmitter();
	void SaveEmitters();
	void AutoSave();
	void BackupSave();

	SB::GrowingArray<std::string, unsigned short> myEmitterTypeNames;
	SB::GrowingArray<std::string, unsigned short> myLocalForceFields;
	std::string myEmitterName;
	std::string myChosenEmitter;
	std::string myChosenForceField;
	float myEmitCD;
	int myParticleAmount;
	std::shared_ptr<SB::Texture> myAtlasTexture;
	std::shared_ptr<SB::EmitterSettings> myEmitterSettings;
	std::shared_ptr<SB::ParticleEmitter> myEmitter;
	SB::ParticleForceField * myEditingForceField;
	unsigned short myChosenEmitterIndex;
	unsigned short myChosenForceFieldIndex;
	SB::Time myAutoSaveTimer;
	SB::Time mySaveTimer;
	SB::Time myDidntRenameTimer;
	SB::Time myAppliedTimer;
	SB::Time myDeletedTimer;
	int myNumberOfGridLines;
	float myDistanceBetweenGridLines;
	bool myShouldShowGrid;
	bool myShouldShowForceFields;
};


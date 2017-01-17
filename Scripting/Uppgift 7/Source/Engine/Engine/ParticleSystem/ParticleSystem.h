#pragma once
#include <Utilities\Container\StaticList.h>

const int MultiplicationFactor = 8;
const int MaxAmountParticles = 1024 * MultiplicationFactor; //Might need to lower
const int EightOfMax = (MaxAmountParticles * (MultiplicationFactor / 8));

namespace SB
{
	struct ForceFieldDying;
	struct ParticleForceField;
	class ParticleEmitter;
	struct EmitterSettings;

	struct ScheduledParticleCommand;
	struct ParticleDeltaInfo;
	struct ParticleData;
	struct ParticleLogic;

	class ParticleEffect;
	struct EndOfFrameMessage;

	class Texture;

	class ParticleSystem : public Subscriber<EndOfFrameMessage>
	{
	public:
		ParticleSystem( SB::Scene & aScene/*const unsigned short aMaxAmountOfParticles = 1024 * 8*/);
		~ParticleSystem();

		void Update(const Time & aDeltaTime);
		void RenderWorldParticles(const Camera & aCamera) const;

		void QueueParticle(const ScheduledParticleCommand aCommand);

		void SpawnQueuedParticles();

		void ShutDownCleanUp();

		std::shared_ptr<ParticleEmitter> CreateEmitter(const std::string & aEmitterType);
		std::shared_ptr<ParticleEmitter> CreateEmptyEmitter();

		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;

		Vector2f GetParticleAtlasSize() const;

		void RemoveEmitterType(const std::string & aName);
		void AddEmitterType(const EmitterSettings & someSettings, const std::string & aName);
		void ModifyEmitterType(const EmitterSettings & someSettings, const std::string & aNewName, const std::string & anOldName);
		void SaveEmitterTypes(const std::string & aFile) const;

		GrowingArray<std::string> GetEmitterNames() const;

		std::shared_ptr<Texture> GetAtlas();

		void RemoveLocalForceAfterTime(const unsigned short aIndex, const Time & aDyingTimer);

	protected:
		void UpdateForceFieldDeaths(const Time & aDeltaTime);
		void LoadParticleEmitterTypes();
		bool UpdateWorldParticle(const unsigned short anIndex, const Time & aDeltaTime);

		void ErrorCheckMinMaxValues(const Vector2f & aMinMaxVector, const std::string & anErrorMessage) const;

		SB::GrowingArray<ScheduledParticleCommand> myQueuedParticles;

		std::unordered_map<std::string, std::shared_ptr<EmitterSettings>> myEmitterTypes; //flyweight
		SB::StaticList<SB::GrowingArray<ParticleForceField>, EightOfMax> myLocalForceFields;
		SB::Stack<unsigned short> myFreeLocalForceFieldIndexes;
		SB::GrowingArray<ForceFieldDying> myQueuedForceFieldDeaths;

		//World Particles
		SB::StaticList<ParticleDeltaInfo, MaxAmountParticles> myParticleInstancesDeltaInfo;
		SB::StaticList<ParticleData, MaxAmountParticles> myParticleInstancesData;
		SB::StaticList<ParticleLogic, MaxAmountParticles> myParticleInstancesLogic;

		std::shared_ptr<VertexBuffer<ParticleData>> myVertexBuffer;
		std::shared_ptr<ParticleEffect> myEffect;

		std::shared_ptr<Texture> myTextureAtlas;

		SB::Scene * myScene;

	};

}
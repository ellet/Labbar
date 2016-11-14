#pragma once
#include <Utilities\Container\StaticList.h>

const int MaxAmountParticles = 1024 *8 ;

namespace ENGINE_NAMESPACE
{
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
		void Render() const;

		void QueueParticle(const ScheduledParticleCommand aCommand);

		void SpawnQueuedParticles();

		void ShutDownCleanUp();

		std::shared_ptr<ParticleEmitter> CreateEmitter(const std::string & aEmitterType);
		std::shared_ptr<ParticleEmitter> CreateEmptyEmitter();

		virtual ReceiveResult Receive(const EndOfFrameMessage & aMessage) override;

		Vector2f GetParticleAtlasSize() const;

		void RemoveEmitterType(const std::string & aName);
		void AddEmitterType(const EmitterSettings & someSettings, const std::string & aName);
		void SaveEmitterTypes() const;

		std::shared_ptr<Texture> GetAtlas();

	private:
		void LoadParticleEmitterTypes();
		bool UpdateParticle(const unsigned short anIndex, const Time & aDeltaTime);

		void ErrorCheckMinMaxValues(const Vector2f & aMinMaxVector, const std::string & anErrorMessage) const;

		SB::GrowingArray<ScheduledParticleCommand> myQueuedParticles;
		//Stack<unsigned short> myFreeMemorySlots;

		std::unordered_map<std::string, std::shared_ptr<EmitterSettings>> myEmitterTypes; //flyweight
		SB::GrowingArray<std::shared_ptr<ParticleEmitter>> myEmittersInstances;

		SB::StaticList<ParticleDeltaInfo, MaxAmountParticles> myParticleInstancesDeltaInfo;
		SB::StaticList<ParticleData, MaxAmountParticles> myParticleInstancesData;
		SB::StaticList<ParticleLogic, MaxAmountParticles> myParticleInstancesLogic;

		std::shared_ptr<VertexBuffer<ParticleData>> myVertexBuffer;
		std::shared_ptr<ParticleEffect> myEffect;

		std::shared_ptr<Texture> myTextureAtlas;

		SB::Scene * myScene;

		//unsigned short myMaxAmountOfParticles;
	};

}
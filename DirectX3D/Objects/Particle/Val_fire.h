#pragma once
class Val_fire
{
public:
	Val_fire();
	~Val_fire();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);
	void PlaySpark(Vector3 pos);

	void Stop();
	void ParticleRotate();

	bool IsActive() { return particle->IsActive(); }
	void SetParent(Transform* transform) { parent = transform; }
	void SetPos(Vector3 pos);
	void SetBurstPos(Vector3 pos);
	void SetVortex(Vector3 pos);
	void PlayExplosion();
	void PlaySpark();
	void FullBurstScale(Vector3 pos);

private:
	ParticleSystem* particle = nullptr;
	ParticleSystem* particle2 = nullptr;
	Sprite* sprite;
	ParticleSystem* explosionParticle = nullptr;

	Sprite* bulletExplosion1;
	Sprite* bulletExplosion2;
	Sprite* bulletExplosion3;
	Sprite* bulletExplosion4;
	Sprite* bulletSparkExplosion;

	ParticleSystem* burstparticle1 = nullptr;
	ParticleSystem* burstparticle2 = nullptr;


	float lifeTime = 0;
	Transform* parent = nullptr;
	Vector3 pos;
};


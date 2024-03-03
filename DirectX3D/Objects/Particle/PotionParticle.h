#pragma once
class PotionParticle
{
public:
	PotionParticle();
	~PotionParticle();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	bool IsActive() { return particle->IsActive(); }
	void SetParent(Transform* transform) { parent = transform; }	
	void SetPos(Vector3 pos);
	void SetVortex(Vector3 pos);

private:
	ParticleSystem* particle = nullptr;
	ParticleSystem* particle2 = nullptr;
	ParticleSystem* particle3 = nullptr;
	ParticleSystem* particle4 = nullptr;

	float lifeTime = 0;
	Transform* parent = nullptr;
	Vector3 pos;
};


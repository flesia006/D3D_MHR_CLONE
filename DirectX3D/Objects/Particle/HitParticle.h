#pragma once
class HitParticle
{
public:
	HitParticle();
	~HitParticle();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	bool IsActive() { return hit1->IsActive() && hit2->IsActive(); }

private:
	ParticleSystem* hit1 = nullptr;
	ParticleSystem* hit2 = nullptr;

	float lifeTime = 0;
};


#pragma once
class HitBoomParticle
{
public:
	HitBoomParticle();
	~HitBoomParticle();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	bool IsActive() { return hit->IsActive(); }

private:
	ParticleSystem* hit = nullptr;	

	float lifeTime = 0;
};


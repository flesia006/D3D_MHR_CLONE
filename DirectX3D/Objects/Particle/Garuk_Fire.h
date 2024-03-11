#pragma once
class Garuk_Fire
{
public:
	Garuk_Fire();
	~Garuk_Fire();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();
	void ParticleRotate();

	bool IsActive() { return smoke->IsActive(); }

private:
	ParticleSystem* smoke = nullptr;
	ParticleSystem* fire = nullptr;

	float lifeTime = 0;
};


#pragma once
class RoarEffect
{
public:
	RoarEffect();
	~RoarEffect();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);
	void roarCloserCam(Vector3 pos, Vector3 targetpos, float speed = 0.001f);

	void Stop();

	bool IsActive() { return roar->IsActive(); }

private:
	ParticleSystem* roar = nullptr;

	float lifeTime = 0;
};


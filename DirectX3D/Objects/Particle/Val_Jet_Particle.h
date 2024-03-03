#pragma once
class Val_Jet_Particle
{
public:
	Val_Jet_Particle();
	~Val_Jet_Particle();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	bool IsActive() { return jet->IsActive(); }

	void SetPos(Vector3 pos);


private:
	ParticleSystem* jet = nullptr;

	float lifeTime = 0;
};


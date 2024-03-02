#pragma once
class Sp_atk_ready_Particle
{
public:
	Sp_atk_ready_Particle();
	~Sp_atk_ready_Particle();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	bool IsActive() { return sp->IsActive() && halo->IsActive();}

private:
	ParticleSystem* sp;
	ParticleSystem* halo;

	float lifeTime = 0;
};


#pragma once
class Sp_atk_start
{
public:
	Sp_atk_start();
	~Sp_atk_start();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	bool IsActive() { return sp->IsActive() && sp1->IsActive(); }

private:
	ParticleSystem* sp;
	ParticleSystem* sp1;

	float lifeTime = 0;
};


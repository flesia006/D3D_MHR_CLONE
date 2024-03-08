#pragma once
class Sp_atk_success
{
public:
	Sp_atk_success();
	~Sp_atk_success();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();
	void SetPos(Vector3 pos);

	bool IsActive() { return sp->IsActive() && sp1->IsActive(); }

private:
	ParticleSystem* sp;
	ParticleSystem* sp1;

	float lifeTime = 0;
};


#pragma once
class Sutdol
{
public:
	Sutdol();
	~Sutdol();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);
	void PlayHalo(Vector3 pos);

	void Stop();
	void ParticleRotate();

	bool IsActive() { return spark->IsActive(); }
	void SetPos(Vector3 pos);

private:
	ParticleSystem* spark = nullptr;
	ParticleSystem* halo = nullptr;

	float lifeTime = 0;
};


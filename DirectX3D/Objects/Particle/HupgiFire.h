#pragma once
class HupgiFire
{
public:
	HupgiFire();
	~HupgiFire();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);

	void Stop();

	//bool IsActive() { return sprite->IsActive(); }

	//void SetPos(Vector3 pos);


private:
	//ParticleSystem* jet = nullptr;
	Sprite* sprite;
	float lifeTime = 0;
};


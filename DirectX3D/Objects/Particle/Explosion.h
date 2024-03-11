#pragma once
class Explosion
{
public:
	Explosion();
	~Explosion();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);
	void Play1(Vector3 pos, Vector3 rot);
	void Play2(Vector3 pos, Vector3 rot);
	void Play3(Vector3 pos, Vector3 rot);
	void PlaySpark(Vector3 pos, Vector3 rot);
	void PlaySmall(Vector3 pos, Vector3 rot);
	void Stop();

	void BulletExpoision(Vector3 pos, Vector3 rot);

	bool IsActive() { return explosionParticle->IsActive(); }

private:
	ParticleSystem* explosionParticle = nullptr;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	Sprite* sprite4;	
	Sprite* sprite5;
	Sprite* sprite6;
	Sprite* sprite7;
	Sprite* sprite8;
	Sprite* sprite9;
	Sprite* spark_sprite;

	Sprite* bulletExplosion1;
	Sprite* bulletExplosion2;
	Sprite* bulletExplosion3;
	Sprite* bulletExplosion4;

	float lifeTime = 0;
	bool on = false;
	float timer = 0;
};


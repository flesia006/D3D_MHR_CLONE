#pragma once
class FullBurstParticle2 : public Transform
{
public:
	FullBurstParticle2();
	~FullBurstParticle2();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);
	void PlaySpark(Vector3 pos, Vector3 rot);
	void PlaySpark2(Vector3 pos, Vector3 rot) { sprite2->Play(pos); }
	void PlaySpark3(Vector3 pos, Vector3 rot) { sprite3->Play(pos); }
	void PlaySpark4(Vector3 pos, Vector3 rot) { sprite4->Play(pos); }
	void PlaySpark5(Vector3 pos, Vector3 rot) { sprite5->Play(pos); }
	void PlaySpark6(Vector3 pos, Vector3 rot) { sprite6->Play(pos); }
	void SetPos(Vector3 pos);
	void Stop();
	void ParticleRotate();

	bool IsActive() { return hit->IsActive(); }
private:
	ParticleSystem* hit = nullptr;

	float timer = 0.0f;
	int num = 1;


	Vector3 zet1Scale;
	Vector3 zet2Scale;
	vector<Val_fire*> beamSpark;

	ParticleSystem* particle = nullptr;
	ParticleSystem* particle2 = nullptr;
	Sprite* sprite;
	Sprite* sprite2;
	Sprite* sprite3;
	Sprite* sprite4;
	Sprite* sprite5;
	Sprite* sprite6;


	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];


};


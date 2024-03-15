#pragma once
class FullBurstParticle : public Transform
{
public:
	FullBurstParticle();
	~FullBurstParticle();

	void Update();
	void Render();
	void GUIRender();

	void Play(Vector3 pos, Vector3 rot);
	void PlaySpark(Vector3 pos, Vector3 rot,int num);
	void Stop();
	void ParticleRotate();
	void PlayAlpha();
	void RepairZet();

	bool IsActive() { return hit->IsActive(); }
private:
	ParticleSystem* hit = nullptr;

	float timer = 0.0f;
	int num = 1;

	Quad* zet1;
	Quad* zet2;

	Vector3 zet1Scale;
	Vector3 zet2Scale;
	vector<Val_fire*> beamSpark;

	ParticleSystem* particle = nullptr;
	ParticleSystem* particle2 = nullptr;
	Sprite* sprite;


	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	
};


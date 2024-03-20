#pragma once
class UseBug
{
public:
	UseBug();
	~UseBug();

	void Update();
	void Render();
	void GUIRender();

	void Play1(Vector3 pos);
	void Play2(Vector3 pos);
	void Play3(Vector3 pos);
	void Play4(Vector3 pos);
	void Play5(Vector3 pos);
	void Play6(Vector3 pos);
	void Play7(Vector3 pos);
	void Play8(Vector3 pos);
	void Play9(Vector3 pos);
	void Play10(Vector3 pos);

	void Stop();

	bool IsActive() { return bugfinish->IsActive(); }
	void SetPos(Vector3 pos);

private:
	vector<ParticleSystem*> usebug;
	ParticleSystem* bugfinish = nullptr;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float lifeTime = 0;
};


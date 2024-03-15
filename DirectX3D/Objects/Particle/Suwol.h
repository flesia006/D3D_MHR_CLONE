#pragma once
class Suwol :public Transform
{
	const int count = 50;

public:
	Suwol();
	~Suwol();

	void EffectOn();
	void EffectOff();

	void Update();
	void Render();
	void GUIRender();

	bool active = false;
private:
	vector<Model*> suwol;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float timer = 0.0f;
	int num = 1;
};



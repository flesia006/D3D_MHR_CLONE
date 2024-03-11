#pragma once
class TuguEft :public Transform
{
public:
	TuguEft();
	~TuguEft();

	void Update();
	void Render();

	bool active = false;
private:
	Quad* tugu;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float timer = 0.0f;
	int num = 1;
};


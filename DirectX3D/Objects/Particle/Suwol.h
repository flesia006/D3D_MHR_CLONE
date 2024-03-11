#pragma once
class Suwol :public Transform
{
public:
	Suwol();
	~Suwol();


	void Update();
	void Render();
	void GUIRender();

private:
	Quad* suwol[30];

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float timer = 0.0f;
	int num = 1;
};



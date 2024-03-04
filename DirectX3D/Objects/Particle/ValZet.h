#pragma once

class ValZet :public Transform
{
public:
	ValZet();
	~ValZet();

	void Update();
	void Render();

private:
	Quad* zet1;
	Quad* zet2;


	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float timer = 0.0f;
	int num = 1;

};





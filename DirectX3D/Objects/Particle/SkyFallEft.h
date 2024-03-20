#pragma once
class SkyFallEft :public Transform
{
public:
	SkyFallEft();
	~SkyFallEft();

	void Update();
	void Render();
	void GUIRender();

	bool active = false;

private:
	Quad* zet1;
	Quad* zet2;
	Quad* zet3;
	Quad* zet4;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float timer = 0.0f;
	int num = 1;

};

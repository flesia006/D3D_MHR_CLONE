#pragma once
class SliceEft :public Transform
{
public:
	SliceEft();
	~SliceEft();

	void Update();
	void Render();

	bool active = false;
private:
	Cylinder2* v_circle;
	Ring* h_circle;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	RasterizerState* rasterizerState[2];

	float timer = 0.0f;
	int count = 0;
	int num = 1;
};


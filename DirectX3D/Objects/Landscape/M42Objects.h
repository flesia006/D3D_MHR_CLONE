#pragma once
class M42Objects
{
public:
	M42Objects();
	~M42Objects();

	void Update();
	void Render();
	void GUIRender();
	void SetShader(wstring path);

private:
	Model* ground;
	Model* castle;



	string basicTexPath = "Textures/M41";
	Vector3 basicPos = Vector3(2062.1f, 180, 17653.896f);

	const float unitRad = XM_PI / 180.0f;
	int num = 0;
};

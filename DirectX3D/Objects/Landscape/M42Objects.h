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

	Model* sm414_000_00;
	Model* sm414_001_00;
	ModelInstancing* sm414_002_00;
	Model* sm414_002_02;

	Model* sm414_003_00;
	Model* sm414_003_01;
	Model* sm414_003_02;
	Model* sm414_003_03;

	ModelInstancing* sm414_004_00;

	Model* sm414_007_00;

	ModelInstancing* sm414_003_07;

	Model* sm414_005_03;
	Model* sm414_005_00;
	Model* sm414_005_01;

	Model* tent;

	string basicTexPath = "Textures/M41";
	Vector3 basicPos = Vector3(2062.1f, 180, 17653.896f);

	const float unitRad = XM_PI / 180.0f;
	int num = 0;
};

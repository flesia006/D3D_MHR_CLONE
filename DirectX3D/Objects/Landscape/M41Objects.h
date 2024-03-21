#pragma once
class M41Objects
{
public:
	M41Objects();
	~M41Objects();

	void Update();
	void Render();
	void GUIRender();
	void SetShader(wstring path);

private:
	Model* M42A01;
	//Model* grass;
	Model* sm415_000_01;   //


	ModelInstancing* sm414_007_00;   //»ç°¢ ±âµÕ

	ModelInstancing* sm414_005_04;   // ¹ı±Ô ¸ğ¾ç º®

	Model* sm414_005_01;   // ¿ïÅüºÒÅü º®
	Model* sm414_005_01_2;   // ¿ïÅüºÒÅü º®

	ModelInstancing* sm414_005_02;   // ¿ïÅüºÒÅü º® 2
	ModelInstancing* sm414_009_00;

	string basicTexPath = "Textures/M41";
	Vector3 basicPos = Vector3(2062.1f, 180, 17653.896f);

	RasterizerState* rasterizerState[2];

	const float unitRad = XM_PI / 180.0f;
	int num = 0;
};


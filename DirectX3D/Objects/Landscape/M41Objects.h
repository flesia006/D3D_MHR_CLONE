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
	Model* grass;
	Model* sm415_000_01;   //
	Model* sm414_007_00;   //»ç°¢ ±âµÕ
	Model* sm414_007_00_2;

	Model* sm414_005_04;   // ¹ý±Ô ¸ð¾ç º®

	Model* sm414_005_01;   // ¿ïÅüºÒÅü º®
	Model* sm414_005_01_2;   // ¿ïÅüºÒÅü º®


	string basicTexPath = "Textures/M41";
	Vector3 basicPos = Vector3(2062.1f, 180, 17653.896f);

	int num = 0;
};


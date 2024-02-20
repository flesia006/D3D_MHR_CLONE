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


	Model* sm415_000_01;

	string basicTexPath = "Textures/M41";
	Vector3 basicPos = Vector3(2062.1f, 180, 17653.896f);

};


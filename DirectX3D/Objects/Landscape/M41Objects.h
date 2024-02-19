#pragma once
class M41Objects
{
public:
	M41Objects();
	~M41Objects();

	void Update();
	void Render();
	void GUIRender();


private:
	Model* forest;

	Model* tikei10;
	Model* tikei4;

};


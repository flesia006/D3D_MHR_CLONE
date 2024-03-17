#pragma once
class headBreakAtk
{

public:
	headBreakAtk();
	~headBreakAtk();

	void Update();
	void PostRender();

	bool active = false;
private:
	Quad* cut = nullptr;


};


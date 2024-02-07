#pragma once
class Valphalk : public ModelAnimator
{
public:
	Valphalk();
	~Valphalk();


	void Update();
	void PreRender();
	void Render();
	void GUIRender();
	void PostRender();

	SphereCollider* GetHead() { return headCollider; }

private:
	SphereCollider* headCollider = nullptr;
	Transform* head = nullptr;

	int node = 14;
};



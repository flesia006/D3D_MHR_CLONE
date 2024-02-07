#include "Framework.h"
#include "Valphalk.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{

	ReadClip("stun");
	headCollider = new SphereCollider(80);
	headCollider->SetColor({ 1, 0, 0, 1 });
}

Valphalk::~Valphalk()
{
	delete head;
	delete headCollider;
}

void Valphalk::Update()
{
	headCollider->Pos() = GetTranslationByNode(node);
	headCollider->UpdateWorld();
	ModelAnimator::Update();
}

void Valphalk::PreRender()
{


}

void Valphalk::Render()
{
	ModelAnimator::Render();
	headCollider->Render();
}

void Valphalk::GUIRender()
{
	ModelAnimator::GUIRender();
	ImGui::SliderInt("Val_node", &node, 0, 100);
}

void Valphalk::PostRender()
{

}

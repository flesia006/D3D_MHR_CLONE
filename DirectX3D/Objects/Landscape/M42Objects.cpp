#include "Framework.h"
#include "M42Objects.h"

M42Objects::M42Objects()
{
	ground = new Model("M42Ground");
	ground->Pos().y -= 56890;
	ground->UpdateWorld();
	ground->GetMaterials()[15]->SetShader(L"Basic/Texture2.hlsl");
	ground->GetMaterials()[28]->SetShader(L"Basic/Texture2.hlsl");
	ground->GetMaterials()[29]->SetShader(L"Basic/Texture2.hlsl");
	ground->GetMaterials()[31]->SetShader(L"Basic/Texture2.hlsl");
	ground->GetMaterials()[35]->SetShader(L"Basic/Texture2.hlsl");

	castle = new Model("castle");
	castle->SetTag("castle");
	castle->Pos() = { 0, 3000, -3330 };
	castle->Rot().y += XM_PI;
	castle->GetMaterials()[3]->SetShader(L"Basic/Texture2.hlsl");
	castle->UpdateWorld();

}

M42Objects::~M42Objects()
{
}

void M42Objects::Update()
{
	ground->UpdateWorld();
	castle->UpdateWorld();
}

void M42Objects::Render()
{
	ground->Render();
	castle->Render();
}

void M42Objects::GUIRender()
{
	ground->GUIRender();
	castle->GUIRender();
}

void M42Objects::SetShader(wstring path)
{
}

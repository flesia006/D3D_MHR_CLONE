#include "Framework.h"
#include "M41Objects.h"

M41Objects::M41Objects()
{
    M42A01 = new Model("M42A01");
    M42A01->Pos() = basicPos;
    M42A01->Rot().y = XM_PI;
    M42A01->UpdateWorld();

    sm415_000_01 = new Model("sm415_000_01");
    sm415_000_01->SetTag("sm415_000_01");
    sm415_000_01->Pos() = Vector3(65000, 3000, 3500);
    sm415_000_01->Rot().y = XM_PI;
    sm415_000_01->UpdateWorld();

}

M41Objects::~M41Objects()
{
}

void M41Objects::Update()
{

}

void M41Objects::Render()
{
    //M42A01->SetShader(L"Light/Shadow.hlsl");

    sm415_000_01->Render();
    M42A01->Render();

}

void M41Objects::GUIRender()
{
    M42A01->GUIRender();
//    sm415_000_01->GUIRender();
}

void M41Objects::SetShader(wstring path)
{
    M42A01->SetShader(path);
    sm415_000_01->SetShader(path);
}

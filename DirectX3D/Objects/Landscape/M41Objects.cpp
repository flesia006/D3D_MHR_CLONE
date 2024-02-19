#include "Framework.h"
#include "M41Objects.h"

M41Objects::M41Objects()
{
    forest = new Model("GroundAll(fix)");
    forest->Pos() = Vector3(2062.1f, 180, 17653.896f);
    forest->Rot().y = XM_PI;
    forest->UpdateWorld();

    tikei10 = new Model("tikei10");
    tikei10->Pos() = Vector3(2389.8f, 159, 17597);
    tikei10->Rot().y = XM_PI;
    tikei10->UpdateWorld();

    tikei4 = new Model("tikei4");
    tikei4->Pos() = Vector3(2163, 189, 17383.4f);
    tikei4->Rot().y = XM_PI;
    tikei4->UpdateWorld();

}

M41Objects::~M41Objects()
{
}

void M41Objects::Update()
{
    tikei10->UpdateWorld();
    tikei4->UpdateWorld();
}

void M41Objects::Render()
{
    forest->SetShader(L"Light/Shadow.hlsl");
    forest->Render();
    tikei10->Render();
    tikei4->Render();
}

void M41Objects::GUIRender()
{
    //forest->GUIRender();
    //tikei10->GUIRender();
    tikei4->GUIRender();
}

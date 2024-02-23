#include "Framework.h"
#include "M41Objects.h"

M41Objects::M41Objects()
{
    M42A01 = new Model("ground");
    M42A01->Pos() = basicPos;
    M42A01->Rot().y = XM_PI;
    M42A01->UpdateWorld();

    grass = new Model("grass");
    grass->Pos() = basicPos;
    grass->Rot().y = XM_PI;
    grass->UpdateWorld();

    sm415_000_01 = new Model("sm415_000_01");
    sm415_000_01->SetTag("sm415_000_01");
    sm415_000_01->Pos() = Vector3(65000, 3000, 3500);
    sm415_000_01->Rot().y = XM_PI;
    sm415_000_01->UpdateWorld();

    sm414_007_00 = new Model("sm414_007_00");
    sm414_007_00->SetTag("sm414_007_00");
    sm414_007_00->Pos() = Vector3(5755, 153.3, 1526.3);
    sm414_007_00->Rot() = Vector3(0, XM_PIDIV2, -0.12);
    sm414_007_00->UpdateWorld();

    sm414_005_04 = new Model("sm414_005_04");
    sm414_005_04->SetTag("sm414_005_04");
    sm414_005_04->Pos() = Vector3(3809, 231.7, 395.1);
    sm414_005_04->Rot() = Vector3(0.034, XM_PI, 0);
    sm414_005_04->UpdateWorld();
}

M41Objects::~M41Objects()
{
}

void M41Objects::Update()
{
    sm414_005_04->UpdateWorld();
}

void M41Objects::Render()
{
    //M42A01->SetShader(L"Light/Shadow.hlsl");

    sm415_000_01->Render();
    sm414_007_00->Render();
    sm414_005_04->Render();
    M42A01->Render();

    grass->SetShader(L"Basic/Texture2.hlsl");
    grass->Render();

}

void M41Objects::GUIRender()
{
        M42A01->GUIRender();
        //sm414_007_00->GUIRender();
    //sm414_005_04->GUIRender();
    //    sm415_000_01->GUIRender();
}

void M41Objects::SetShader(wstring path)
{
    M42A01->SetShader(path);
    sm415_000_01->SetShader(path);
}

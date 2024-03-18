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

	sm414_003_02 = new Model("sm414_003_02");
	sm414_003_02->Pos() = { 2614, 70.7, 4000 };
	sm414_003_02->GetMaterials()[3]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_02->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_02->Rot().y += XM_PI;
	sm414_003_02->UpdateWorld();

	sm414_000_00 = new Model("sm414_000_00");
	sm414_000_00->Pos() = { 2363.2, 12, 2229.5 };
	sm414_000_00->Rot().y = XM_PIDIV2;
	sm414_000_00->GetMaterials()[6]->SetShader(L"Basic/Texture2.hlsl");
	sm414_000_00->UpdateWorld();

	sm414_001_00 = new Model("sm414_001_00");
	sm414_001_00->Pos() = { -3219.5, -68, 3066.2 };
	sm414_001_00->Rot().y = -XM_PIDIV2;
	sm414_001_00->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
	sm414_001_00->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
	sm414_001_00->UpdateWorld();

	sm414_002_00 = new ModelInstancing("sm414_002_00");
	{
		{// 0
			Transform* t = sm414_002_00->Add();
			t->Pos() = Vector3(-1693.4, 0, 596.6);
			t->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
		}

		{// 1
			Transform* t = sm414_002_00->Add();
			t->Pos() = Vector3(-2232.8, 0, 1343.1);
			t->Rot() = { 0 * unitRad, -104 * unitRad, 0 };
		}

		{// 2
			Transform* t = sm414_002_00->Add();
			t->Pos() = Vector3(1732.8, 0, 698.5);
			t->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
		}

		{// 3
			Transform* t = sm414_002_00->Add();
			t->Pos() = Vector3(1976.4, 0, 835.5);
			t->Rot() = { 0 * unitRad, 90 * unitRad, 0 };
		}
		sm414_002_00->Update();
	}

	sm414_002_02 = new Model("sm414_002_02");
	sm414_002_02->Pos() = { 1942.8, -60.5, 2984.6 };
	sm414_002_02->Rot().y = 90 * unitRad;
	sm414_002_02->UpdateWorld();

	sm414_003_00 = new Model("sm414_003_00");
	sm414_003_00->Pos() = { -3761, 835.8, 752 };
	sm414_003_00->Rot().y = XM_PI;
	sm414_003_00->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_00->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_00->UpdateWorld();

	sm414_003_01 = new Model("sm414_003_01");
	sm414_003_01->Pos() = { 2595.8, 1326.5, 249.7 };
	sm414_003_01->Rot().y = XM_PI;
	sm414_003_01->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_01->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_01->UpdateWorld();

	sm414_003_03 = new Model("sm414_003_03");
	sm414_003_03->Pos() = { -3116.7, 847.0, 4453.6 };
	sm414_003_03->Rot().y = XM_PI;
	sm414_003_03->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_03->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
	sm414_003_03->UpdateWorld();

	sm414_004_00 = new ModelInstancing("sm414_004_00");
	sm414_004_00->SetMap(basicTexPath);
	{
		{// 0
			Transform* t = sm414_004_00->Add();
			t->Pos() = Vector3(-673.5, 0, 596.6);
			t->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
		}

		{// 1
			Transform* t = sm414_004_00->Add();
			t->Pos() = Vector3(-2006.8, 0.6, 611.1);
			t->Rot() = { 0 * unitRad, -104 * unitRad, 0 };
		}

		{// 2
			Transform* t = sm414_004_00->Add();
			t->Pos() = Vector3(642.4, 0, 698.5);
			t->Rot() = { 0 * unitRad, 180 * unitRad, 0 };
		}

		{// 3
			Transform* t = sm414_004_00->Add();
			t->Pos() = Vector3(1976.4, 0, 835.5);
			t->Rot() = { 0 * unitRad, 90 * unitRad, 0 };
		}

		{// 4
			Transform* t = sm414_004_00->Add();
			t->Pos() = Vector3(-2341, 0, 1587.8);
			t->Rot() = { 0 * unitRad, -104 * unitRad, 0 };
		}
		sm414_004_00->Update();
	}


	sm414_007_00 = new Model("sm414_007_00");
	sm414_007_00->Pos() = { 3150, 238, 3554 };
	sm414_007_00->Rot() = { 90 * unitRad, -75 * unitRad, 0 };
	sm414_007_00->UpdateWorld();


	sm414_003_07 = new ModelInstancing("sm414_003_07");
	{
		{// 0
			Transform* t = sm414_003_07->Add();
			t->Pos() = Vector3(-2625.7, 9, 3600.4);
			t->Rot() = { 0 * unitRad, 90 * unitRad, 0 };
		}

		{// 1
			Transform* t = sm414_003_07->Add();
			t->Pos() = Vector3(-2593.8, 0.0, 2480.3);
			t->Rot() = { 0 * unitRad, -104 * unitRad, 0 };
		}
		sm414_003_07->Update();
	}

	sm414_005_03 = new Model("sm414_005_03");
	sm414_005_03->Pos() = { -187.4, 0, 4168.5 };
	sm414_005_03->Rot().y = 175 * unitRad;
	sm414_005_03->GetMaterials()[0]->SetShader(L"Basic/Texture2.hlsl");
	sm414_005_03->UpdateWorld();

	sm414_005_00 = new Model("sm414_005_00");
	sm414_005_00->Pos() = { -1112.6, 0, 4109.5 };
	sm414_005_00->Rot().y = -XM_PI;
	sm414_005_00->SetMap(basicTexPath);
	sm414_005_00->UpdateWorld();

	sm414_005_01 = new Model("sm414_005_01");
	sm414_005_01->Pos() = { -2519.2, 0, 3910.2 };
	sm414_005_01->Rot().y = 164 * unitRad;
	sm414_005_01->GetMaterials()[4]->SetShader(L"Basic/Texture2.hlsl");
	sm414_005_01->GetMaterials()[5]->SetShader(L"Basic/Texture2.hlsl");
	sm414_005_01->UpdateWorld();

	tent = new Model("tent");
	tent->Pos() = { -649.1, 61.2, 2390.7 };
	tent->Rot().y = -153 * unitRad;
	tent->UpdateWorld();

	
}

M42Objects::~M42Objects()
{
}

void M42Objects::Update()
{
}

void M42Objects::Render()
{
	ground->Render();
	castle->Render();
	sm414_003_02->Render();
	sm414_000_00->Render();
	sm414_001_00->Render();
	sm414_002_00->Render();
	sm414_002_02->Render();
	sm414_003_00->Render();
	sm414_003_01->Render();
	sm414_003_03->Render();
	sm414_004_00->Render();
	sm414_007_00->Render();
	sm414_003_07->Render();
	sm414_005_03->Render();
	sm414_005_00->Render();
	sm414_005_01->Render();
	tent->Render();
}

void M42Objects::GUIRender()
{
//	tent->GUIRender();
//	sm414_005_01->GUIRender();
//	sm414_005_00->GUIRender();
//	sm414_005_03->GUIRender();
//	sm414_003_07->GUIRender();
//	sm414_007_00->GUIRender();
//	sm414_004_00->GUIRender();
//	sm414_003_03->GUIRender();
//	sm414_003_01->GUIRender();
//	sm414_003_00->GUIRender();
//	sm414_002_02->GUIRender();
//	sm414_002_00->GUIRender();
//	sm414_001_00->GUIRender();
//	ground->GUIRender();
//	sm414_000_00->GUIRender();
//	castle->GUIRender();
//	sm414_003_02->GUIRender();
}

void M42Objects::SetShader(wstring path)
{
}

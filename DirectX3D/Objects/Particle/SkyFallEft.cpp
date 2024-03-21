#include "Framework.h"
#include "SkyFallEft.h"

SkyFallEft::SkyFallEft()
{
	zet1 = new Quad(L"Textures/Effect/fire.tga");
	zet2 = new Quad(L"Textures/Effect/fire.tga");
	zet3 = new Quad(L"Textures/Effect/fire.tga");
	zet4 = new Quad(L"Textures/Effect/fire.tga");

	zet1->Scale() *= 15;
	zet1->Scale().y *= 1.7;
	zet1->Pos().y += 3000;
	zet1->SetParent(this);
	zet1->UpdateWorld();

	zet2->Scale() *= 15;
	zet2->Scale().y *= 1.7;
	zet2->Pos().y += 3000;
	zet2->Rot().y += XM_PIDIV2;
	zet2->SetParent(this);
	zet2->UpdateWorld();

	zet3->Scale() *= 20;
	zet3->Scale().y *= 1.7;
	zet3->Pos().y += 6000;
	zet3->Rot().y += XM_PIDIV4;
	zet3->SetParent(this);
	zet3->UpdateWorld();

	zet4->Scale() *= 20;
	zet4->Scale().y *= 1.7;
	zet4->Pos().y += 6000;
	zet4->Rot().y -= XM_PIDIV4;
	zet4->SetParent(this);
	zet4->UpdateWorld();

	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	FOR(2) rasterizerState[i] = new RasterizerState();

	//blendState[1]->Alpha(true);
	blendState[1]->Additive();
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	//depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);
	rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

SkyFallEft::~SkyFallEft()
{
}

void SkyFallEft::Update()
{
	if (active)
	{
		zet1->Rot().y += 105 * DELTA;
		zet2->Rot().y += 105 * DELTA;
		zet3->Rot().y -= 105 * DELTA;
		zet4->Rot().y -= 105 * DELTA;

		zet1->UpdateWorld();
		zet2->UpdateWorld();
		zet3->UpdateWorld();
		zet4->UpdateWorld();
		Transform::UpdateWorld();
	}

}

void SkyFallEft::Render()
{
	if (active)
	{
		blendState[1]->SetState();
		depthState[1]->SetState();
		rasterizerState[1]->SetState();
		zet1->Render();
		zet2->Render();
		zet3->Render();
		zet4->Render();
		blendState[0]->SetState();
		depthState[0]->SetState();
		rasterizerState[0]->SetState();
	}

}

void SkyFallEft::GUIRender()
{
	Transform::GUIRender();
}

#include "Framework.h"
#include "SimpleTestScene.h"

SimpleTestScene::SimpleTestScene()
{
	half = new HalfSphere(1000, 32, 2);
	ring = new Cylinder2(500, 1000, 32);
	ring->GetMaterial()->SetShader(L"Basic/Texture.hlsl");

	suwol = new Suwol();
	breath = new Model("breath");
	breath->SetTag("breath");
	val = new ValZet();
	cut = new Quad(L"Textures/Effect/critical.png");
	//cut->Pos() = 

	FOR(breath->GetMaterials().size())
		breath->GetMaterials()[i]->SetShader(L"Basic/Texture.hlsl");

	slice = new SliceEft();

	FOR(2) rasterizerState[i] = new RasterizerState();
	FOR(2) blendState[i] = new BlendState();
	blendState[1]->Alpha(true);
	rasterizerState[1]->CullMode(D3D11_CULL_NONE);
	depthState[0] = new DepthStencilState();
	depthState[1] = new DepthStencilState();
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

}

SimpleTestScene::~SimpleTestScene()
{

}

void SimpleTestScene::Update()
{
	ring->UpdateWorld();

	if(KEY_DP('4'))
		slice->active = true;


	cut->UpdateWorld();

	slice->Update();
}

void SimpleTestScene::PreRender()
{
}

void SimpleTestScene::Render()
{
	//val->Render();
	rasterizerState[1]->SetState();
	blendState[1]->SetState();
	depthState[1]->SetState();
	//breath->Render();
	//half->Render();
	//ring->Render();
	//slice->Render();
	//suwol->Render();
	blendState[0]->SetState();
	depthState[0]->SetState();
	rasterizerState[0]->SetState();
}

void SimpleTestScene::PostRender()
{
}

void SimpleTestScene::GUIRender()
{
	//suwol->GUIRender();
	//ring->GUIRender();
	//breath->GUIRender();
	//val->GUIRender();
	slice->GUIRender();
}

#include "Framework.h"
#include "LoadingScene.h"

LoadingScene::LoadingScene()
{
    loading = new Quad(L"Textures/UI/Loading.png");
    loading->Pos() = CAM->Forward() * 1800;
    loading->Scale() *= 4.1f;
    loading->Pos() = { 3730.f,6.2f,1655.f };
    //lobby->Scale().x = WIN_WIDTH;
    //lobby->Scale().z = WIN_HEIGHT;    

    icon = new Quad(L"Textures/UI/LoadingIcon.png");
    nowloading = new Quad(L"Textures/UI/NOWLOADING.png");
    icon->Pos() = { 293.2f,-133.7f,469.565f };
    icon->Scale() = { 0.5f,0.5f,1 };

    FOR(2) blendState[i] = new BlendState(); //ºí·»µå
    FOR(2) depthState[i] = new DepthStencilState(); //µª½º

    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);

    //CAM->Pos().y += 10000;
    
    
    loading->Pos().x = +3500;//CAM->GlobalPos().x + CAM->Forward().x * 2530;
    //icon->Pos() = CAM->GlobalPos() + CAM->Forward() * 1630;
    
  
    //icon->Pos().x = -166.6f;
    //icon->Pos().y = 9875.2f;
    //icon->Pos().z = -41934.484f;
    icon->Pos() = { 359.1, 9842.3f,594.f };
    nowloading->Pos() = { 297.4,9797.3,594.f };
    nowloading->Scale() = { 0.25f,0.25f,1 };
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update()
{
    CAM->Pos() = { 0,10000,0 };
    CAM->Rot() = 0;
    loading->Pos().y = CAM->GlobalPos().y + CAM->Forward().y * 1620;
    loading->Pos().z = CAM->GlobalPos().z + CAM->Forward().z * 1630;
    //icon->Pos().x = CAM->GlobalPos().x + CAM->Forward().x * 1030;
    //icon->Pos().y = CAM->GlobalPos().y + CAM->Forward().y * 1030;
    //icon->Pos().z = CAM->GlobalPos().z + CAM->Forward().z * 1030;
    //CAM->Pos().y = 10000;
    //CAM->Rot() = 0;
    loading->Pos().x -= 100 * DELTA;
    icon->Rot().z -= 4 * DELTA;

    timer += DELTA;
    Float4 color = nowloading->GetMaterial()->GetData().diffuse;
    if (timer <= 0.8f)
    {
        color.w -= 0.5f * DELTA;
    }
    else if (timer >= 0.8f)
    {
        color.w += 0.5f * DELTA;
    }
    nowloading->GetMaterial()->SetDiffuseMapColor(color);
    if (timer >= 1.6f)
        timer = 0;

    loading->UpdateWorld();
    icon->UpdateWorld();    
    nowloading->UpdateWorld();

    if (UIManager::Get()->choice >= 100)
        UIManager::Get()->choice++;
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
    blendState[1]->SetState();
    depthState[1]->SetState();
    loading->Render();
    nowloading->Render();
    icon->Render();
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void LoadingScene::PostRender()
{    
    

}

void LoadingScene::GUIRender()
{
    //loading->GUIRender();
    //icon->GUIRender();
    ImGui::Text("%d", UIManager::Get()->choice);
    nowloading->GUIRender();
}

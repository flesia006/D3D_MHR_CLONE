#include "Framework.h"
#include "OpeningScene.h"

OpeningScene::OpeningScene()
{
    lobby = new Quad(L"Textures/UI/lobby.png");
    lobby->Scale() *= 2;
    //lobby->Scale().x = WIN_WIDTH;
    //lobby->Scale().z = WIN_HEIGHT;
    Sounds::Get()->AddSound("lobbyBGM", SoundPath + L"lobbyBGM.mp3", true);
    Sounds::Get()->Play("lobbyBGM", 0.1f);
    select = new Quad(L"Textures/UI/SelectBar.png");
    FOR(6)menuBar.push_back(new Quad(L"Textures/UI/menuBar.png"));

    FOR(menuBar.size())
    {
        menuBar[0]->Pos() = { 179.2f, 9973.8f, 469.565f };
        menuBar[1]->Pos() = { 179.2f, 9955.8f, 469.565f };
        menuBar[2]->Pos() = { 179.2f, 9937.8f, 469.565f };
        menuBar[3]->Pos() = { 179.2f, 9919.8f, 469.565f };
        menuBar[4]->Pos() = { 179.2f, 9901.8f, 469.565f };
        menuBar[5]->Pos() = { 179.2f, 9883.8f, 469.565f };
    }
    FOR(menuBar.size())menuBar[i]->Scale() = { 0.7,0.6,1 };
    //select->Pos() = { 162.1f,-26.3f,469.565f };
    select->Pos() = { 179.2f,9974.7f,469.565f };
    select->Scale() = { .9f,.6f,1 };
    
    //select->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
    CAM->Pos().y += 10000;
    lobby->Pos().y += 10000;
    //select->Pos().y += 10000;

    FOR(2) blendState[i] = new BlendState(); //블렌드
    FOR(2) depthState[i] = new DepthStencilState(); //뎁스

    blendState[1]->Alpha(true);
    //blendState[1]->AlphaToCoverage(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

OpeningScene::~OpeningScene()
{
}

void OpeningScene::Update()
{
    Float4 color = select->GetMaterial()->GetData().diffuse;
    timer += DELTA;

    if (timer <= 0.8f)
    {
        color.w -= 0.25f * DELTA; //=> 예가 알파                             
    }
    if (timer >= .8f)
    {
        color.w += 0.25f * DELTA;        
    }
    if (timer >= 1.6f)
    {
        timer = 0.0f;
    }

    select->GetMaterial()->SetDiffuseMapColor(color);

    CAM->Pos() = { 0,10000,0 };
    CAM->Rot() = 0;
    lobby->Pos() = CAM->GlobalPos() + CAM->Forward() * 1630;//CAM->Forward() * 1630;
    lobby->UpdateWorld();
    select->UpdateWorld();    
    
    FOR(menuBar.size())menuBar[i]->UpdateWorld();


    if (!isEnd)
    {
        for (int key = 0; key < 256; ++key)
        {
            if (GetAsyncKeyState(key) & 0x8000)
            {
                Sounds::Get()->Play("gameStart", 0.8f);
                isEnd = true;
            }
        }
    }
    else if (KEY_DOWN(VK_SPACE) && selectNum == 0 && isEnd == true)
    {
        Sounds::Get()->Play("playgame", 0.5f);
        UIManager::Get()->choice = 1;
    }

    if (KEY_DOWN(VK_SPACE) && selectNum > 0 && selectNum < 5)
    {
        Sounds::Get()->Play("dontget", 0.5f);        
    }
    if (KEY_DOWN(VK_SPACE) && selectNum == 5)
    {
        Sounds::Get()->Play("select", 0.5f);
        UIManager::Get()->choice = 6;
    }





    if (KEY_DOWN('W') && selectNum > 0)
    {
        Sounds::Get()->Play("select", 0.5f);
        select->Pos().y += 18;
        selectNum--;
    }
    if (KEY_DOWN('S') && selectNum < 5)
    {
        Sounds::Get()->Play("select", 0.5f);
        select->Pos().y -= 18;
        selectNum++;
    }
    
}


void OpeningScene::PreRender()
{
}

void OpeningScene::Render()
{
    blendState[1]->SetState();
    depthState[1]->SetState();

    lobby->Render();
    select->Render();
    if (isEnd)
    {
        FOR(menuBar.size())menuBar[i]->Render();

        if (selectNum == 0) menuBar[0]->SetActive(false); else menuBar[0]->SetActive(true);
        if (selectNum == 1) menuBar[1]->SetActive(false); else menuBar[1]->SetActive(true);
        if (selectNum == 2) menuBar[2]->SetActive(false); else menuBar[2]->SetActive(true);
        if (selectNum == 3) menuBar[3]->SetActive(false); else menuBar[3]->SetActive(true);
        if (selectNum == 4) menuBar[4]->SetActive(false); else menuBar[4]->SetActive(true);
        if (selectNum == 5) menuBar[5]->SetActive(false); else menuBar[5]->SetActive(true);
    }
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void OpeningScene::PostRender()
{    
    Font::Get()->SetStyle("Default");
    Font::Get()->SetColor("Black");
    
 
    if (!isEnd)
    {
        Font::Get()->RenderText("아무 버튼이나 누르세요", { WIN_WIDTH - 401, WIN_HEIGHT / 2.3f - 1 });
        Font::Get()->RenderText("아무 버튼이나 누르세요", { WIN_WIDTH - 399, WIN_HEIGHT / 2.3f + 1 });
        Font::Get()->SetColor("White");
        Font::Get()->RenderText("아무 버튼이나 누르세요", { WIN_WIDTH - 400, WIN_HEIGHT / 2.3f }); //{ valphalkStateIcon1->Pos().x - 68, valphalkStateIcon1->Pos().y - 15 });
    }
    if (isEnd == true)
    {
        Font::Get()->SetColor("White");
        Font::Get()->RenderText("새 게임", { WIN_WIDTH - 398, WIN_HEIGHT / 2.3f - 1 });
        Font::Get()->SetColor("RealGray");
        Font::Get()->RenderText("계속하기", { WIN_WIDTH - 401, WIN_HEIGHT / 2.3f - 51 });
        Font::Get()->RenderText("옵션", { WIN_WIDTH - 401, WIN_HEIGHT / 2.3f - 101 });        
        Font::Get()->RenderText("사용설명서", { WIN_WIDTH - 401, WIN_HEIGHT / 2.3f - 151 });
        Font::Get()->RenderText("크레디트", { WIN_WIDTH - 401, WIN_HEIGHT / 2.3f - 201 });
        Font::Get()->SetColor("White");
        Font::Get()->RenderText("QUIT", { WIN_WIDTH - 410, WIN_HEIGHT / 2.3f - 251 });
    }

    Font::Get()->SetColor("Black");
    Font::Get()->AddStyle("White", L"Arial", 22, DWRITE_FONT_WEIGHT_MEDIUM);
    Font::Get()->RenderText("Developed : 임문이최", { WIN_WIDTH - 102, WIN_HEIGHT / 2.3f - 352 });
    Font::Get()->SetColor("White");
    Font::Get()->AddStyle("White", L"Arial", 20, DWRITE_FONT_WEIGHT_MEDIUM);
    Font::Get()->RenderText("Developed : 임문이최", { WIN_WIDTH - 101, WIN_HEIGHT / 2.3f - 351 });
}

void OpeningScene::GUIRender()
{
    select->GUIRender();
    ImGui::Text("%d", selectNum);
    //FOR(menuBar.size())menuBar[i]->GUIRender();
}

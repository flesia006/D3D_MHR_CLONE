#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    //particle = new ParticleSystem(L"Textures/Effect/star.png");
    //particle = new Rain(); //비 인스턴스 생성 (하고 파티클로 사용)
    //particle = new Sprite(L"Textures/Effect/explosion.png", 30, 30, 5, 3, true);
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 30, 8, 2, true);
    particle = new ParticleSystem2("TextData/Particles/hupgi_charge.fx");
    particle->Play({ 0, 0, 0 }, {0, 1, 0});
    //sprite = new Sprite(L"Textures/Effect/temp5.png", 500, 500, 5, 4, false);
    //sprite2 = new Sprite(L"Textures/Effect/temp5.png", 500, 500, 5, 4, false);
    //sprite3 = new Sprite(L"Textures/Effect/temp5.png", 500, 500, 5, 4, false);
    //sprite4 = new Sprite(L"Textures/Effect/temp5.png", 500, 500, 5, 4, false);
    //sprite5 = new Sprite(L"Textures/Effect/temp5.png", 500, 500, 5, 4, false);
    //sprite6 = new Sprite(L"Textures/Effect/temp1.png", 500, 500, 8, 6, false);
    //sprite3 = new Sprite(L"Textures/Effect/explosion_3.png", 500, 500, 4, 8, false);
    //sprite4 = new Sprite(L"Textures/Effect/explosion_4.png",500,500,4,8,false);
    collider = new SphereCollider(30);
    //wind = new Wind(); 
    
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
}

void ParticleScene::Update()
{
    //sprite->SetColor({ 0,0,0,1 });
    //sprite2->SetColor({ 0,0,0,1 });
    //sprite3->SetColor({ 0,0,0,1 });

    Ray ray;
    Contact contact;
    if (KEY_DOWN(VK_LBUTTON))
    {
        ray = CAM->ScreenPointToRay(mousePos);
        contact;

        if (collider->IsRayCollision(ray, &contact))
        {
            particle->Play(contact.hitPoint, {0, 0, 0});
            //sprite->Play(contact.hitPoint);
            //sprite3->Play(contact.hitPoint);
            //timer++;
        }
    }/*
    if (timer >= 1)
    {
        on = true;
    }
    if (on == true)
        timer += DELTA;

    if (timer >= 2.29 && timer < 2.3)
    {
        sprite->Play(contact.hitPoint);
        sprite6->Play(contact.hitPoint);
        sprite5->Play({ contact.hitPoint.x - 50,contact.hitPoint.y - 50,contact.hitPoint.z + 0 });
    }
    if (timer >= 2.36 && timer < 2.39)
    {
        sprite2->Play({ contact.hitPoint.x - 50,contact.hitPoint.y + 50,contact.hitPoint.z + 0 });
        sprite3->Play({ contact.hitPoint.x + 50,contact.hitPoint.y - 50,contact.hitPoint.z + 0 });
    }
    if (timer >= 2.49 && timer < 2.5)
    {
        sprite4->Play({ contact.hitPoint.x - 50,contact.hitPoint.y + 50,contact.hitPoint.z + 0 });
        sprite2->Play({ contact.hitPoint.x + 50,contact.hitPoint.y + 50,contact.hitPoint.z + 0 });
    }
    if (timer > 2.6)
    {
        timer = 0;
        on = false;
    }*/


    //sprite->Update();
    //sprite2->Update();
    //sprite3->Update();
    //sprite4->Update();
    //sprite5->Update();
    //sprite6->Update();
    particle->Update();
    //wind->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    //sprite6->Render();
    particle->Render();
    collider->Render();
    //sprite->Render();
    //sprite2->Render();
    //sprite3->Render();
    //sprite4->Render();
    //sprite5->Render();
    //wind->Render();
}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    //sprite->GUIRender();
}

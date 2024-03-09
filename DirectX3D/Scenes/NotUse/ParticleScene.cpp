#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    //particle = new ParticleSystem(L"Textures/Effect/star.png");
    //particle = new Rain(); //비 인스턴스 생성 (하고 파티클로 사용)
    //particle = new Sprite(L"Textures/Effect/explosion.png", 30, 30, 5, 3, true);
    //particle = new Sprite(L"Textures/Effect/fire_8x2.png", 5, 30, 8, 2, true);
    particle = new HitParticle();
    particle->Play({ 0, 0, 0 }, {0, 1, 0});
    sprite = new Sprite(L"Textures/Effect/explosion_1.png", 1500, 1500, 4, 8, false);
    sprite2 = new Sprite(L"Textures/Effect/explosion_2.png", 1500, 1500, 4, 8, false);
    sprite3 = new Sprite(L"Textures/Effect/explosion_3.png", 1500, 1500, 4, 8, false);
    sprite4 = new Sprite(L"Textures/Effect/explosion_4.png",1500,1500,4,8,false);
    collider = new SphereCollider(30);
    wind = new Wind(); 
    
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
}

void ParticleScene::Update()
{
    sprite->SetColor({ 0,0,0,1 });
    sprite2->SetColor({ 0,0,0,1 });
    sprite3->SetColor({ 0,0,0,1 });

    if (KEY_DOWN(VK_LBUTTON))
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        Contact contact;

        if (collider->IsRayCollision(ray, &contact))
        {
            //particle->Play(contact.hitPoint, {1, -1, 0});
            //sprite->Play(contact.hitPoint);
            sprite->Play(contact.hitPoint);
            //sprite2->Play(contact.hitPoint);
            //sprite3->Play(contact.hitPoint);
        }
    }
    if (KEY_UP(VK_LBUTTON))
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        Contact contact;
        //if(collider->IsRayCollision(ray,&contact))
            //sprite4->Play(contact.hitPoint);

    }    
    if (KEY_DOWN(VK_LBUTTON))
        timer++;

    if(timer>0)
    timer += DELTA;

    if (timer > 10)
        timer = 0;
    sprite->Update();
    sprite2->Update();
    sprite3->Update();
    sprite4->Update();
    particle->Update();
    wind->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    particle->Render();
    collider->Render();
    sprite4->Render();
    sprite3->Render();
    sprite2->Render();
    sprite->Render();
    wind->Render();
}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    sprite->GUIRender();
}

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

    collider = new SphereCollider(30);
}

ParticleScene::~ParticleScene()
{
    delete particle;
    delete collider;
}

void ParticleScene::Update()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        Ray ray = CAM->ScreenPointToRay(mousePos);
        Contact contact;

        if (collider->IsRayCollision(ray, &contact))
        {
            particle->Play(contact.hitPoint, {1, -1, 0});
        }
    }

    particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
    particle->Render();
    collider->Render();
}

void ParticleScene::PostRender()
{
}

void ParticleScene::GUIRender()
{
    particle->GUIRender();
}

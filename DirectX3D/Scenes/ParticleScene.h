#pragma once
class ParticleScene : public Scene
{
public:
    ParticleScene();
    ~ParticleScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    // 테스트용 파티클
    //ParticleSystem* particle; // 범용 파티클
    //Particle* particle;         // 특수 파티클(의 범용 인터페이스)
    //HitParticle* particle;

    //-----------------------------------
    SphereCollider* collider; // 클릭용 표적
    Sprite* sprite;
    Sprite* sprite2;
    Sprite* sprite3;
    Sprite* sprite4;
    Sprite* sprite5;
    Sprite* sprite6;
    Wind* wind;
    ParticleSystem2* particle;
    
    bool on = false;
    float timer = 0;
};


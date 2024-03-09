#pragma once
class FightTestScene :public Scene
{
public:

    FightTestScene();
    ~FightTestScene();

    virtual void Update()     override;
    virtual void PreRender()  override;
    virtual void Render()     override;
    virtual void PostRender() override;
    virtual void GUIRender()  override;


    RasterizerState* rasterizer;
    Valphalk* GetValphalk() { return valphalk; }
    Player* GetPlayer() { return player; }
    Sample* GetGaruk() { return garuk; }

private:
    Player* player;
    Sample* garuk;
    Valphalk* valphalk;
    CapsuleCollider* capsule;
};


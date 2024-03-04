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

private:
    Player* player;
    Valphalk* valphalk;
    CapsuleCollider* capsule;
};


#pragma once
class ValphalkTestScene :public Scene
{
public:

    ValphalkTestScene();
    ~ValphalkTestScene();

    virtual void Update()     override;
    virtual void PreRender()  override;
    virtual void Render()     override;
    virtual void PostRender() override;
    virtual void GUIRender()  override;

    void CapsuleMove();
    RasterizerState* rasterizer;
    Valphalk* GetValphalk() { return valphalk; }

private:
    Player* player;
    Valphalk* valphalk;
    Sample* garuk;
    CapsuleCollider* capsule;
};


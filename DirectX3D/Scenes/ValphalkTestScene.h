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


private:
    Player* player;
    Valphalk* valphalk;
    CapsuleCollider* capsule;
};


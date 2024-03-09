#pragma once
class PlayerTestScene : public Scene
{
public:
    PlayerTestScene();
    ~PlayerTestScene();

    virtual void Update() override;

    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    DummyValphalk* GetValphalk() { return valphalk; }

private:
    Player* player;
    DummyValphalk* valphalk;
    WireBug* wireBug;
};


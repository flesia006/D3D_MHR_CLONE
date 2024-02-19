#pragma once

class ShadowScene : public Scene
{
public:
    ShadowScene();
    ~ShadowScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    Valphalk* GetValphalk() { return valphalk; }
    Player* GetPlayer() { return player; }

private:
    void AddSounds();
private:

    Model* forest;

    Player* player;
    Valphalk* valphalk = nullptr;

    Shadow* shadow;


    HalfSphere* ball;
    Model* fog;




    LightBuffer::Light* light; //ºû »ç¿ëÇÏ±â

private:
    //Terrain* terrain;
    //AStar* aStar;
    Garuk* garuk;
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];

};


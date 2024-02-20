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
    TerrainEditor* GetTerrain() { return terrain; }

private:
    void AddSounds();

private:
    Player* player;
    Valphalk* valphalk = nullptr;

    Shadow* shadow;

    M41Objects* objects;

    HalfSphere* ball;
    Model* fog;
    Model* fieldFog;

    TerrainEditor* terrain;


    LightBuffer::Light* light; //ºû »ç¿ëÇÏ±â

private:
    //Terrain* terrain;
    //AStar* aStar;
    Garuk* garuk;
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];

};


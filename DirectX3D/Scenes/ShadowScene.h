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
    Player* player;
    Valphalk* valphalk = nullptr;

    Shadow* shadow;

    M41Objects* objects;
    M42Objects* objects2;

    HalfSphere* ball;
    Model* fog;
    Model* fieldFog;

    TerrainEditor* terrain;

    WireBug* wireBug;

    LightBuffer::Light* light; //ºû »ç¿ëÇÏ±â

private:
    //Terrain* terrain;
    //AStar* aStar;
    Sample* garuk;
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];

    bool firstRender = false;

};


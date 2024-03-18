#pragma once
class MapDesignScene :public Scene
{
public:
    MapDesignScene();
    ~MapDesignScene();


    virtual void Update() override;

    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender()  override;

    TerrainEditor* GetTerrain() { return terrain; }

private:

    DummyValphalk* val = nullptr;
    ModelAnimator* utusi = nullptr;

    HalfSphere* ball;
    HalfSphere* ball2;
    HalfSphere* fog;
    HalfSphere* fog2;
    Model* fieldFog;


    TerrainEditor* terrain;

    LightBuffer::Light* light; //ºû »ç¿ëÇÏ±â
    LightBuffer::Light* light2;
    LightBuffer::Light* light3;

    M41Objects* objects;
    M42Objects* objects_M42;


    RasterizerState* rasterizerState[2];
    BlendState* blendState[3];

    CapsuleCollider* cap;
};


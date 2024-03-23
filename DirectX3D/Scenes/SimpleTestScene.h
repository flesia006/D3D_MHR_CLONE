#pragma once
class SimpleTestScene : public Scene
{


public:
    SimpleTestScene();
    ~SimpleTestScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private :
    HalfSphere* half = nullptr;
    Cylinder2* ring = nullptr;
    Suwol* suwol = nullptr;
    Model* breath = nullptr;
    ValZet* val = nullptr;
    SliceEft* slice = nullptr;
    Quad* cut = nullptr;
    ValZet* vz = nullptr;
    SkyFallEft* sfe = nullptr;

    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];
    DepthStencilState* depthState[2];

};


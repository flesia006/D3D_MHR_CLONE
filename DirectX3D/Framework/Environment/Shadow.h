#pragma once

class Shadow
{
public:
    Shadow(UINT width = 6000, UINT height = 6000);
    ~Shadow();

    void SetRenderTarget();
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    void SetViewProjection();

private:
    UINT width, height;
    float scale = 100.0f;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    ViewBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    class Quad* quad;
};
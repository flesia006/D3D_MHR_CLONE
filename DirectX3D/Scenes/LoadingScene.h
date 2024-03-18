#pragma once

class LoadingScene : public Scene
{
private:
    UINT COUNT = 100;
public:
    LoadingScene();
    ~LoadingScene();

    void ExportClip(string name, string clipName);

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    Quad* GetLoading() { return loading; }
    Quad* GetIcon() { return icon; }

private:
    BlendState* blendState[2]; //���� ������Ʈ
    DepthStencilState* depthState[2]; //���� ������Ʈ
    Quad* loading;
    Quad* icon;
    Quad* nowloading;
};
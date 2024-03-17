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
    BlendState* blendState[2]; //블렌드 스테이트
    DepthStencilState* depthState[2]; //뎁스 스테이트
    Quad* loading;
    Quad* icon;
    Quad* nowloading;
};
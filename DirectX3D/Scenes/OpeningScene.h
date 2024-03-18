#pragma once
class OpeningScene : public Scene
{
private:
    UINT COUNT = 100;
public:
    OpeningScene();
    ~OpeningScene();

    void ExportClip(string name, string clipName);

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    int choice = 0;

private:
    BlendState* blendState[2]; 

    Material* material;
    VertexBuffer* vertexBuffer;

    DepthStencilState* depthState[2];
    vector<VertexUV> vertices; 

    Quad* lobby;
    Quad* select;

    vector<Quad*> menuBar;

    bool isEnd = false;
    int sequence = 0;
    int selectNum = 0;


};
#pragma once

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Update();
    void Render();

    Quad* firstScreen;

    int sequence = 0;
    bool isStart = false;

    int timer = 0;

private:
    void Create();
    void Delete();

};
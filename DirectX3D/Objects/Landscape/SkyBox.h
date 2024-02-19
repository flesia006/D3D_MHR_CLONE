#pragma once

class SkyBox : public Sphere
{
    // 스카이 박스 : 배경에서 하늘을 빠르게 묘사하기 위해서 배치하는 큰 원시 모형
    //              특징 : 안쪽을 향하는(혹은 기본은 바깥을 항햐지만 안에서도 볼 수 있는) 텍스처 출력
    //                     텍스처가 하늘 - 단일 텍스처처럼 인식 가능한 큰 텍스처 아틀라스
    //                     (*아틀라스 : 큰 그림 1장 혹은 작은 그림 여러 장으로 이루어진 이미지 데이터)
    //                     *지금 프레임워크에서 하늘 이미지를 1장 써서 큐브 모형을 만들면 실제론 하늘 6장 출력
    //                      -> 그래서 큐브 대신 스피어 사용 (그러면 큰 하늘 1장이 보일 것)

public:
    SkyBox(wstring fileName); //"하늘 배경"은 목적과 리소스가 분명한 경우를 전제할 테니까
    ~SkyBox();

    void Render();
    void Update();
private:
    Texture* skyMap; //하늘용 텍스처 (맵)

    // DX11 제공 스테이트, 래스터라이저 : 정점 정보와 텍스처 정보를 픽셀 정보로 변환해서 고정해주는 상태
    //                                  장점 : 1. 픽셀의 확실함을 얻을 수 있다 2. 한 번 변환이 끝나면 렌더는 빠르다
    RasterizerState* rasterizerSatate[2];
    // DX11 제공 스테이트, 뎁스-스텐실 : 깊이(UV의 우선순위) 정보와 스텐실(장애물 판정) 정보를 적용해주는 상태
    //                                 용도 : 배경색 지우기(알파-블렌드와 유사) / 겹쳐진 이미지에서 특정 화소 렌더 선별
    //                                        잘 쓰면 특정 물체에 가려진 화소를 아예 렌더하지 않거나, 특정 색을 빼고 출력할 수 있다
    DepthStencilState* depthStencilState[2];

};

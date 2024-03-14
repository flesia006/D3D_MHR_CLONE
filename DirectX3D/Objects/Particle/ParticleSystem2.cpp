#include "Framework.h"

// ���� Ŭ���� ȯ�濡�� ���� �������� (=�ؽ�Ʈ ����)
ParticleSystem2::ParticleSystem2(string file)
{
    LoadData(file); // ���� ������ �ҷ����� �Լ� �������

    //Ʈ������ ������ �غ�
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //��¿� ������Ʈ�� �غ�
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true); //���� ���� (������ ���� ������ ����)

    FOR(2) depthState[i] = new DepthStencilState();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); // �������� ����Ʈ
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� �������� ����Ʈ

    quad->SetActive(false); // �ϴ� ���� ���� �ƴϾ ��Ȱ��ȭ    

    parent = new Transform();
    parent->Pos() = {};
    FOR(2) rasterizerState[i] = new RasterizerState();

    rasterizerState[1]->CullMode(D3D11_CULL_NONE);
}

// �ܺ� Ž���⿡�� ���� �������� (=�׸� ����)
ParticleSystem2::ParticleSystem2(wstring file)
{
    LoadData(file); // ���� ������ �ҷ����� �Լ� �������

    //Ʈ������ ������ �غ�
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //��¿� ������Ʈ�� �غ�
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true); //���� ���� (������ ���� ������ ����)

    FOR(2) depthState[i] = new DepthStencilState();
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); // �������� ����Ʈ
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� �������� ����Ʈ

    quad->SetActive(false); // �ϴ� ���� ���� �ƴϾ ��Ȱ��ȭ
    
    parent = new Transform();
    parent->Pos() = {};

}

ParticleSystem2::~ParticleSystem2()
{
    delete quad;
    delete instanceBuffer;
    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];
}

void ParticleSystem2::Update()
{
    if (!quad->Active()) return;

    lifeSpan += DELTA;

    UpdatePhysical(); // ���� ������Ʈ
    UpdateColor();    // ������ ������Ʈ
    quad->UpdateWorld();  //������Ʈ�� ������ �׸��� ���߱� (�׸��� ��ƼŬ�� �°� ������Ʈ)
    parent->UpdateWorld();

    if (lifeSpan > data.duration) //������ ����ð��� �����ֱ�(�� ����ð�)�� �ʰ��ϸ�
    {
        if (data.isLoop) Init(); // �ݺ� �ɼ��� ���� ������ �����
        else Stop(); // ���߱�
    }
}

void ParticleSystem2::Render()
{
    if (!quad->Active()) return;
    rasterizerState[1]->SetState(); // �ĸ鵵 �׸�
    {
        //�ν��Ͻ� �غ�
        instanceBuffer->Set(1);

        //�׸��غ�
        quad->SetRender();

        //������Ʈ �غ�
        blendState[1]->SetState();
        depthState[1]->SetState();

        //�����ġ�� ȣ��
        DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0); // �Ű������� � ������, �󸶳� ����
                                                         // ���, � �߰� ���� �ڷ�� ����� ���ΰ�

        //���󺹱�
        blendState[0]->SetState();
        depthState[0]->SetState();
    }
    rasterizerState[0]->SetState();

}

void ParticleSystem2::GUIRender()
{
    quad->GUIRender();
}

void ParticleSystem2::Play(Vector3 pos, Vector3 rot)
{
    quad->SetActive(true);

    quad->Pos() = pos;
//    quad->Rot() = rot;

    Init(rot);
}

void ParticleSystem2::Play2(Vector3 pos, Vector3 rot)
{
    quad->SetActive(true);

    quad->Pos() = pos;
    quad->Rot() = rot;    
}
void ParticleSystem2::Stop()
{
    quad->SetActive(false);
}

void ParticleSystem2::ParticleRotate()
{
    float randZ = Random(0.f, 3.14f);
    quad->Rot().z = randZ;
}

void ParticleSystem2::HaloPos()
{
    quad->Pos().x += 100;
    quad->Pos().y -= 100;
    //quad->Pos().z -= 50;
}

void ParticleSystem2::SetRotation(Vector3 rot)
{
    quad->Rot() = rot;
}

void ParticleSystem2::SetScale(float scale)
{
    quad->Scale() *= scale;
}

void ParticleSystem2::SetVortex(Vector3 pos)
{
    //for (int i = 0; i < 1000; ++i)
    //{
    //    quad->Pos() = Float3(quad->Pos().x + i * 10, quad->Pos().y, quad->Pos().y);
    //}
    //quad->Rot().z += 1 * DELTA;
    //parent->Pos() = pos;
    
    //for(int i=0;i<1;++i)
    //quad->Pos() = Float3(quad->Pos().x, quad->Pos().y, quad->Pos().z);
    //parent->Scale() *= 0.01f;
    //quad->Scale() *= 100;
    //quad->SetParent(parent);
    //quad->Pos() = { pos.x + 10, pos.y, pos.z + 10 };
    quad->Rot().x = XM_PIDIV2;
    quad->Rot().z += 10 * DELTA;
    quad->Rot().y = XM_PIDIV2;
    //quad->Pos() = pos;
    //parent->Rot().y += 1.01f * DELTA;

}

//�Ʒ� �� �Լ� = ��ƼŬ (���� ���� ������) ������Ʈ
void ParticleSystem2::UpdatePhysical()
{
    drawCount = 0;


    FOR(data.count) //���� ����Ʈ ���
    {
        // * particleInfos[i] : �̸� ������� ��ƼŬ�� ����� ��� ȣ���� ���

        if (lifeSpan < particleInfos[i].startTime) continue;
                // �ֱⰡ ������ ���� = ���۵� �ȵ� ��ƼŬ ��ġ��

        //���� ���� ��ƼŬ ���
        particleInfos[i].velocity += particleInfos[i].acceleration * DELTA; // �ӷ±���
        particleInfos[i].transform.Pos() = Lerp(particleInfos[i].transform.Pos(), 0, 0.006f);
        //particleInfos[i].transform.Pos() += particleInfos[i].velocity
        //    * particleInfos[i].speed * DELTA; // �ӷ±��� * �⺻�ӵ� * �ð���� = �����ӷ�
                                              // �����ӷ��� ��ġ�� ���ؼ� ��ġ ����
        particleInfos[i].transform.Rot().z += particleInfos[i].angularVelocity * DELTA;
                                              // ���� ����

        //������ �ɼ��� Ȱ��ȭ�Ǿ� ������ �׸��� ī�޶� ������ (����ȭ)
        if (data.isBillboard)
        {
          /*  particleInfos[i].transform.Pos().x = Random(-100, 100);
            particleInfos[i].transform.Pos().y = Random(-100, 100);*/
            particleInfos[i].transform.Rot().x = CAM->Rot().x;
            particleInfos[i].transform.Rot().y = CAM->Rot().y;
            //            particleInfos[i].transform.Rot().z = atan2(particleInfos[i].velocity.x, particleInfos[i].velocity.y);

        }
        // ���͸� ���� ������ ������ ���������� -> �׸��� ������ 100% 2D �������� ���δٴ� ������ ����
        // ������Ʈ�� ���̴��� �ᵵ ������ -> ���� ������ �޶����� �� ���� �ִ� (�ɼǿ� ������ ���� �Ͽ�ȭ)

        float t = (lifeSpan - particleInfos[i].startTime)
            / (data.duration - particleInfos[i].startTime); //�ֱ� �� ��� �ð��� (������Ʈ �߿��� �����ֱ�=����ð�)
                                                            //��ƼŬ�� ��ü ��� �ð��� ���� ���۽ð��� ���� ���̸� ����
                                                            //�׿� ���� ��� ����(t)�� ����
                                                            // = ������� ����(0)���� ������� ����(1) ������ ���� ���� ��

        //������ ���� �ð� ��� ������ �̿��ؼ� ũ�� (��쿡 ���� �ٸ� �ɼ��� �ִٸ� �װ͵�) ����
        particleInfos[i].transform.Scale() =
            Lerp(particleInfos[i].startScale, particleInfos[i].endScale, t);

//        Vector3 camFwd = CAM->Forward();
//        float mul = 1 - abs(Dot(particleInfos[i].velocity, camFwd));
//        particleInfos[i].transform.Scale() *= mul;



        //��ġ, ȸ��, ũ�� ���� ���� ���� ��� ���� ������Ʈ
        particleInfos[i].transform.UpdateWorld();

        //������Ʈ�� ������ ��ƼŬ�� ���� ����
        instances[drawCount++].transform = //drawCount�� ȣ���� ��, ������ ������ ������ +1 (�������� Ȱ�� �ļ�)
            XMMatrixTranspose(particleInfos[i].transform.GetWorld());
    }

    // ������� ���� �� ��ƼŬ�� ���� ���� ������ ��� ������ �ȴ�
    // -> �̿� ���� ���۸� ������Ʈ
    instanceBuffer->Update(instances.data(), drawCount);// ��� ������ �� �� ������Ʈ�� ���ΰ�
}

void ParticleSystem2::UpdateColor()
{
    // ���� ������Ʈ ���� �������� �̹� ��ƼŬ�� �������, ��������(��������) ������ ������ ��
    // -> ���� �� �׷��ٸ� ���ʿ��� �ٽ� �� ������ �� ����� ���� ��
    // -> ������ �������� ������ ���⼭ �� �� �ʿ�� ����. ��� �ű⼭ ���� �� ä����� �Ѵ�

    float t = lifeSpan / data.duration; // ����ð� ������ ������ ����ð�(�Ϲݰ�)

    //��ٷ� Ȱ��
    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t); // R
    color.y = Lerp(data.startColor.y, data.endColor.y, t); // G
    color.z = Lerp(data.startColor.z, data.endColor.z, t); // B
    color.w = Lerp(data.startColor.w, data.endColor.w, t); // A

    //���忡�� ����
    quad->GetMaterial()->GetData().diffuse = color;
}

void ParticleSystem2::Init()
{
    // ���� ��ƼŬ�� �����ϱ�

    // �׸��� ������ ȥ�������ΰ�(additive) �ƴϸ� �׳� �ܵ� ���İ� �ִ� �ǰ�(���� �ִ� ������)
    // ->�ɼǿ� ���� ������Ʈ ���� �ѹ� �� Ȯ�λ��
    if (data.isAdditive) blendState[1]->Additive(); //ȥ�տ� ���� ���� Ȱ��ȭ
    else blendState[1]->Alpha(true);                //���İ� �ִ� ������ Ȱ��ȭ
                                                    //->�߰��� �ɼ��� �ٲ�� ��츦 ���ؼ�

    lifeSpan = 0; //�ֱ�(�� ��� �ð�) 0
    drawCount = 0; //��ο� ��û Ƚ�� 0
    data.count = particleCount; //������ ��� (���� �ɼ��� �޶����� �� �ڵ嵵 ���� �ʿ�)

    // ���� �ٽ� ����
    instances.resize(data.count);
    particleInfos.resize(data.count); //���� ��ƼŬ ����

    //�Ʒ� �ڵ�� ���� : ���� ��ƼŬ ������ �ְ�, ���� �������ٰ� ����
    // -> �ó������� �ٲ�� �� �ڵ�� �����ǰų�, �ٸ� ������ ���� ȣ��Ǿ�� �Ѵ�
    for (ParticleInfo& info : particleInfos) //���� ���� ���� ���� Ȱ��
    {
        info.transform.Pos() = {}; //�ϴ� ��� ����. Ʈ�������� �ֱ�� ����

        //��ƼŬ�μ��� �ɼ� ����
        info.velocity = Random(data.minVelocity, data.maxVelocity);
        info.acceleration = Random(data.minAcceleration, data.maxAcceleration);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);

        //��ƼŬ���� �ӷ��� ����ȭ�Ѵٸ� �Ʒ� �ڵ����
        info.velocity.Normalize();
    }
    //�� �ݺ����� ������ ������ ���� �� ���� ��ƼŬ�� ���� �ٸ� ������ ����
    //->���߿� �� �������� �ٸ� ��ƼŬ�� �θ��⸸ �ص� �پ��� ������ ���� ��ƼŬ ���� ����
    //-> �̸� ��ƼŬ�� ����� ����ȭ���� ������ �ǰ�, ����� ���� ������Դ� ū ��̸� ���� ���Ѵ�
}

void ParticleSystem2::Init(Vector3 rot)
{
    if (data.isAdditive) blendState[1]->Additive(); 
    else blendState[1]->Alpha(true);             

    lifeSpan = 0; 
    drawCount = 0; 
    data.count = particleCount; 

    instances.resize(data.count);
    particleInfos.resize(data.count);

    Vector3 Rot = rot.GetNormalized();

    for (ParticleInfo& info : particleInfos) //���� ���� ���� ���� Ȱ��
    {
        info.transform.Pos().x = Random(-2000, 2000); //�ϴ� ��� ����. Ʈ�������� �ֱ�� ����
        info.transform.Pos().y = Random(-2000, 2000);

        //��ƼŬ�μ��� �ɼ� ����
        info.velocity = Random(Rot - Vector3(0.3, 0.3, 0.3), Rot + Vector3(0.3, 0.3, 0.3));
        info.acceleration = Random(Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed * 3);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale*1.2, data.maxStartScale*1.2);
        info.endScale = Random(data.minEndScale, data.maxEndScale);

        //��ƼŬ���� �ӷ��� ����ȭ�Ѵٸ� �Ʒ� �ڵ����
        info.velocity.Normalize();
    }

}

void ParticleSystem2::LoadData(string file)
{
    //������ ������ ����(�ؽ�Ʈ ����, ini ��)�� �ִٰ� ġ�� �ű⼭ �ڷ� �ҷ�����

    //���� �б� �غ�
    BinaryReader* reader = new BinaryReader(file);

    //���� ���� ���Ͽ��� ���� �̸��� �����ؼ� �׸� �����
    wstring tFile = reader->WString();
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetDiffuseMap(tFile);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");

    //������ ������ ��ƼŬ �ɼ� �ҷ��ͼ� �����ϱ�
    // -> �ؽ�Ʈ ������� Ȱ���ؼ� �츮�� ������ ���� ���� �ְ� (�׷��� ���� ���� ������ ���� �ְ�)
    // -> ���� ��ƼŬ�̸� ���� ������� ������ ������ �ɼ��� �ּ������� ������ �Ǳ� ������ ���⼭
    //    ������ �о �ٷ� �ɼ� ������ �����ϴ�

    ParticleData* pData = new ParticleData();
    reader->Byte((void**)&pData, sizeof(ParticleData));
    data = *pData;

    //���� ����
    instances.resize(data.count);
    particleInfos.resize(data.count);

    delete reader;
}

void ParticleSystem2::LoadData(wstring file)
{
    //�׸� �����
    quad = new Quad(Vector2(1, 1)); // ������ ���ذ�. ���⼭ �ٲ㵵 ������,
                                    // ������ �ɼǿ��� �����ϴ� ���� ����

    quad->GetMaterial()->SetDiffuseMap(file); // �׸� ���� �ҷ�����
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl"); // �⺻ �ؽ�ó Ȥ�� ���� ���̴�

    //���� ����Ʈ, ���� �ν��Ͻ��� ����ؼ� ���� ����(��������)
    instances.resize(data.count);
    
    //���� �ν��Ͻ� ������ �ʿ��ϴٸ� ���� ���͵� ����
    particleInfos.resize(data.count);

    // ������� ����� �׸��� ���� ����(��ƼŬ �⺻ �׸�) �� �⺻ �����ʹ� ���� ��
    // ���� �ɼ��� �����ϰ�... (data ����ü�� �����ϰ�)
    // �ű⿡ �ִ� count�� ���� �� ���� ���� 2���� �ٽ� ��������� �Ѵ�

    // -> �ٸ� �� LoadData �Լ��� �����ϸ� �Ƹ� ���� ���� ������ ���� ���� ���� ��.
}

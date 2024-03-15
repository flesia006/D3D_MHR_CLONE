#include "Framework.h"
#include "ModelQuad.h"

ModelQuad::ModelQuad() :Model("quad")
{

}

ModelQuad::~ModelQuad()
{
}

void ModelQuad::Render()
{
	Model::Render();
}

void ModelQuad::SetTexture(wstring file)
{
}

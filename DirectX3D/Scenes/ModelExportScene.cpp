#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "Garuk";
    string file = "Models/FBX/" + name + ".fbx";
    ModelExporter* exporter;
    string clipName;

//    exporter = new ModelExporter(name, file);
//    exporter->ExportMaterial();
//    exporter->ExportMesh();
//    delete exporter;    
//    
    clipName = "G_010";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);    
    delete exporter;

    clipName = "G_022";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;
    
    clipName = "G_024";
    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;
    
    //clipName = "Walk";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "Hit";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
    //
    //clipName = "StandUp";
    //file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    //exporter = new ModelExporter(name, file);
    //exporter->ExportClip(clipName);
    //delete exporter;
}

ModelExportScene::~ModelExportScene()
{
}

void ModelExportScene::Update()
{
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
}

void ModelExportScene::PostRender()
{
}

void ModelExportScene::GUIRender()
{
}

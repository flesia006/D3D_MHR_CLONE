#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "Player";
    string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    string clipName;

//    exporter = new ModelExporter(name, file);
//    exporter->ExportMaterial();
//    exporter->ExportMesh();
//    delete exporter;    


// Å¬¸³µþ ¶§ ÀÌ°Å ¾²¼À
    ExportClip(name, "D_026");
//    ExportClip(name, "D_004");
//    ExportClip(name, "D_007");
//    ExportClip(name, "D_011");
//    ExportClip(name, "D_015");
//    ExportClip(name, "D_016");
//    ExportClip(name, "D_021");
//    ExportClip(name, "D_022");
//    ExportClip(name, "D_029");
//    ExportClip(name, "D_030");
//    ExportClip(name, "D_031");
//    ExportClip(name, "D_032");
//    ExportClip(name, "D_033");
//    ExportClip(name, "D_045");
//    ExportClip(name, "D_046");
//    ExportClip(name, "D_066");
//    ExportClip(name, "D_078");
//    ExportClip(name, "D_079");
//    ExportClip(name, "D_080");
//    ExportClip(name, "L_400");
//    ExportClip(name, "L_403");
//    ExportClip(name, "L_451");
//    ExportClip(name, "L_453");
//    ExportClip(name, "L_455");
//    ExportClip(name, "E_2200");
//    ExportClip(name, "E_2210");
//    ExportClip(name, "E_2211");

//    name = "E_0003";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportMaterial();
//    exporter->ExportMesh();
//    delete exporter;
//
//    name = "tikei10";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportMaterial();
//    exporter->ExportMesh();
//    delete exporter;

//    
//    clipName = "E_1151";
//    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportClip(clipName);    
//    delete exporter;
//
//    clipName = "E_1155";
//    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportClip(clipName);
//    delete exporter;
//    clipName = "E_2054";
//    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportClip(clipName);
//    delete exporter;
  
//    clipName = "E_1163";
//    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportClip(clipName);
//    delete exporter;
//    
//    clipName = "E_1164";
//    file = "Models/Animations/" + name + "/" + clipName + ".fbx";
//    exporter = new ModelExporter(name, file);
//    exporter->ExportClip(clipName);
//    delete exporter;
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

void ModelExportScene::ExportClip(string name, string clipName)
{
    string file = "Models/Animations/" + name + "/" + clipName + ".fbx";
    ModelExporter* exporter;
    exporter = new ModelExporter(name, file);
    exporter->ExportClip(clipName);
    delete exporter;
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

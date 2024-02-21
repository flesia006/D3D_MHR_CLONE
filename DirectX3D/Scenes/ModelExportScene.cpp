#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    string name = "Valphalk";
    string file = "Models/FBX/" + name + ".fbx";
    //ModelExporter* exporter;
    string clipName;

//    exporter = new ModelExporter(name, file);
//    exporter->ExportMaterial();
//    exporter->ExportMesh();
//    delete exporter;    


// Å¬¸³µþ ¶§ ÀÌ°Å ¾²¼À
//    ExportClip(name, "E_2082");
//    ExportClip(name, "E_2091");
//    ExportClip(name, "E_2092");
//    ExportClip(name, "E_2093");
//    ExportClip(name, "E_2103");
//    ExportClip(name, "E_2129");
//    ExportClip(name, "E_2130");
//    ExportClip(name, "E_2131");
//    ExportClip(name, "E_2133");
//    ExportClip(name, "E_2134");
//    ExportClip(name, "E_2144");
//    ExportClip(name, "E_2145");
//    ExportClip(name, "E_2146");
//    ExportClip(name, "E_2151");
//    ExportClip(name, "E_2152");
//    ExportClip(name, "E_2153");
//    ExportClip(name, "E_2381");
//    ExportClip(name, "E_2382");
//    ExportClip(name, "E_2383");




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

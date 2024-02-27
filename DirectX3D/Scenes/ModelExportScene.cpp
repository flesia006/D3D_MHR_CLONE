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
    ExportClip(name, "R_013");
    ExportClip(name, "R_024");
    ExportClip(name, "R_031");
    ExportClip(name, "R_041");
    ExportClip(name, "R_104");
    ExportClip(name, "R_142");
    ExportClip(name, "R_143");
    ExportClip(name, "R_144");
    ExportClip(name, "R_400");
    ExportClip(name, "R_401");
    ExportClip(name, "R_402");
    ExportClip(name, "R_600");
    ExportClip(name, "R_601");
    ExportClip(name, "R_602");
//    ExportClip(name, "E_2106");
//    ExportClip(name, "E_2107");
//    ExportClip(name, "E_2108");
//    ExportClip(name, "E_2118");
//    ExportClip(name, "E_2121");
//    ExportClip(name, "E_2173");
//    ExportClip(name, "E_2174");
//    ExportClip(name, "E_2175");
//    ExportClip(name, "E_2185");
//    ExportClip(name, "E_2188");
//    ExportClip(name, "E_2189");
//    ExportClip(name, "E_2190");
//    ExportClip(name, "E_2192");
//    ExportClip(name, "E_2193");
//    ExportClip(name, "E_2200");
//    ExportClip(name, "E_2210");
//    ExportClip(name, "E_2288");

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

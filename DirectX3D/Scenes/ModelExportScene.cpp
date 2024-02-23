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
    ExportClip(name, "E_0043");
    ExportClip(name, "E_0044");
    ExportClip(name, "E_0045");
    ExportClip(name, "E_0055");
    ExportClip(name, "E_0059");
    ExportClip(name, "E_0060");
    ExportClip(name, "E_0061");
    ExportClip(name, "E_0071");
    ExportClip(name, "E_0151");
    ExportClip(name, "E_0152");
    ExportClip(name, "E_0153");
    ExportClip(name, "E_0164");
    ExportClip(name, "E_0165");
    ExportClip(name, "E_0166");
    ExportClip(name, "E_0186");
    ExportClip(name, "E_0187");
    ExportClip(name, "E_0188");
    ExportClip(name, "E_2253");
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

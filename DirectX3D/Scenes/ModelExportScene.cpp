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
//    ExportClip(name, "E_0146");
//    ExportClip(name, "E_2001");
//    ExportClip(name, "E_2002");
//    ExportClip(name, "E_2003");
//    ExportClip(name, "E_2013");
//    ExportClip(name, "E_2015");
//    ExportClip(name, "E_2017");
//    ExportClip(name, "E_2019");
//    ExportClip(name, "E_2020");
//    ExportClip(name, "E_2022");
//    ExportClip(name, "E_2027");
//    ExportClip(name, "E_2032");
//    ExportClip(name, "E_2033");
    ExportClip(name, "E_2146");
    //ExportClip(name, "E_2042");
//    ExportClip(name, "E_2044");
//    ExportClip(name, "E_2045");
//    ExportClip(name, "E_2054");
//    ExportClip(name, "E_2056");
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

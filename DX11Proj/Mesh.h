#pragma once


#include "Vertex.h"
#include <vector>

//For MeshData
#include "GeometryGenerator.h"

//Assimp Headers
#include "Importer.hpp"
#include "cimport.h"
#include "postprocess.h"
#include "scene.h"


class Mesh
{
public:
	std::vector<GeometryGenerator::MeshData> m_meshData;
	UINT m_materialIndex;


public:
	Mesh();
	~Mesh();

	bool LoadMesh(const std::string& Filename);
	void Draw();

private:
	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	void InitMesh(UINT Index, const aiMesh* paiMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& Filename);
	void Clear();
};

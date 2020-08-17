#pragma once
#include "Singleton.h"
#include "Mesh.h"
#include "unordered_map"



class AssimpModelLoader : public Singleton<AssimpModelLoader>
{
private:
	const aiScene* m_pScene;
	std::vector<Mesh> m_meshes;
	std::unordered_map<std::string, aiBone> m_Bones;
	UINT m_numVertices;
	UINT m_numMaterials;

public:
	AssimpModelLoader();
	~AssimpModelLoader();
};
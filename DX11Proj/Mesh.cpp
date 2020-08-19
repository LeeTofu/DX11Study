#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	Clear();
}

bool Mesh::LoadMesh(const std::string& Filename)
{
	Clear();

	bool ret = false;

    Assimp::Importer importer;

    
    const aiScene* pScene = importer.ReadFile(Filename.c_str(),
        aiProcess_JoinIdenticalVertices |          // ������ ������ ����, �ε��� ����ȭ
        //aiProcess_ValidateDataStructure |          // �δ��� ����� ����
        //aiProcess_ImproveCacheLocality |           // ��� ������ ĳ����ġ�� ����
        //aiProcess_RemoveRedundantMaterials |       // �ߺ��� ���͸��� ����
        //aiProcess_GenUVCoords |                    // ����, ������, ���� �� ��� ������ ������ UV�� ��ȯ
        //aiProcess_TransformUVCoords |              // UV ��ȯ ó���� (�����ϸ�, ��ȯ...)
        //aiProcess_FindInstances |                  // �ν��Ͻ��� �Ž��� �˻��Ͽ� �ϳ��� �����Ϳ� ���� ������ ����
        //aiProcess_LimitBoneWeights |               // ������ ���� ����ġ�� �ִ� 4���� ����
        //aiProcess_OptimizeMeshes |                 // ������ ��� ���� �Ž��� ����
        aiProcess_GenSmoothNormals |               // �ε巯�� �븻����(��������) ����
        //aiProcess_SplitLargeMeshes |               // �Ŵ��� �ϳ��� �Ž��� �����Ž���� ��Ȱ(����)
        //aiProcess_SortByPType |                    // ����Ÿ���� ������Ƽ��� ������ '������' �Ž��� ����
        aiProcess_Triangulate |                    // 3�� �̻��� �𼭸��� ���� �ٰ��� ���� �ﰢ������ ����(����)
        aiProcess_ConvertToLeftHanded);            // D3D�� �޼���ǥ��� ��ȯ

    if (pScene)
        ret = InitFromScene(pScene, Filename);
        
	return ret;
}

void Mesh::Draw()
{
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
    m_meshData.reserve(pScene->mNumMeshes);
    m_materialIndex = pScene->mNumMaterials;

    for (UINT i = 0; i < m_meshData.size(); i++)
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }

	return true;    //InitMaterials(pScene, Filename);
}

void Mesh::InitMesh(UINT Index, const aiMesh* paiMesh)
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (UINT i = 0; i < paiMesh->mNumVertices; i++)
    {
        //p, n, t, uv
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
        const aiVector3D* pTangent = &(paiMesh->mTangents[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        GeometryGenerator::Vertex v(pPos->x, pPos->y, pPos->z,
            pNormal->x, pNormal->y, pNormal->z,
            pTangent->x, pTangent->y, pTangent->z,
            pTexCoord->x, pTexCoord->y);

        m_meshData[Index].Vertices.push_back(v);
    }

    for (UINT i = 0; i < paiMesh->mNumFaces; i++)
    {
        const aiFace& Face = paiMesh->mFaces[i];
        m_meshData[Index].Indices.push_back(Face.mIndices[0]);
        m_meshData[Index].Indices.push_back(Face.mIndices[1]);
        m_meshData[Index].Indices.push_back(Face.mIndices[2]);
    }
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
    //�� ���� & �ִϸ��̼� ���� ���Ŀ� �߰��ҿ���
	return false;
}

void Mesh::Clear()
{
    m_meshData.clear();
}

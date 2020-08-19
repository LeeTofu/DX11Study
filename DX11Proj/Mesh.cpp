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
        aiProcess_JoinIdenticalVertices |          // 동일한 꼭지점 결합, 인덱싱 최적화
        //aiProcess_ValidateDataStructure |          // 로더의 출력을 검증
        //aiProcess_ImproveCacheLocality |           // 출력 정점의 캐쉬위치를 개선
        //aiProcess_RemoveRedundantMaterials |       // 중복된 매터리얼 제거
        //aiProcess_GenUVCoords |                    // 구형, 원통형, 상자 및 평면 매핑을 적절한 UV로 변환
        //aiProcess_TransformUVCoords |              // UV 변환 처리기 (스케일링, 변환...)
        //aiProcess_FindInstances |                  // 인스턴스된 매쉬를 검색하여 하나의 마스터에 대한 참조로 제거
        //aiProcess_LimitBoneWeights |               // 정점당 뼈의 가중치를 최대 4개로 제한
        //aiProcess_OptimizeMeshes |                 // 가능한 경우 작은 매쉬를 조인
        aiProcess_GenSmoothNormals |               // 부드러운 노말벡터(법선벡터) 생성
        //aiProcess_SplitLargeMeshes |               // 거대한 하나의 매쉬를 하위매쉬들로 분활(나눔)
        //aiProcess_SortByPType |                    // 단일타입의 프리미티브로 구성된 '깨끗한' 매쉬를 만듬
        aiProcess_Triangulate |                    // 3개 이상의 모서리를 가진 다각형 면을 삼각형으로 만듬(나눔)
        aiProcess_ConvertToLeftHanded);            // D3D의 왼손좌표계로 변환

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
    //모델 추출 & 애니메이션 구현 이후에 추가할예정
	return false;
}

void Mesh::Clear()
{
    m_meshData.clear();
}

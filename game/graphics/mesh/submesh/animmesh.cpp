#include "animmesh.h"
#include "packedmesh.h"

#include <Tempest/Log>

static size_t countBones(const Resources::VertexA* v, size_t n) {
  if(n==0)
    return 0;
  uint8_t ret = 0;
  for(size_t i=0; i<n; ++i) {
    ret = std::max(ret, v[i].boneId[0]);
    ret = std::max(ret, v[i].boneId[1]);
    ret = std::max(ret, v[i].boneId[2]);
    ret = std::max(ret, v[i].boneId[3]);
    }
  return ret+1;
  }

AnimMesh::AnimMesh(const PackedMesh& mesh)
  : bonesCount(countBones(mesh.verticesA.data(),mesh.verticesA.size())) {
  vbo = Resources::vbo(mesh.verticesA.data(),mesh.verticesA.size());
  ibo = Resources::ibo(mesh.indices.data(),  mesh.indices.size());

  sub.resize(mesh.subMeshes.size());
  for(size_t i=0;i<mesh.subMeshes.size();++i){
    sub[i].texName   = mesh.subMeshes[i].material.texture;
    sub[i].material  = Resources::loadMaterial(mesh.subMeshes[i].material,true);
    sub[i].iboOffset = mesh.subMeshes[i].iboOffset;
    sub[i].iboSize   = mesh.subMeshes[i].iboLength;
    }
  bbox.assign(mesh.bbox());
  }

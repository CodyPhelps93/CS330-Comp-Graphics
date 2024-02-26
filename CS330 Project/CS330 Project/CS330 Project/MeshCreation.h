#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct GLMesh
{
    GLuint vao;
    GLuint vbos[2];
    GLuint nIndices;
    GLuint nVertices;

};



void UCreateCubeMesh(GLMesh& cubeMesh);
void UCreateStand(GLMesh& standMesh);
void UCreateTower(GLMesh& towerMesh);
void UCreatePlane(GLMesh& planeMesh);
void UCreateMesh(GLMesh& mesh);
void UCreateMonitor(GLMesh& monitorMesh);
void UCreateSpeaker(GLMesh& speakerMesh);
void UCreateTorus(GLMesh& torusMesh);
void UCreateKeyboard(GLMesh& keyboardMesh);
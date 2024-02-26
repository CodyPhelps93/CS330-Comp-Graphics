#include "MeshCreation.h"
#include <vector>

void UCreateMesh(GLMesh& mesh)
{
    // Specifies Normalized Device Coordinates for triangle vertices
  // Vertex data
    GLfloat verts[] = {
        // Vertex Positions		// Normals			// Texture coords
        //bottom side
        -0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
        -0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	0.0f, 0.0f,		//back bottom left
        0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
        -0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
        -0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
        0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,     //front bottom right
        0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
        -0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
        //back side
        0.0f, 0.5f, 0.0f,		0.0f, 0.0f, -1.0f,	0.5f, 1.0f,		//top point	
        0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,		//back bottom right	
        -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	1.0f, 0.0f,		//back bottom left
        0.0f, 0.5f, 0.0f,		0.0f, 0.0f, -1.0f,	0.5f, 1.0f,		//top point	
        //left side
        0.0f, 0.5f, 0.0f,		-1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
        -0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		//back bottom left	
        -0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,     //front bottom left
        0.0f, 0.5f, 0.0f,		-1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
        //right side
        0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
        0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,     //front bottom right
        0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
        0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
        //front side
        0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,		//top point			
        -0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,     //front bottom left	
        0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,     //front bottom right
        0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,		//top point
    };

    const GLuint floatsPerVertex = 3;	// Number of coordinates per vertex
    const GLuint floatsPerColor = 3;	// Number of values per vertex color
    const GLuint floatsPerUV = 2;		// Number of texture coordinate values

    // Calculate total defined vertices
    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerColor + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao);			// Creates 1 VAO
    glGenBuffers(1, mesh.vbos);					// Creates 1 VBO
    glBindVertexArray(mesh.vao);				// Activates the VAO
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);	// Activates the VBO
    // Sends vertex or coordinate data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    // Strides between sets of attribute data
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor + floatsPerUV);

    // Creates the Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerColor)));
    glEnableVertexAttribArray(2);


}

void UCreateCubeMesh(GLMesh& cubeMesh) {
    // Position and Color data
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //Front Face         //Positive Z Normal
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //Left Face          //Negative X Normal
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Right Face         //Positive X Normal
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Bottom Face        //Negative Y Normal
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    cubeMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &cubeMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(cubeMesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, cubeMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateStand(GLMesh& standMesh)
{
    // Define vertices for stand
    GLfloat standVerts[] = {
        // Top of stand triangle
        // Texture Coord    Normals                 UV Coords
        -0.2f, 0.5f, 0.2f,   0.0f, 1.0f, 0.0f,     0.5f, 1.0f,// top-left 0
        0.1f, 0.5f, 0.2f,    0.0f, 1.0f, 0.0f,      1.0f, 1.0f,  // Top-right 1
        0.0f, 0.5f, 0.1f,    0.0f, 1.0f, 0.0f,      0.5f, 0.5f,// Back-middle 2

        // bottome triangle of stand
        -0.5f, 0.0f, 0.2f,   0.0f, -1.0f, 0.0f,     0.0f, 0.0f,// Bottom-left 3
         0.2f, 0.0f, 0.2f,   0.0f, -1.0f, 0.0f,     1.0f, 0.0f, // Bottom-right 4
         0.0f, 0.0f, -0.2f,  0.0f, -1.0f, 0.0f,     0.5f, 0.5f // Bottom-Back-Middle 5

    };


    // Define indices for stand
    GLushort standIndices[] = {
       2, 1, 0,  // top triangle
       0, 3, 4,// bottome triangle
       4, 1, 0,   // 1st left side triangle
       0, 2, 5, // 2nd left-side triangle
       5, 3, 0, // 1st right-side triangle
       1, 4, 5, // 2nd right-side triangle
       5, 2, 1,

    };

    standMesh.nIndices = sizeof(standIndices) / sizeof(standIndices[0]);

    const GLuint floatsPerVertex = 3; // number of coordinates per vertex
    const GLuint floatsPerColor = 3; // (r, g, b, a)
    const GLuint floatsPerUV = 2; // texture coords

   
    // Create stand VBO and VAO
    glGenVertexArrays(1, &standMesh.vao);  //can generate multiple VAOs or buffers
    glBindVertexArray(standMesh.vao);

    glGenBuffers(2, standMesh.vbos); // Creates 2 buffers
    glBindBuffer(GL_ARRAY_BUFFER, standMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(standVerts), standVerts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, standMesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(standIndices), standIndices, GL_STATIC_DRAW);



    // Strides between vertex coordinates is 8 (x, y, r, g, b, a, U,V,)
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor + floatsPerUV);

    // creates the vertex attribute pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex + floatsPerColor));
    glEnableVertexAttribArray(2);
}

void UCreateTower(GLMesh& towerMesh)
{

    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom left
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.21f, 0.0f, // bottom right
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.21f, 1.0f, // top right
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.21f, 1.0f, // top right
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // top left
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // bottom left

       //Front Face         //Positive Z Normal
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.22f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.45f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.45f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.45f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.22f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.22f, 0.0f,

      //Left Face          //Negative X Normal
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.75f, 0.0f, //bottom right
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.75f, 1.0f, // top right
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 1.0f, // top left
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 1.0f, // top left
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.5f, 0.0f, // bottom left
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.75f, 0.0f, // bottom right

     //Right Face         //Positive X Normal
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.3f, 0.5f, 
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.3f, 0.8f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.25f, 0.8f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.25f, 0.8f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.25f, 0.5f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.3f, 0.5f,

     //Bottom Face        //Negative Y Normal
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.75f, 1.0f, // top left
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.98f, 1.0f, // top right
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.75f, 0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.75f, 1.0f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    towerMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &towerMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(towerMesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, towerMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, towerMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreatePlane(GLMesh& planeMesh)
{
    // Vertex data
    GLfloat verts[] = {
        // Vertex Positions		// Normals			// Texture coords	// Index
        -1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,			//0
        1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,			//1
        1.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			//2
        -1.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,			//3
    };

    // Index data
    GLuint indices[] = {
        0,1,2,
        0,3,2
    };

    // total float values per each type
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    // store vertex and index count
    planeMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));
    planeMesh.nIndices = sizeof(indices) / sizeof(indices[0]);

    // Generate the VAO for the mesh
    glGenVertexArrays(1, &planeMesh.vao);
    glBindVertexArray(planeMesh.vao);	// activate the VAO

    // Create VBOs for the mesh
    glGenBuffers(2, planeMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, planeMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends data to the GPU

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeMesh.vbos[1]); // Activates the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateMonitor(GLMesh& monitorMesh) {
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f, // left bottom
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // right bottom
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top right
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top right
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 1.0f, // top left
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f, // bottom left

       //Front Face         //Positive Z Normal
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //Left Face          //Negative X Normal
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Right Face         //Positive X Normal
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Bottom Face        //Negative Y Normal
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    monitorMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &monitorMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(monitorMesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, monitorMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, monitorMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateKeyboard(GLMesh& keyboardMesh) {
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f, // left bottom
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // right bottom
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top right
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top right
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 1.0f, // top left
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f, // bottom left

       //Front Face         //Positive Z Normal
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //Left Face          //Negative X Normal
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Right Face         //Positive X Normal
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Bottom Face        //Negative Y Normal
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    keyboardMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &keyboardMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(keyboardMesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, keyboardMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, keyboardMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateSpeaker(GLMesh& speakerMesh) {
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f, // bottom left
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // bottom right
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top right
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // top right
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 1.0f, // top left
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.5f, 0.0f, // bottom left

       //Front Face         //Positive Z Normal
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.5f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //Left Face          //Negative X Normal
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.8f, 0.6f, // bottom right
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.8f, 0.6f, // top right
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.6f, 0.4f, // top left
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.6f, 0.4f, // top left
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.6f, 0.4f, // bottom left
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.8f, 0.4f, // bottom right

     //Right Face         //Positive X Normal
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f, 0.6f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.8f, 0.6f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f, 0.4f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f, 0.4f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.6f, 0.4f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f, 0.4f,

     //Bottom Face        //Negative Y Normal
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f, 0.6f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f, 0.6f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f, 0.4f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f, 0.4f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f, 0.4f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f, 0.4f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    speakerMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &speakerMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(speakerMesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, speakerMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, speakerMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateTorus(GLMesh& torusMesh)
{
    int _mainSegments = 30;
    int _tubeSegments = 30;
    float _mainRadius = 1.0f;
    float _tubeRadius = .1f;

    auto mainSegmentAngleStep = glm::radians(360.0f / float(_mainSegments));
    auto tubeSegmentAngleStep = glm::radians(360.0f / float(_tubeSegments));

    std::vector<glm::vec3> vertex_list;
    std::vector<std::vector<glm::vec3>> segments_list;
    std::vector<glm::vec3> normals_list;
    std::vector<glm::vec2> texture_coords;
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 normal;
    glm::vec3 vertex;
    glm::vec2 text_coord;

    // generate the torus vertices
    auto currentMainSegmentAngle = 0.0f;
    for (auto i = 0; i < _mainSegments; i++)
    {
        // Calculate sine and cosine of main segment angle
        auto sinMainSegment = sin(currentMainSegmentAngle);
        auto cosMainSegment = cos(currentMainSegmentAngle);
        auto currentTubeSegmentAngle = 0.0f;
        std::vector<glm::vec3> segment_points;
        for (auto j = 0; j < _tubeSegments; j++)
        {
            // Calculate sine and cosine of tube segment angle
            auto sinTubeSegment = sin(currentTubeSegmentAngle);
            auto cosTubeSegment = cos(currentTubeSegmentAngle);

            // Calculate vertex position on the surface of torus
            auto surfacePosition = glm::vec3(
                (_mainRadius + _tubeRadius * cosTubeSegment) * cosMainSegment,
                (_mainRadius + _tubeRadius * cosTubeSegment) * sinMainSegment,
                _tubeRadius * sinTubeSegment);

            //vertex_list.push_back(surfacePosition);
            segment_points.push_back(surfacePosition);

            // Update current tube angle
            currentTubeSegmentAngle += tubeSegmentAngleStep;
        }
        segments_list.push_back(segment_points);
        segment_points.clear();

        // Update main segment angle
        currentMainSegmentAngle += mainSegmentAngleStep;
    }

    float horizontalStep = 1.0 / _mainSegments;
    float verticalStep = 1.0 / _tubeSegments;
    float u = 0.0;
    float v = 0.0;

    // connect the various segments together, forming triangles
    for (int i = 0; i < _mainSegments; i++)
    {
        for (int j = 0; j < _tubeSegments; j++)
        {
            if (((i + 1) < _mainSegments) && ((j + 1) < _tubeSegments))
            {
                vertex_list.push_back(segments_list[i][j]);
                normal = normalize(segments_list[i][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v));
                vertex_list.push_back(segments_list[i][j + 1]);
                normal = normalize(segments_list[i][j + 1] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v + verticalStep));
                vertex_list.push_back(segments_list[i + 1][j + 1]);
                normal = normalize(segments_list[i + 1][j + 1] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u + horizontalStep, v + verticalStep));
                vertex_list.push_back(segments_list[i][j]);
                normal = normalize(segments_list[i][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v));
                vertex_list.push_back(segments_list[i + 1][j]);
                normal = normalize(segments_list[i + 1][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u + horizontalStep, v));
                vertex_list.push_back(segments_list[i + 1][j + 1]);
                normal = normalize(segments_list[i + 1][j + 1] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u + horizontalStep, v - verticalStep));
                vertex_list.push_back(segments_list[i][j]);
                normal = normalize(segments_list[i][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v));
            }
            else
            {
                if (((i + 1) == _mainSegments) && ((j + 1) == _tubeSegments))
                {
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i][0]);
                    normal = normalize(segments_list[i][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, 0));
                    vertex_list.push_back(segments_list[0][0]);
                    normal = normalize(segments_list[0][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[0][j]);
                    normal = normalize(segments_list[0][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v));
                    vertex_list.push_back(segments_list[0][0]);
                    normal = normalize(segments_list[0][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                }
                else if ((i + 1) == _mainSegments)
                {
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i][j + 1]);
                    normal = normalize(segments_list[i][j + 1] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v + verticalStep));
                    vertex_list.push_back(segments_list[0][j + 1]);
                    normal = normalize(segments_list[0][j + 1] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v + verticalStep));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[0][j]);
                    normal = normalize(segments_list[0][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v));
                    vertex_list.push_back(segments_list[0][j + 1]);
                    normal = normalize(segments_list[0][j + 1] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v + verticalStep));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                }
                else if ((j + 1) == _tubeSegments)
                {
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i][0]);
                    normal = normalize(segments_list[i][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, 0));
                    vertex_list.push_back(segments_list[i + 1][0]);
                    normal = normalize(segments_list[i + 1][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u + horizontalStep, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i + 1][j]);
                    normal = normalize(segments_list[i + 1][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u + horizontalStep, v));
                    vertex_list.push_back(segments_list[i + 1][0]);
                    normal = normalize(segments_list[i + 1][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u + horizontalStep, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                }

            }
            v += verticalStep;
        }
        v = 0.0;
        u += horizontalStep;
    }

    std::vector<GLfloat> combined_values;

    // combine interleaved vertices, normals, and texture coords
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex = vertex_list[i];
        normal = normals_list[i];
        text_coord = texture_coords[i];
        combined_values.push_back(vertex.x);
        combined_values.push_back(vertex.y);
        combined_values.push_back(vertex.z);
        combined_values.push_back(normal.x);
        combined_values.push_back(normal.y);
        combined_values.push_back(normal.z);
        combined_values.push_back(text_coord.x);
        combined_values.push_back(text_coord.y);
    }

    // total float values per each type
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    // store vertex and index count
    torusMesh.nVertices = vertex_list.size();
    torusMesh.nIndices = 0;

    // Create VAO
    glGenVertexArrays(1, &torusMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(torusMesh.vao);

    // Create VBOs
    glGenBuffers(1, torusMesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, torusMesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * combined_values.size(), combined_values.data(), GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}
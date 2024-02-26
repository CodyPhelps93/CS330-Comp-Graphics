

#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE, EXIT_SUCCESS
#include <GL/glew.h>        // GLEW Lib
#include <GLFW/glfw3.h>     // GLFW Lib
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "MeshCreation.h"


using namespace std;

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

namespace
{

    // declare const varible for window
    const char* const WINDOW_TITLE = "CS330 Project Cody Phelps";
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Stores GL data relative to mesh
    //struct GLMesh
    //{
    //    GLuint vao;  // Handle for the vertex array object
    //    GLuint vbos[2];  // Handle for the vertex array object
    //    GLuint nIndices;   // Number of indices of the mesh
    //    GLuint nVertices;
    //};

    //Main GLFW window
    GLFWwindow* gWindow = nullptr;
    // Triangel mesh data
    GLMesh gMesh;
    GLMesh gCubeMesh;
    GLMesh planeMesh;
    GLMesh standMesh;
    GLMesh towerMesh;
    GLMesh monitorMesh;
    GLMesh speakerMesh;
    GLMesh torusMesh;
    GLMesh keyboardMesh;
    // Textru id
    GLuint gTextureId;
    GLuint gDeskId;
    GLuint gStandId;
    GLuint gTowerId;
    GLuint gMonitorId;
    GLuint gSpeakerId;
    GLuint gTorusId;
    GLuint gKeyboardId;
    glm::vec2 gUVScale(1.0f, 1.0f);
    // shader program
    //GLuint gProgramId;
    GLuint gCubeProgramId;
    GLuint gLampProgramId;

    //bool for wireframe
    static bool enableWireframe = false;
    static bool tabKeyPressed = false;
    static bool renderSecondLight = false;
    static bool pKeyPressed = false;
    

    // camera
    Camera gCamera(glm::vec3(0.0f, 1.0f, 6.0f));
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    bool isOrtho = false;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Subject position and scale
    glm::vec3 gCubePosition(0.0f, 0.0f, 0.0f);
    glm::vec3 gCubeScale(2.0f);

    // Cube and light color
    const int NUM_LIGHTS = 2;
    //::vec3 gObjectColor(0.6f, 0.5f, 0.75f);
    glm::vec3 gLightColors[NUM_LIGHTS]{

        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 1.0f)
    };
    glm::vec3 gObjectColor(1.f, 0.2f, 0.0f);
    float intensity[NUM_LIGHTS]{
        // Key Light, Fill Light
        1.0f, 0.00001f
    };

    float highlightSize = 9.0f;


    // Light position and scale
    glm::vec3 gLightPosition[NUM_LIGHTS]{
        glm::vec3(-0.5f, 0.5f, 6.0f),
        glm::vec3(1.3f, -1.0f, -0.1f)
    };

    glm::vec3 gLightScale[NUM_LIGHTS]{
        glm::vec3(0.2f),
        glm::vec3(-0.1),

    };

}

/*Functions to initialze the program
* set window size
* redraw and render graphics
*/
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UCreateMesh(GLMesh& mesh);
void UCreateCubeMesh(GLMesh& mesh);
//void UCreateStand(GLMesh& mesh);
void UDestroyMesh(GLMesh& cubeMesh);
void URender(const GLMesh& mesh);
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
bool UCreateTexture(const char* filename, GLuint& textureId);
bool UCreateCubeMap(vector<const char*> filenames, GLuint& textureId);
void UDestroyTexture(GLuint textureId);
void toggleOrtho();

/* Cube Vertex Shader Source Code*/
const GLchar* cubeVertexShaderSource = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Cube Fragment Shader Source Code*/
const GLchar* cubeFragmentShaderSource = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing cube color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
const int NUM_LIGHTS = 2;

uniform vec3 objectColor;
uniform vec3 lightColor[NUM_LIGHTS];
uniform vec3 lightPos[NUM_LIGHTS];
uniform vec3 viewPosition;
uniform float intensity[NUM_LIGHTS];
uniform float highlightSize;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;
uniform bool toggleSecondLight;
uniform vec3 lightViewDirection[NUM_LIGHTS];

void main()
{
    /* Phong lighting model calculations to generate ambient, diffuse, and specular components */

    // Initialize lighting components to zero
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for (int i = 0; i < NUM_LIGHTS; i++) {
        if (i == 1 && toggleSecondLight == false) {
            continue;
        }

        // Calculate Ambient lighting
        float ambientStrength = 0.1f;  // Set ambient or global lighting strength
        ambient += ambientStrength * lightColor[i];

        // Calculate Diffuse lighting
        vec3 norm = normalize(vertexNormal);
        vec3 lightDirection;

        if (i == 1) {
            lightDirection = normalize(lightViewDirection[i]);
        }
        else {
            lightDirection = normalize(lightPos[i] - vertexFragmentPos);
        }

        float distance = length(lightPos[i] - vertexFragmentPos);
        float attenuation = 1.0 / (1.0 + 0.1 * distance + 0.01 * distance * distance);
        float impact = max(dot(norm, lightDirection), 0.0) * attenuation;
        diffuse += impact * lightColor[i];

        // Calculate Specular lighting
        vec3 viewDir = normalize(viewPosition - vertexFragmentPos);
        vec3 reflectDir = reflect(-lightDirection, norm);
        float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize) * attenuation;
        specular += intensity[i] * specularComponent * lightColor[i];
    }

    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);
    vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

    fragmentColor = vec4(phong, 1.0);
}
);


/* Lamp Shader Source Code*/
const GLchar* lampVertexShaderSource = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

        //Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
}
);


/* Fragment Shader Source Code*/
const GLchar* lampFragmentShaderSource = GLSL(440,

    out vec4 fragmentColor; // For outgoing lamp color (smaller cube) to the GPU

void main()
{
    fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
}
);



// used to flip images because Y axis is loaded on the bottom but Y axis on OpenGL is up
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}




// Main function for OpenGL
int main(int argc, char* argv[])
{
  

    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create Mesh
    UCreateMonitor(monitorMesh);  // Calls function to create the Vertex Buffer Object
    UCreateCubeMesh(gCubeMesh);
    UCreateCubeMesh(gCubeMesh);
    UCreatePlane(planeMesh);
    UCreateStand(standMesh);
    UCreateTower(towerMesh);
    UCreateSpeaker(speakerMesh);
    UCreateTorus(torusMesh);
    UCreateKeyboard(keyboardMesh);
    // Create Shader Program
    if (!UCreateShaderProgram(cubeVertexShaderSource, cubeFragmentShaderSource, gCubeProgramId))
        return EXIT_FAILURE;
    if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLampProgramId))
        return EXIT_FAILURE;




    //Open Texture and bind it
    const char* texFilename = "BrickWall.PNG";
    if (!UCreateTexture(texFilename, gTextureId)) {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }
    texFilename = "desk.png";
    if (!UCreateTexture(texFilename, gDeskId)) {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }

    texFilename = "stand.png";
    if (!UCreateTexture(texFilename, gStandId)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }

    texFilename = "monitor.png";
    if (!UCreateTexture(texFilename, gMonitorId)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }


    texFilename = "tower.png";
    if (!UCreateTexture(texFilename, gTowerId)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }

    texFilename = "speaker.png";
    if (!UCreateTexture(texFilename, gSpeakerId)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }

    texFilename = "monitor.png";
    if (!UCreateTexture(texFilename, gTorusId)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }

    texFilename = "keyboard.png";
    if (!UCreateTexture(texFilename, gKeyboardId)) {
        cout << "Failed to load texture" << texFilename << endl;
        return EXIT_FAILURE;
    }


    glUseProgram(gCubeProgramId);
    //set the texture as unit 0
    glUniform1i(glGetUniformLocation(gCubeProgramId, "uTexture"), 0);


    //Set background color using GLclear
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // create render loop
    while (!glfwWindowShouldClose(gWindow))
    {

        // timing for frames
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input

        UProcessInput(gWindow);

        URender(monitorMesh);
        URender(gCubeMesh);
        URender(gCubeMesh);
        URender(planeMesh);
        URender(standMesh);
        URender(towerMesh);
        URender(speakerMesh);
        URender(torusMesh);
        URender(keyboardMesh);

        glfwPollEvents();

    }

    // Destroy mesh data here
    UDestroyMesh(monitorMesh);
    UDestroyMesh(gCubeMesh);
    UDestroyMesh(planeMesh);
    UDestroyMesh(standMesh);
    UDestroyMesh(towerMesh);
    UDestroyMesh(speakerMesh);
    UDestroyMesh(torusMesh);
    UDestroyMesh(keyboardMesh);

    UDestroyTexture(gTextureId);
    UDestroyTexture(gDeskId);
    UDestroyTexture(gStandId);
    UDestroyTexture(gMonitorId);
    UDestroyTexture(gTowerId);
    UDestroyTexture(gSpeakerId);
    UDestroyTexture(gTorusId);
    UDestroyTexture(gKeyboardId);

    //Destroy Shader
    UDestroyShaderProgram(gCubeProgramId);
    UDestroyShaderProgram(gLampProgramId);

    std::exit(EXIT_SUCCESS); // Terminates the pogram succesfully
}

//Initialize GLFW, GLEW, and create the window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure (desired OpenGL Version for this we will use 3)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //GLFW: window creation:

    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);

    // Tells GLFW to capture mouse and disable cursor
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize

    // Used if using GLEW 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;

    }

    // Display GPU OpenGL Version

    std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return true;
}

void toggleSecondLight() {
    renderSecondLight = !renderSecondLight;
}

void toggleOrtho() {
    isOrtho = !isOrtho;
}
// process key input

void UProcessInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //quick wireframe enable and disable
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tabKeyPressed)
    {
        tabKeyPressed = true; // Set flag to true to indicate Tab key is pressed

        // Toggle wireframe mode
        enableWireframe = !enableWireframe;
        glPolygonMode(GL_FRONT_AND_BACK, enableWireframe ? GL_LINE : GL_FILL);
        if (enableWireframe)
            cout << "Wire Mode Enabled!" << endl;
        else
            cout << "Wire Mode Disabled!" << endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
    {
        tabKeyPressed = false; // Reset the flag when Tab key is released
    }


    // movement with wasd
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        toggleSecondLight();  // Toggle rendering of the second light on 'L' key press
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        cout << "O button pressed" << endl;
        toggleOrtho();
    }


}

// glfw: window resize function (executes when window is resized by OS or user)

void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Mouse callback when mouse moves
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}

// Mouse wheel callback
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

    // if mouse wheel scroll forward
    if (yoffset == 1) {
        gCamera.MovementSpeed += 2.5f; //gCamera.MovementSpeed is used to calculate velocity in camera.h


        if (gCamera.MovementSpeed >= 45.0f) {
            gCamera.MovementSpeed = 45.0f;
        }
        cout << "Speed set to: " << gCamera.MovementSpeed << endl;
    }
    // if mouse wheel scroll back
    if (yoffset == -1) {
        gCamera.MovementSpeed -= 1.5f;
        if (gCamera.MovementSpeed < 0.0f) {
            gCamera.MovementSpeed = 0.0f;
        }

        cout << "Speed set to: " << gCamera.MovementSpeed << endl;
    }
}

// function that renders the frame
void URender(const GLMesh& mesh)
{
    glm::mat4 rotation;
    glm::mat4 projection;
    // enable z-depth
    glEnable(GL_DEPTH_TEST);

    // clear background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // scale shape must be done first
    glm::mat4 scale = glm::scale(glm::vec3(1.25f, 0.75f, 0.01f));
    // rotate shape (x, y, z)
    //glm::mat4 rotation = glm::rotate(1.0f, glm::vec3(0.0f, 0.5f, 0.0f));
    // translates by 0.5 in the y axis
    glm::mat4 translation = glm::translate(glm::vec3(-0.025f, -0.90f, 0.1f));
    // transformation applied in the right-to-left order
    glm::mat4 model = translation * scale;


    // create view
    glm::mat4 view = gCamera.GetViewMatrix();

    // Create Perspective view (Field of view , aspect ratio, distance near plane to camera, distance of far plane to camera)
    if (!isOrtho){
        projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    }
    else if (isOrtho) {
        projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
    }

    // set shader to be useds
    glUseProgram(gCubeProgramId);

    // Retrieves and passes transform matrices to the shader
    GLint modelLoc = glGetUniformLocation(gCubeProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gCubeProgramId, "view");
    GLint projLoc = glGetUniformLocation(gCubeProgramId, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glm::vec3 viewDirection = glm::normalize(-gLightPosition[1]);
    GLint lightViewDirLoc = glGetUniformLocation(gCubeProgramId, "lightViewDirection");
    glUniform3fv(lightViewDirLoc + 1, 1, glm::value_ptr(viewDirection));

    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    GLint intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    GLint highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");

    //for loop to pass light varibles to shader
    for (int i = 0; i < NUM_LIGHTS; i++) {
        glUniform3fv(lightColorLoc + i, 1, glm::value_ptr(gLightColors[i]));
        glUniform3fv(lightPositionLoc + i, 1, glm::value_ptr(gLightPosition[i]));
        glUniform1f(intensityLoc, intensity[i]);
        glUniform1f(highlightSizeLoc, highlightSize);
    }

    // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    //glUniform3f(LightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    //glUniform3f(lightPositionLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPosition = gCamera.Position;
    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);


    GLint UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));


    // Activate VBOs contained with mesh's VAO
    glBindVertexArray(monitorMesh.vao);
    
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gMonitorId);

    // Draw Triangles
    glDrawArrays(GL_TRIANGLES, 0, monitorMesh.nVertices);

    glBindVertexArray(planeMesh.vao);

    // 1. Scales the object
    scale = glm::scale(glm::vec3(2.5f, 1.0f, 1.5f));
    // 2. Rotate the object
    rotation = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 1.0f));
    // 3. Position the object
    translation = glm::translate(glm::vec3(0.0f, -1.5f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = translation * rotation * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");


    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);

    UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Draws the triangles
     // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gDeskId);
    glDrawElements(GL_TRIANGLES, planeMesh.nIndices, GL_UNSIGNED_INT, (void*)0);

    // Draw the stand
    glBindVertexArray(standMesh.vao);

    // 1. Scales the object
    scale = glm::scale(glm::vec3(0.5f, 1.0f, 0.5f));
    // 2. Rotate the object
    rotation = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 1.0f));
    // 3. Position the object
    translation = glm::translate(glm::vec3(0.0f, -1.5f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = translation * rotation * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");


    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);

    UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Draws the triangles
     // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gStandId);
    glDrawElements(GL_TRIANGLES, standMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Draw the tower
    glBindVertexArray(towerMesh.vao);

    // 1. Scales the object
    scale = glm::scale(glm::vec3(0.5f, 0.75f, 1.0f));
    // 2. Rotate the object
    //rotation = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 1.0f));
    // 3. Position the object
    translation = glm::translate(glm::vec3(1.5f, -1.1f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = translation * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");


    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);

    UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Draws the triangles
     // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTowerId);
    glDrawArrays(GL_TRIANGLES, 0, towerMesh.nVertices);

    // draw cube for speaker
    glBindVertexArray(speakerMesh.vao);

    // 1. Scales the object
    scale = glm::scale(glm::vec3(0.175f, 0.275f, 0.2f));
    // 2. Rotate the object
    //rotation = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 1.0f));
    // 3. Position the object
    translation = glm::translate(glm::vec3(-1.2f, -1.37f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    model = translation * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");


    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);

    UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Draws the triangles
     // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gSpeakerId);
    glDrawArrays(GL_TRIANGLES, 0, speakerMesh.nVertices);

    // Create torus for speakers
    glBindVertexArray(torusMesh.vao);

    // 1. Scales the object
    scale = glm::scale(glm::vec3(-0.09f, -0.09f, -0.09f));
    // 2. Rotate the object
    //rotation = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 1.0f));
    // 3. Position the object
    translation = glm::translate(glm::vec3(-1.2f, -1.37f, 0.09f));
    // Model matrix: transformations are applied right-to-left order
    model = translation * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");


    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);

    UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Draws the triangles
     // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gSpeakerId);
    glDrawArrays(GL_TRIANGLES, 0, torusMesh.nVertices);

    // Draws the keyboard
        // Create torus for speakers
    glBindVertexArray(keyboardMesh.vao);

    // 1. Scales the object
    scale = glm::scale(glm::vec3(1.0f, 0.05f, 0.25f));
    // 2. Rotate the object
    //rotation = glm::rotate(0.0f, glm::vec3(1.0, 0.0f, 1.0f));
    // 3. Position the object
    translation = glm::translate(glm::vec3(0.0f, -1.45f, 1.0f));
    // Model matrix: transformations are applied right-to-left order
    model = translation * scale;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    objectColorLoc = glGetUniformLocation(gCubeProgramId, "objectColor");
    lightColorLoc = glGetUniformLocation(gCubeProgramId, "lightColor");
    lightPositionLoc = glGetUniformLocation(gCubeProgramId, "lightPos");
    viewPositionLoc = glGetUniformLocation(gCubeProgramId, "viewPosition");
    intensityLoc = glGetUniformLocation(gCubeProgramId, "intensity");
    highlightSizeLoc = glGetUniformLocation(gCubeProgramId, "highlightSize");


    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);

    UVScaleLoc = glGetUniformLocation(gCubeProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    // Draws the triangles
     // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gKeyboardId);
    glDrawArrays(GL_TRIANGLES, 0, keyboardMesh.nVertices);

    // Draw the lamps
    GLint isSecondLightEnabledLoc = glGetUniformLocation(gCubeProgramId, "toggleSecondLight");
    glUniform1i(isSecondLightEnabledLoc, renderSecondLight);
    for (int i = 0; i < NUM_LIGHTS; ++i) {
        if (i != 1 || (i == 1 && renderSecondLight)) {
            glUseProgram(gLampProgramId);
            glBindVertexArray(gCubeMesh.vao);

            // Use the single light position variable for all lamps
            glm::vec3 lampPosition = gLightPosition[i];

            // Transform the smaller cube used as a visual cue for the light source
            glm::mat4 lampModel = glm::translate(lampPosition) * glm::scale(gLightScale[i]);

            // Pass matrix data to the Lamp Shader program's matrix uniforms
            modelLoc = glGetUniformLocation(gLampProgramId, "model");
            viewLoc = glGetUniformLocation(gLampProgramId, "view");
            projLoc = glGetUniformLocation(gLampProgramId, "projection");

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lampModel));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));



            glDrawArrays(GL_TRIANGLES, 0, gCubeMesh.nVertices);
        }
    }

    //Deactivate VAO
    glBindVertexArray(0);
    glUseProgram(0);

    // glfw: swap buffers and poll IO events
    glfwSwapBuffers(gWindow);
}



// Create the UCreateMesh function



void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}

//Implemets the UCreateShaders Function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{

    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a shader program object
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile vertex shader
    glCompileShader(vertexShaderId);

    //Check for errors compiling shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // compile fragment shader
    glCompileShader(fragmentShaderId);
    // check for compile erros with fragment shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }


    // Attached compiled shaders to shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);
    // check linking erros
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId); // use the shader pogram

    return true;
}



//texture
bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Set the texture wrapping parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture.

        return true;
    }

    // Error loading the image
    return false;
}

bool UCreateCubeMap(vector<const char*> filenames, GLuint& textureId)
{
    int width, height, channels;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    for (GLuint i = 0; i < 6; ++i) {
        unsigned char* image = stbi_load(filenames[i], &width, &height, &channels, 0);
        if (image) {
            flipImageVertically(image, width, height, channels);

            if (channels == 3)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            else if (channels == 4)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            else {
                std::cout << "Not implemented to handle image with " << channels << " channels" << std::endl;
                stbi_image_free(image);
                return false;
            }

            stbi_image_free(image);
        }
        else {
            std::cout << "Error loading image: " << filenames[i] << std::endl;
            return false;
        }
    }

    // Set the texture parameters.
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0); // Unbind the texture.

    return true;
}

// delete texture;
void UDestroyTexture(GLuint textureId) {
    glGenTextures(1, &textureId);
}

// delete shader program
void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}

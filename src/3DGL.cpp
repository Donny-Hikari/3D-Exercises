#include <cstdio>
#include <cstring>

#include <GL/glew.h>
#include <GL/glut.h>

#include <donny/logger.hpp>

#include "../lib/DGLShaders.hpp"

enum VAO_IDs { GLTriangles, Trapezoidal, Pentagon, Crystal, NumVAOs };
// enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0, fragColor = 1 };
enum Shader_IDs { DefaultShader, PentagonShader, CrystalShader, NumShaders };

const GLuint NumVertices[] = { 42, 12, 15, 24 };
const struct {
    int x, y;
} v2WndResolution = { 512, 512 };

GLuint VAOs[NumVAOs];
GLuint VertexBuffers[NumVAOs];
GLuint FragBuffers[NumVAOs];
GLuint ShaderProgram[NumVAOs];

GLuint uResolutionLoc = 0;

void initGLTriangles()
{
    // GLfloat vertices[NumVertices][2] = {
    //     { -0.90, -0.90 },
    //     {  0.85, -0.90 },
    //     { -0.90,  0.85 },
    //     {  0.90, -0.85 },
    //     {  0.90,  0.90 },
    //     { -0.85,  0.90 }
    // };
    const GLfloat vertices[ NumVertices[GLTriangles] ][2] = {
        /* G */
        { -0.90,  0.90 },
        { -0.90,  0.60 },
        { -0.10,  0.90 },
        { -0.10,  0.90 },
        { -0.90,  0.60 },
        { -0.10,  0.60 },

        { -0.90,  0.90 },
        { -0.90, -0.90 },
        { -0.70,  0.90 },
        { -0.70,  0.90 },
        { -0.90, -0.90 },
        { -0.70, -0.90 },

        { -0.90, -0.60 },
        { -0.90, -0.90 },
        { -0.10, -0.10 },
        { -0.90, -0.90 },
        { -0.60, -0.90 },
        { -0.10, -0.10 },
        
        { -0.55, -0.05 },
        { -0.55, -0.30 },
        { -0.10, -0.05 },
        { -0.10, -0.05 },
        { -0.55, -0.30 },
        { -0.10, -0.30 },

        { -0.35, -0.10 },
        { -0.35, -0.90 },
        { -0.10, -0.10 },
        { -0.10, -0.10 },
        { -0.35, -0.90 },
        { -0.10, -0.90 },

        /* L */
        {  0.10,  0.90 },
        {  0.10, -0.90 },
        {  0.40, -0.90 },
        {  0.40, -0.90 },
        {  0.40,  0.90 },
        {  0.10,  0.90 },

        {  0.10, -0.60 },
        {  0.10, -0.90 },
        {  0.90, -0.60 },
        {  0.90, -0.60 },
        {  0.10, -0.90 },
        {  0.90, -0.90 },
    };

    glBindVertexArray(VAOs[GLTriangles]);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffers[GLTriangles]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPosition);
}

void initTrapezoidal()
{
    const GLfloat vertices[ NumVertices[Trapezoidal] ][2] = {
        { -0.80, -0.60 },
        { -0.30, -0.60 },
        { -0.30,  0.60 },

        { -0.30,  0.60 },
        { -0.30, -0.60 },
        {  0.30,  0.60 },

        {  0.30,  0.60 },
        { -0.30, -0.60 },
        {  0.30, -0.60 },

        {  0.30, -0.60 },
        {  0.80, -0.60 },
        {  0.30,  0.60 },
    };

    glBindVertexArray(VAOs[Trapezoidal]);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffers[Trapezoidal]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPosition);
}

void initPentagon()
{
    const GLfloat vertices[ NumVertices[Pentagon] ][2] = {
        {  0.00,  0.00 },
        {  0.00,  0.90 },
        { -0.96,  0.18 },

        {  0.00,  0.00 },
        { -0.96,  0.18 },
        { -0.60, -0.90 },

        {  0.00,  0.00 },
        { -0.60, -0.90 },
        {  0.60, -0.90 },

        {  0.00,  0.00 },
        {  0.60, -0.90 },
        {  0.96,  0.18 },

        {  0.00,  0.00 },
        {  0.96,  0.18 },
        {  0.00,  0.90 },        
    };

    GLfloat fragments[ NumVertices[Pentagon] ][3];

    glBindVertexArray(VAOs[Pentagon]);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffers[Pentagon]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPosition);

    glBindBuffer(GL_ARRAY_BUFFER, FragBuffers[Pentagon]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fragments),
                 fragments, GL_STATIC_DRAW);

    glVertexAttribPointer(fragColor, 3, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(fragColor);
}

void initUBTriangles()
{
    const GLfloat vertices[ NumVertices[Crystal] ][3] = {
        {  0.000,  1.414,  0.000 },
        { -1.000,  0.000, -1.000 },
        {  1.000,  0.000, -1.000 },

        {  0.000,  1.414,  0.000 },
        {  1.000,  0.000, -1.000 },
        {  1.000,  0.000,  1.000 },
        
        {  0.000,  1.414,  0.000 },
        {  1.000,  0.000,  1.000 },
        { -1.000,  0.000,  1.000 },
        
        {  0.000,  1.414,  0.000 },
        { -1.000,  0.000,  1.000 },
        { -1.000,  0.000, -1.000 },
        
        { -1.000,  0.000, -1.000 },
        {  1.000,  0.000, -1.000 },
        {  0.000, -1.414,  0.000 },

        {  1.000,  0.000, -1.000 },
        {  1.000,  0.000,  1.000 },
        {  0.000, -1.414,  0.000 },
        
        {  1.000,  0.000,  1.000 },
        { -1.000,  0.000,  1.000 },
        {  0.000, -1.414,  0.000 },
        
        { -1.000,  0.000, -1.000 },
        { -1.000,  0.000,  1.000 },
        {  0.000, -1.414,  0.000 },
    };

    GLfloat fragments[ NumVertices[Crystal] ][3];

    glBindVertexArray(VAOs[Crystal]);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffers[Crystal]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vPosition);

    glBindBuffer(GL_ARRAY_BUFFER, FragBuffers[Crystal]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fragments),
                 fragments, GL_STATIC_DRAW);

    glVertexAttribPointer(fragColor, 3, GL_FLOAT,
                          GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(fragColor);
}

void init(void)
{
    glGenVertexArrays(NumVAOs, VAOs);
    glGenBuffers(NumVAOs, VertexBuffers);
    glGenBuffers(NumVAOs, FragBuffers);

    initGLTriangles();
    initTrapezoidal();
    initPentagon();
    initUBTriangles();
            
    ShaderFileInfo sfis[][2] = {
        { { GL_VERTEX_SHADER, "../shaders/default.vert" },
          { GL_FRAGMENT_SHADER, "../shaders/default.frag" } },
        { { GL_VERTEX_SHADER, "../shaders/pentagon.vert" },
          { GL_FRAGMENT_SHADER, "../shaders/pentagon.frag" } },
        { { GL_VERTEX_SHADER, "../shaders/crystal.vert" },
          { GL_FRAGMENT_SHADER, "../shaders/crystal.frag" } },
    };

    ShaderProgram[DefaultShader]
        = ShaderProgram[GLTriangles]
        = ShaderProgram[Trapezoidal]
        = LoadShaders(sfis[DefaultShader]);
    glUseProgram(ShaderProgram[DefaultShader]);
    uResolutionLoc = glGetUniformLocation(ShaderProgram[DefaultShader], "uResolution");
    glUniform2f(uResolutionLoc, v2WndResolution.x, v2WndResolution.y);

    ShaderProgram[Pentagon]
        = LoadShaders(sfis[PentagonShader]);
    glUseProgram(ShaderProgram[Pentagon]);

    ShaderProgram[Crystal]
        = LoadShaders(sfis[CrystalShader]);
    glUseProgram(ShaderProgram[Crystal]);
    srand(time(nullptr));
}

struct Property {
    GLfloat scale;
    GLfloat rotation[3];
};
void moveCrystal(Property property)
{
	const GLchar *propertyNames[] = {
        "scale",
        "rotation",
    };
    const int propertyCount = donny::length_of_array(propertyNames);

    GLuint propertyInd;
    GLint propertySize;
    GLbyte *blockBuffer;
	GLuint propertyIndices[propertyCount];
	GLint propertyOffset[propertyCount];

    propertyInd = glGetUniformBlockIndex(ShaderProgram[Crystal], "Property");
    glGetActiveAtomicCounterBufferiv(ShaderProgram[Crystal], propertyInd,
        GL_UNIFORM_BLOCK_DATA_SIZE, &propertySize);
    //donny::logstdout << propertyInd << " " << propertySize << donny::endl;
    blockBuffer = new GLbyte[propertySize];

	glGetUniformIndices(ShaderProgram[Crystal], propertyCount, propertyNames, propertyIndices);
	glGetActiveUniformsiv(ShaderProgram[Crystal],
        propertyCount, propertyIndices,
        GL_UNIFORM_OFFSET, propertyOffset);

    memcpy(blockBuffer + propertyOffset[0], &property.scale, sizeof(property.scale));
    memcpy(blockBuffer + propertyOffset[1], &property.rotation, sizeof(property.rotation));

    //donny::logstdout << (int)propertyIndices[1] << " " << propertyOffset[1] << donny::endl;

    GLuint uniformblock;
    glGenBuffers(1, &uniformblock);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformblock);
    glBufferData(GL_UNIFORM_BUFFER, propertySize, blockBuffer, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, propertyInd, uniformblock);

    delete[] blockBuffer;
}

int nNowDisplay = 0;
Property crystalProperty = {
    0.5,
    { 0, 0, 0 }, //(GLfloat)(rand() % 200 - 100) / 100, 3.141592657*90/180
};

void display(void)
{
    //donny::logstdout << "Refreshing..." << donny::endl;
    //donny::logstdout << "Now displaying: " << nNowDisplay << donny::endl;

    if (nNowDisplay == Crystal)
    {
        crystalProperty.rotation[0] += 0.001;
        crystalProperty.rotation[1] += 0.003;
        crystalProperty.rotation[2] += 0.007;
        //donny::logstdout << crystalProperty.rotation[2] << donny::endl;
        moveCrystal(crystalProperty);
    }

    glClearStencil(0);

    // glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // glEnable(GL_STENCIL_TEST); 
    // glStencilFunc(GL_ALWAYS, 1, -1);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // glutWireSphere(5,9,9);	
    // glStencilFunc(GL_NOTEQUAL, 1, -1);
    // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); 
    // glLineWidth(2);
    // glPolygonMode(GL_FRONT, GL_LINE);
    // glutWireSphere(5,9,9);
    // glLineWidth(1);

    glUseProgram(ShaderProgram[nNowDisplay]);
    glBindVertexArray(VAOs[nNowDisplay]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices[nNowDisplay]);

    glFlush();
}

void keyboard(u_char key, int x, int y)
{
    switch (key)
    {
    case 0x31: // 1
        nNowDisplay = GLTriangles;
        glDisable(GL_DEPTH_TEST);
        break;
    case 0x32: // 2
        nNowDisplay = Trapezoidal;
        glDisable(GL_DEPTH_TEST);
        break;
    case 0x33: // 3
        nNowDisplay = Pentagon;
        glDisable(GL_DEPTH_TEST);
        break;
    case 0x34:
        nNowDisplay = Crystal;
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        break;
    case 0x1B:
        exit(0);
        break;
    }
    donny::logstdout << "Key down: " << key << donny::endl;
    glutPostRedisplay();
    // glFinish();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(v2WndResolution.x, v2WndResolution.y);
    // glutInitContextVersion(4, 3);
    // glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("3DGL");
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
}

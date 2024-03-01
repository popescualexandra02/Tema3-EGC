#include "lab_m1/tema3/tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;



Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


glm::vec3 lightsPosition;
glm::vec3 lightsDirection;
unsigned int Shininess;
float Kd, Ks;
float cut_off[2];

void Tema3::Init()
{
    //poze din textures
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "textures");

    // Load textures
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "moon.jpg").c_str(), GL_REPEAT);
        mapTextures["moon"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "apa.jpg").c_str(), GL_REPEAT);
        mapTextures["apa"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "iarba.jpg").c_str(), GL_REPEAT);
        mapTextures["iarba"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "old_wall.jpg").c_str(), GL_REPEAT);
        mapTextures["wall"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "white.png").c_str(), GL_REPEAT);
        mapTextures["white"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "wood.jpg").c_str(), GL_REPEAT);
        mapTextures["wood"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "panza.jpg").c_str(), GL_REPEAT);
        mapTextures["panza"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "grey.jpg").c_str(), GL_REPEAT);
        mapTextures["grey"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "steag.jpg").c_str(), GL_REPEAT);
        mapTextures["steag"] = texture;
    }
    
    // Load meshes
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cylinder");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cylinder.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create the water
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(5, 0, -5),    // top right
            glm::vec3(5, 0, 5),    // bottom right
            glm::vec3(-5, 0, 5),    // bottom left
            glm::vec3(-5, 0, -5),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(0.0f, 0.0f),
            glm::vec2(50, 0.0f),
            glm::vec2(50, 50),
            glm::vec2(0.0f, 50)

        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("water");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    //create the box
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0, 0.2f, 0),   // top left back
            glm::vec3(0.8f, 0.2f, 0),    // top right back
            glm::vec3(0.8f, 0, 0),   // bottom right back
            glm::vec3(0, 0, 0),  // bottom left back

            glm::vec3(0, 0.2f, 0.5f),    // top left front
            glm::vec3(0.8f, 0.2f, 0.5f),     // top right front
            glm::vec3(0.8f, 0, 0.5f),    // bottom right front
            glm::vec3(0, 0, 0.5f)    // bottom left front
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 0),   // top face
            glm::vec3(0, 0, -1),  // back face
            glm::vec3(1, 0, 0),   // right face
            glm::vec3(0, 0, 1),   // front face
            glm::vec3(-1, 0, 0),  // left face
            glm::vec3(0, -1, 0)   // bottom face
        };

        vector<glm::vec2> textureCoords
        {
            // Top face
           glm::vec2(0.0f, 0.0f),
           glm::vec2(1.0f, 0.0f),
           glm::vec2(1.0f, 1.0f),
           glm::vec2(0.0f, 1.0f),

           // Bottom face
           glm::vec2(0.0f, 0.0f),
           glm::vec2(1.0f, 0.0f),
           glm::vec2(1.0f, 1.0f),
           glm::vec2(0.0f, 1.0f),

           // Right face
           glm::vec2(0.0f, 1.0f),
           glm::vec2(1.0f, 0.0f),
           glm::vec2(1.0f, 1.0f),
           glm::vec2(0.0f, 0.0f),

           // Left face
           glm::vec2(0.0f, 0.0f),
           glm::vec2(1.0f, 0.0f),
           glm::vec2(1.0f, 1.0f),
           glm::vec2(0.0f, 1.0f),

           // Back face
           glm::vec2(0.0f, 0.0f),
           glm::vec2(1.0f, 0.0f),
           glm::vec2(1.0f, 1.0f),
           glm::vec2(0.0f, 1.0f),

           // Front face
           glm::vec2(0.0f, 0.0f),
           glm::vec2(1.0f, 0.0f),
           glm::vec2(1.0f, 1.0f),
           glm::vec2(0.0f, 1.0f),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,  // top face
            0, 2, 3,
            4, 5, 6,  // bottom face
            4, 6, 7,
            1, 5, 6,  // right face
            1, 6, 2,
            0, 4, 7,  // left face
            0, 7, 3,
            3, 2, 6,  // back face
            3, 6, 7,
            0, 1, 5,  // front face
            0, 5, 4
        };

        Mesh* mesh = new Mesh("box");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    //create the triangle
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0, 0.2f, 0.25f),   
            glm::vec3(0.8f, 0.2f, 0.25f),   
            glm::vec3(0.4f, 1, 0.25f)
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            glm::vec2(0.0f, 1.0f),   // top left
            glm::vec2(1.0f, 1.0f),   // top right
            glm::vec2(1.0f, 0.0f),   // bottom right
            glm::vec2(0.0f, 0.0f),     // bottom left
        };

        vector<unsigned int> indices =
        {
            0, 1, 2
        };

        Mesh* mesh = new Mesh("triangle");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }
    //create the bat
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0.35f, 1, 0.2f),   // top left back
            glm::vec3(0.45f, 1, 0.2f),    // top right back
            glm::vec3(0.45f, 0.2f, 0.2f),   // bottom right back
            glm::vec3(0.35f, 0.2f, 0.2f),  // bottom left back

            glm::vec3(0.35f, 1, 0.3f),    // top left front
            glm::vec3(0.45f, 1, 0.3f),     // top right front
            glm::vec3(0.45f, 0.2f, 0.3f),    // bottom right front
            glm::vec3(0.35f, 0.2f, 0.3f)    // bottom left front
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 0),   // top face
            glm::vec3(0, 0, -1),  // back face
            glm::vec3(1, 0, 0),   // right face
            glm::vec3(0, 0, 1),   // front face
            glm::vec3(-1, 0, 0),  // left face
            glm::vec3(0, -1, 0)   // bottom face
        };

        vector<glm::vec2> textureCoords
        {
            glm::vec2(0.0f, 1.0f),   // top left
            glm::vec2(1.0f, 1.0f),   // top right
            glm::vec2(1.0f, 0.0f),   // bottom right
            glm::vec2(0.0f, 0.0f),     // bottom left
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,  // top face
            0, 2, 3,
            4, 5, 6,  // bottom face
            4, 6, 7,
            1, 5, 6,  // right face
            1, 6, 2,
            0, 4, 7,  // left face
            0, 7, 3,
            3, 2, 6,  // back face
            3, 6, 7,
            0, 1, 5,  // front face
            0, 5, 4
        };

        Mesh* mesh = new Mesh("bat");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }
    //create the steag
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0.15f, 1.1, 0.28f),   // top left back
            glm::vec3(0.4f, 1.1, 0.28f),    // top right back
            glm::vec3(0.4f, 0.9f, 0.28f),   // bottom right back
            glm::vec3(0.15f, 0.9f, 0.28f),  // bottom left back

            glm::vec3(0.15f, 1.1f, 0.3f),    // top left front
            glm::vec3(0.4f, 1.1f, 0.3f),     // top right front
            glm::vec3(0.4f, 0.9f, 0.3f),    // bottom right front
            glm::vec3(0.15f, 0.9f, 0.3f)    // bottom left front
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 0),   // top face
            glm::vec3(0, 0, -1),  // back face
            glm::vec3(1, 0, 0),   // right face
            glm::vec3(0, 0, 1),   // front face
            glm::vec3(-1, 0, 0),  // left face
            glm::vec3(0, -1, 0)   // bottom face
        };

        vector<glm::vec2> textureCoords
        {
            // Top face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Bottom face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Right face
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),

            // Left face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Back face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Front face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
                    
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,  // top face
            0, 2, 3,
            4, 5, 6,  // bottom face
            4, 6, 7,
            1, 5, 6,  // right face
            1, 6, 2,
            0, 4, 7,  // left face
            0, 7, 3,
            3, 2, 6,  // back face
            3, 6, 7,
            0, 1, 5,  // front face
            0, 5, 4
        };

        Mesh* mesh = new Mesh("steag");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("TemaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    lightsPosition = glm::vec3(2, 0.1f, -3);
    lightsDirection = glm::vec3(0, -1, 0);
    Shininess = 30;
    Kd = 0.5;
    Ks = 0.5;
    cut_off[0] = 30;
    cut_off[1] = 30;

}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
}



void Tema3::Update(float deltaTimeSeconds)
{
    //water
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(-60));
        RenderSimpleMesh(meshes["water"], shaders["TemaShader"], modelMatrix, mapTextures["apa"], mapTextures["apa"],1);
        
    }
    //moon
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 3, -5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1));
        RenderSimpleMesh(meshes["sphere"], shaders["TemaShader"], modelMatrix, mapTextures["moon"], mapTextures["moon"],0);
    }
    //grass
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, -1, -3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(3));
        RenderSimpleMesh(meshes["sphere"], shaders["TemaShader"], modelMatrix, mapTextures["iarba"], mapTextures["iarba"],0);
    }
    //far
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.1f, -3));
        RenderSimpleMesh(meshes["cylinder"], shaders["TemaShader"], modelMatrix, mapTextures["wall"], mapTextures["wall"],0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 1.1f, -3));
        RenderSimpleMesh(meshes["cylinder"], shaders["TemaShader"], modelMatrix, mapTextures["wall"], mapTextures["wall"],0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 2.1f, -3));
        RenderSimpleMesh(meshes["cylinder"], shaders["TemaShader"], modelMatrix, mapTextures["white"], mapTextures["white"],0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 3.1f, -3));
        RenderSimpleMesh(meshes["cylinder"], shaders["TemaShader"], modelMatrix, mapTextures["wall"], mapTextures["wall"],0);
    }
    //barca
    static float boatRotation = 0.0f;
    /*boatRotation += 1.0f * deltaTimeSeconds;*/
    glm::vec3 boatRelativePosition = glm::vec3(0.0f, 0.0f, -3.0f);
    //barca 1
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["box"], shaders["TemaShader"], modelMatrix, mapTextures["wood"], mapTextures["wood"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["triangle"], shaders["TemaShader"], modelMatrix, mapTextures["panza"], mapTextures["panza"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["bat"], shaders["TemaShader"], modelMatrix, mapTextures["grey"], mapTextures["grey"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["steag"], shaders["TemaShader"], modelMatrix, mapTextures["steag"], mapTextures["steag"], 0);
    }

    //barca 2
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["box"], shaders["TemaShader"], modelMatrix, mapTextures["wood"], mapTextures["wood"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["triangle"], shaders["TemaShader"], modelMatrix, mapTextures["panza"], mapTextures["panza"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["bat"], shaders["TemaShader"], modelMatrix, mapTextures["grey"], mapTextures["grey"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["steag"], shaders["TemaShader"], modelMatrix, mapTextures["steag"], mapTextures["steag"], 0);
    }

    //barca 3
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["box"], shaders["TemaShader"], modelMatrix, mapTextures["wood"], mapTextures["wood"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["triangle"], shaders["TemaShader"], modelMatrix, mapTextures["panza"], mapTextures["panza"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["bat"], shaders["TemaShader"], modelMatrix, mapTextures["grey"], mapTextures["grey"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["steag"], shaders["TemaShader"], modelMatrix, mapTextures["steag"], mapTextures["steag"], 0);
    }

    //barca 4
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["box"], shaders["TemaShader"], modelMatrix, mapTextures["wood"], mapTextures["wood"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["triangle"], shaders["TemaShader"], modelMatrix, mapTextures["panza"], mapTextures["panza"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["bat"], shaders["TemaShader"], modelMatrix, mapTextures["grey"], mapTextures["grey"], 0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 0, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(boatRelativePosition.x, boatRelativePosition.y, boatRelativePosition.z));
        modelMatrix = glm::rotate(modelMatrix, boatRotation, glm::vec3(0.0f, 1.0f, 0.0f));
        RenderSimpleMesh(meshes["steag"], shaders["TemaShader"], modelMatrix, mapTextures["steag"], mapTextures["steag"], 0);
    }

}


void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2, float ctr)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need
    float timp_ramas = Engine::GetElapsedTime();
    int loc_timp = glGetUniformLocation(shader->program, "Timp_ramas");
    glUniform1f(loc_timp, timp_ramas);

    int loc_ctr = glGetUniformLocation(shader->program, "ctr");
    glUniform1f(loc_ctr, ctr);

    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_position, 2, glm::value_ptr(lightsPosition));

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3fv(light_direction, 2, glm::value_ptr(lightsDirection));

    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, Shininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, Kd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, Ks);

    int oc = glGetUniformLocation(shader->program, "unghi_cut_off");
    glUniform1fv(oc, 2, cut_off);





    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    if (texture2)
    {
        glActiveTexture(GL_TEXTURE1);

        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);

    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (int i = 0; i < size; i++) {
        data[i] = i;
    }
    // TODO(student): Generate and bind the new texture ID

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }

    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // modul de wrapping pe orizontala
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps

    glGenerateMipmap(GL_TEXTURE_2D);
    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }
}

void Tema3::OnKeyPress(int key, int mods)
{
}

void Tema3::OnKeyRelease(int key, int mods)
{
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}

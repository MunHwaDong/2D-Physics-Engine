#include "PhysicsEngine.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <fstream>
#include <string>
#include <chrono>
#include <thread>

GLsizei SCR_WIDTH = 1400;
GLsizei SCR_HEIGHT = 700;

GLint locPV;

//Matrix4f projection;
//Matrix4f view;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 PV;

Matrix4f model;

void FrameBufferResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void InitShader(unsigned int& shaderProgram)
{
    //Shaders Setting
    std::fstream vertex_shader_code;
    std::fstream fragment_shader_code;

    std::string v_shader_string;
    std::string f_shader_string;
    std::string tmp_string1;
    std::string tmp_string2;

    const char* v_shader_cstyle;
    const char* f_shader_cstyle;

    int success;
    char info[512];

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    vertex_shader_code.open("VertexShader.glsl");

    if (vertex_shader_code.is_open())
    {
        while (getline(vertex_shader_code, tmp_string1))
        {
            v_shader_string += (tmp_string1 + "\n");
        }
    }
    else
    {
        std::cout << "Vertex Shader is Closed" << std::endl;
        exit(1);
    }

    fragment_shader_code.open("FragmentShader.glsl");

    if (fragment_shader_code.is_open())
    {
        while (getline(fragment_shader_code, tmp_string2))
        {
            f_shader_string += (tmp_string2 + "\n");
        }
    }
    else
    {
        std::cout << "Fragment Shader is Closed" << std::endl;
        exit(1);
    }

    v_shader_cstyle = v_shader_string.c_str();
    f_shader_cstyle = f_shader_string.c_str();

    glShaderSource(vertex_shader, 1, &v_shader_cstyle, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info);
        std::cout << "Vertex Shader Compile Error : " << info << std::endl;
    }

    glShaderSource(fragment_shader, 1, &f_shader_cstyle, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info);
        std::cout << "Fragment Shader Compile Error : " << info << std::endl;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info);
        std::cout << "Shader Linking Error : " << info << std::endl;
        return;
    }

    locPV = glGetUniformLocation(shaderProgram, "locPVM");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    fragment_shader_code.close();
    vertex_shader_code.close();
}

void InitializeBuffer(unsigned int& VBO, unsigned int& VAO, vector3f* vertices, size_t vertexCount)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vector3f) * vertexCount, vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RenderObject(unsigned int VAO, size_t vertexCount)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void SetPVMatrix()
{
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -200.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);

    PV = projection * view;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            std::cout << "Escape key pressed" << std::endl;
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_W:
            std::cout << "삼각형 생성" << std::endl;
            // W 키를 눌렀을 때의 동작 구현
            break;
        case GLFW_KEY_A:
            std::cout << "A key pressed" << std::endl;
            // A 키를 눌렀을 때의 동작 구현
            break;
        }
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My 2D Physics Engine", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Fail to Create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Fail to Init GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, FrameBufferResize);

    unsigned int shaderProgram = 0;
    InitShader(shaderProgram);

    PhysicsEngine phyEngine;
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //Data 
    vector3f obj1InitPos(0, -0.5f, 0);
    Shape* shape1 = new Shape(3, 0.2f);
    RenderableObject* obj1 = new RenderableObject(35.0f, shape1);

    obj1->name = "obj1";
   
    vector3f obj2InitPos(0, 0.5f, 0);
    Shape* shape2 = new Shape(3, 0.2f);
    RenderableObject* obj2 = new RenderableObject(5.0f, shape2);

    obj2->name = "obbbbjjjj2";

    SetPVMatrix();
    //////////////////////////////////////////////////////////////////////////////////////////////////
    Matrix4f model = Utill::GetModelMatrix(obj1InitPos, vector3f(100.0f, 100.0f, 0), 0);

    model.Transform(obj1->pos);
    std::transform(obj1->shape->vertices,
                   obj1->shape->vertices + 3,
                   obj1->shape->vertices,
                   [&model](vector3f vertex) { model.Transform(vertex); });

    Matrix4f model = Utill::GetModelMatrix(obj2InitPos, vector3f(100.0f, 100.0f, 0), 0);
    model.Transform(obj2->pos);
    std::transform(obj2->shape->vertices,
        obj2->shape->vertices + 3,
        obj2->shape->vertices,
        [&model](vector3f vertex) { model.Transform(vertex); });

    phyEngine.AddObject(obj1);
    phyEngine.AddObject(obj2);
    //////////////////////////////////////////////////////////////////////////////////////////////////

    // OpenGL
    unsigned int VBO1, VAO1, VBO2, VAO2;
    size_t vertexCount = 3;

    InitializeBuffer(VBO1, VAO1, obj1->shape->vertices, vertexCount);
    InitializeBuffer(VBO2, VAO2, obj2->shape->vertices, vertexCount);

    glfwSetKeyCallback(window, KeyCallback);

    using clock = std::chrono::high_resolution_clock;
    using duration = std::chrono::duration<float>;
    std::chrono::duration<float> timeStep(0.02f);

    auto lastTime = clock::now();

    //Render Loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(locPV, 1, GL_FALSE, glm::value_ptr(PV));

        // Render obj1
        RenderObject(VAO1, vertexCount);

        // Render obj2
        RenderObject(VAO2, vertexCount);

        auto currentTime = clock::now();
        duration delTime = currentTime - lastTime;

        if (delTime >= timeStep)
        {
            phyEngine.Update(0.02f);
            lastTime = currentTime;

            std::this_thread::sleep_for(timeStep - delTime);
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vector3f) * vertexCount, obj1->shape->vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vector3f) * vertexCount, obj2->shape->vertices, GL_DYNAMIC_DRAW);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
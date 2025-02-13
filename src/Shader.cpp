#include <GL/glew.h>
#include "Shader.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.hpp"




int Shader::getUniformLocation(const std::string& name) {

    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    glCall(int location = glGetUniformLocation(m_rendererId, name.c_str()));

    if (location == -1) {
        std::cout << "Uniform doesn't exist" << std::endl;
        exit(0);
    }
    m_uniformLocationCache[name] = location;
    return location;
}

Shader::Shader(const std::string& filePath) : m_filePath(filePath), m_rendererId(0) {
    Shaders shaders = parseShader(filePath);
    m_rendererId = createShader(shaders.vertexShader, shaders.fragmentShader);
}


unsigned int Shader::compileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int compilationResult;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);

    if (!compilationResult) {
        int logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        char* msg = (char*)alloca(logLength * sizeof(char));
        glGetShaderInfoLog(id, logLength, &logLength, msg);
        std::cout << "[ERROR]" << msg << std::endl;
        glDeleteShader(id);
        return 0;
    }


    return id;
}

Shader::~Shader() {
    glCall(glDeleteProgram(m_rendererId))
}

void Shader::bind() const {
    glCall(glUseProgram(m_rendererId));
}

void Shader::unBind() const {
    glCall(glUseProgram(0));

}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}




unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int verShad = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fraShad = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, verShad);
    glAttachShader(program, fraShad);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(verShad);
    glDeleteShader(fraShad);

    return program;
}



Shaders Shader::parseShader(const std::string& filePath) {


    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    std::ifstream file(filePath);
    if (!file.is_open())
        std::cout << "unable to open file" << std::endl;
    std::string line;
    while (getline(file, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;

            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    std::cout << ss[0].str() << std::endl;
    std::cout << ss[1].str() << std::endl;

    return { ss[0].str(), ss[1].str() };
}


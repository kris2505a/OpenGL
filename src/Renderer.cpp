#include "Renderer.hpp"
#include <iostream>



void u_glClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool u_glLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[ERrOr] : " << error << " - " << function << " - " << file << " -> Line : " << line << std::endl;
        return false;
    }
    return true;
}


void Renderer::draw(const VertexArray& vArray, const IndexBuffer& iBuffer, const Shader& shader) {
    shader.bind();
    vArray.bind();
    iBuffer.bind();
    glCall(glDrawElements(GL_TRIANGLES, iBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}
#pragma once

#include <GL/glew.h>
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"



#define ASSERT(Y) if(!(Y)) __debugbreak();
#define glCall(x) u_glClearErrors(); \
                    x; \
                    ASSERT(u_glLogCall(#x, __FILE__, __LINE__))


void u_glClearErrors(); 
bool u_glLogCall(const char* function, const char* file, int line);


class Renderer {
public:
    void draw(const VertexArray& vArray, const IndexBuffer& iBuffer, const Shader& shader);
    void clear() const ;
};
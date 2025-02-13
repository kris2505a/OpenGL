#pragma once
#include "VertexBuffer.hpp"

class VertexBufferLayout;

class VertexArray {

private:
	unsigned int m_rendererId;

public:

	VertexArray();
	~VertexArray();

	void bind() const;
	void unBind() const;

	void addBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& vBufferLayout);
};


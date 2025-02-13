#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"


VertexArray::VertexArray() {
	glCall(glGenVertexArrays(1, &m_rendererId));
}


VertexArray::~VertexArray() {
	glCall(glDeleteVertexArrays(1, &m_rendererId));
}


void VertexArray::bind() const {
	glCall(glBindVertexArray(m_rendererId));
}

void VertexArray::unBind() const {
	glCall(glBindVertexArray(0));
}


void VertexArray::addBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& vBufferLayout) {
	bind();
	vBuffer.bind();
	const auto& elements = vBufferLayout.getElements();

	unsigned int offset = 0;

	for (unsigned int i{ 0 }; i < elements.size(); i++) {

		const auto& element = elements[i];
		glCall(glEnableVertexAttribArray(i));
		glCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vBufferLayout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSize(element.type);
	}

}

#pragma once

class IndexBuffer {
	
private:
	unsigned int m_rendererId;
	unsigned int m_count;

public:

	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void bind() const;
	void unBind() const;
	inline unsigned int getCount() const { return m_count; }
};

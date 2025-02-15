#pragma once
#include "Renderer.hpp"


class Texture {
private:
	unsigned int m_rendererId;
	std::string m_path;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp;

public:
	Texture(std::string path);
	~Texture();
	void bind(unsigned int slot = 0) const;
	void unBind() const;

	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
};


#pragma once
#include <string>
#include <unordered_map>


struct Shaders {
	std::string vertexShader;
	std::string fragmentShader;
};


class Shader {

private:
	
	unsigned int m_rendererId;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;

	int getUniformLocation(const std::string& name);
	unsigned int compileShader(const std::string& source, unsigned int type);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	Shaders parseShader(const std::string& filePath);

public:
	
	Shader(const std::string& filePath);
	~Shader();
	void bind() const;
	void unBind() const;

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, int value);
};
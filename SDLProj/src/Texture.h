#pragma once
#include <string>
#include <unordered_map>

struct SDL_Surface;

class Texture
{
private:
	static unsigned int s_CurrentlyBound;
	static std::unordered_map<std::string, Texture> s_TextureCache;

	unsigned int	m_RendererID;
	std::string		m_Filepath;
	SDL_Surface		*m_LocalBuffer;
public:
	Texture(const std::string& Filepath);
	Texture(const Texture& Other);
	Texture& operator=(const Texture& Other);

	~Texture();

	void Bind(unsigned int Slot = 0) const;
	void Unbind() const;

	int GetWidth() const;
	int GetHeight() const;
private:

	//static const Texture& GetTextureFromCache(const std::string& Filepath);
};


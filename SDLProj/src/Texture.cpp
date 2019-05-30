#include "Texture.h"
#include "Renderer.h"
#include <iostream>

std::unordered_map<std::string, Texture> Texture::s_TextureCache;
unsigned int Texture::s_CurrentlyBound = 0;

Texture::Texture(const std::string& Filepath) :
	m_RendererID(0),
	m_Filepath(Filepath),
	m_LocalBuffer(nullptr)
{
	auto FindIterator = s_TextureCache.find(Filepath);
	if (FindIterator != s_TextureCache.end())
	{
		*this = FindIterator->second;
		return;
	}

	m_LocalBuffer = IMG_Load(Filepath.c_str());
	if (!m_LocalBuffer)
	{
		const char *Error = IMG_GetError();
		std::cerr << Error << "\n";
		SDL_assert(false);
	}
	glGenTextures(1, &m_RendererID);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_LocalBuffer->w, m_LocalBuffer->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer->pixels);
	Unbind();
	s_TextureCache.emplace(Filepath, *this);
	std::cerr << "A new texture loaded: " << Filepath << "\n";
}

Texture::Texture(const Texture & Other) :
	m_RendererID(0),
	m_LocalBuffer(nullptr)
{
	*this = Other;
}

Texture& Texture::operator=(const Texture & Other)
{
	if (m_LocalBuffer)
		SDL_FreeSurface(m_LocalBuffer);
	m_RendererID = Other.m_RendererID;
	m_Filepath = Other.m_Filepath;
	m_LocalBuffer = Other.m_LocalBuffer;
	++m_LocalBuffer->refcount;
	return *this;
}


Texture::~Texture()
{
	SDL_FreeSurface(m_LocalBuffer);
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int Slot) const
{
	//if (m_RendererID == s_CurrentlyBound)
	//	return;
	glActiveTexture(GL_TEXTURE0 + Slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	s_CurrentlyBound = m_RendererID;
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE0, 0);
	s_CurrentlyBound = 0;
}

int Texture::GetWidth() const
{
	return m_LocalBuffer->w;
}

int Texture::GetHeight() const
{
	return m_LocalBuffer->h;
}

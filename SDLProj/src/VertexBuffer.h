#pragma once
#include <vector>

class VertexBuffer
{
private:
	static unsigned int s_CurrentlyBound;

	unsigned int m_RendererID;
public:
	VertexBuffer(const void *Data, size_t Size);

	template<typename T>
	VertexBuffer(const std::vector<T>& Data);

	~VertexBuffer();

	void Bind(void) const ;
	void Unbind(void) const ;
};

template<typename T>
inline VertexBuffer::VertexBuffer(const std::vector<T>& Data) :
	VertexBuffer(Data.data(), Data.size() * sizeof(T))
{}

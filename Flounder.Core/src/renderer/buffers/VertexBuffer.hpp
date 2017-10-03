﻿#pragma once

#include "Buffer.hpp"

namespace Flounder
{
	class VertexBuffer :
		public Buffer
	{
	private:
		uint32_t m_vertexCount;
	public:
		VertexBuffer();

		~VertexBuffer();

		void Create(const uint64_t &elementSize, const size_t &vertexCount, void *newData);

		void Cleanup();

		uint32_t GetVertexCount() const { return m_vertexCount; }
	};
}

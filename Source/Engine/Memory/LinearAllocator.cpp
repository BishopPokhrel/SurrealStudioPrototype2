#include "LinearAllocator.h"

#include <memory>
#include <cassert>

namespace SurrealStudio::Memory {

	static size_t AlignForward(size_t address, size_t alignment) noexcept
	{
		size_t misalignment = address % alignment;
		if (misalignment == 0)
			return address;

		return address + (alignment - misalignment);
	}

	LinearAllocator::LinearAllocator(size_t size) noexcept
	{
		m_Start = (char*)malloc(size);
		m_Size = size;
		assert(m_Start && "Memory is valid!");
		m_Offset = 0;
	}

	LinearAllocator::~LinearAllocator() noexcept
	{
		free(m_Start);
	}

	void* LinearAllocator::Allocate(size_t size, size_t alignment) noexcept
	{
		if (alignment == 0)
			return nullptr;

		char* currentAddress = m_Start + m_Offset;
		void* alignedAddress = (void*)AlignForward((size_t)currentAddress, alignment);
		size_t padding = (size_t)alignedAddress - (size_t)currentAddress;
		size_t newOffset = m_Offset + padding + size;

		if (newOffset > m_Size)
			assert(false && "Allocator overflow!");

		m_Offset = newOffset;
		return alignedAddress;
	}

	void LinearAllocator::Reset() noexcept { m_Offset = 0; }
}
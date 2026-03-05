#include "StackAllocator.h"

#include <cassert>

namespace SurrealStudio::Memory {

	StackAllocator::StackAllocator(size_t size) noexcept
	{
		m_Offset = 0;
		m_Size = size;
		m_Start = (char*)operator new(size);
	}
	
	StackAllocator::~StackAllocator() noexcept
	{
		operator delete(m_Start);
		StackAllocator_Reset();
	}

	size_t StackAllocator::StackAllocator_AlignForward(size_t address, size_t alignment) noexcept
	{
		size_t misalignment = address % alignment;

		if (misalignment == 0)
			return address;
		else
			return address + (alignment - misalignment);
	}

	void* StackAllocator::StackAllocator_Allocate(size_t size, size_t alignment) noexcept
	{
		if (alignment == 0)
			alignment = alignof(std::max_align_t);

		size_t currentAddress = (size_t)m_Start + m_Offset;
		size_t alignedAddress = StackAllocator_AlignForward(currentAddress, alignment);
		size_t padding = alignedAddress - currentAddress;
		size_t requiredSpace = padding + sizeof(StackAllocationHeader) + size;

		if (m_Offset + requiredSpace > m_Size)
			assert(false && "Stack Overflow!");

		StackAllocationHeader* header = (StackAllocationHeader*)((char*)m_Start + m_Offset + padding);

		header->padding = (uint8_t)padding;
		m_Offset += requiredSpace;

		return (void*)((char*)header + sizeof(StackAllocationHeader));
	}

	void StackAllocator::StackAllocator_Free(void* ptr) noexcept
	{
		if (!ptr) return;

		StackAllocationHeader* header = (StackAllocationHeader*)((char*)ptr - sizeof(StackAllocationHeader));
		m_Offset = (size_t)((char*)ptr - m_Start) - sizeof(StackAllocationHeader) - header->padding;
	}
}
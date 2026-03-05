#pragma once

#include <iostream> // for uint8_t

namespace SurrealStudio::Memory {

	struct StackAllocationHeader
	{
		uint8_t padding;
	};

	class StackAllocator
	{
	public:

		StackAllocator(size_t size) noexcept;
		~StackAllocator() noexcept;

		size_t StackAllocator_AlignForward(size_t address, size_t alignment) noexcept;
		void* StackAllocator_Allocate(size_t size, size_t alignment) noexcept;
		
		void StackAllocator_Free(void* ptr) noexcept;
		void StackAllocator_Reset() noexcept { m_Offset = 0; }

	private:

		char* m_Start;
		size_t m_Size;
		size_t m_Offset;
	};
}
#pragma once

namespace SurrealStudio::Memory {

	struct PoolBlock
	{
		PoolBlock* next;
	};

	class PoolAllocator
	{
	public:
		PoolAllocator(size_t blockSize, size_t blockCount) noexcept;
		~PoolAllocator() noexcept;

		void* PoolAllocator_Allocate() noexcept;
		void PoolAllocate_Free(void* ptr) noexcept;

	private:

		char* m_Start;
		PoolBlock* m_FreeListHead;

		size_t m_BlockSize;
		size_t m_BlockCount;
	};
}
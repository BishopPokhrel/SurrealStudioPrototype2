#include "PoolAllocator.h"
#include <memory>

namespace SurrealStudio::Memory {

	PoolAllocator::PoolAllocator(size_t blockSize, size_t blockCount) noexcept
	{
		m_Start = (char*)operator new(blockSize * blockCount);
		m_BlockSize = blockSize;
		m_BlockCount = blockCount;

		m_FreeListHead = (PoolBlock*)m_Start;

		PoolBlock* current = m_FreeListHead;

		for (size_t i = 0; i < blockCount - 1; i++)
		{
			PoolBlock* next = (PoolBlock*)((char*)current + blockSize);

			current->next = next;
			current = next;
		}

		current->next = nullptr;
	}

	PoolAllocator::~PoolAllocator() noexcept
	{
		operator delete(m_Start);
	}

	void* PoolAllocator::PoolAllocator_Allocate() noexcept
	{
		if (!m_FreeListHead)
			return nullptr;

		PoolBlock* freeBlock = m_FreeListHead;
		m_FreeListHead = freeBlock->next;
		return freeBlock;
	}

	void PoolAllocator::PoolAllocate_Free(void* ptr) noexcept
	{
		if (!ptr) return;

		PoolBlock* block = (PoolBlock*)ptr;
		block->next = m_FreeListHead;

		m_FreeListHead = block;
	}
}
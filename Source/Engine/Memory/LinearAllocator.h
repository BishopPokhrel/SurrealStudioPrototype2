#pragma once

namespace SurrealStudio::Memory {

	class LinearAllocator
	{
	public:

		LinearAllocator(size_t size) noexcept;
		~LinearAllocator() noexcept;

		void* Allocate(size_t size, size_t alignment) noexcept;
		void Reset() noexcept;

	private:

		char* m_Start = nullptr;
		size_t m_Size = 0;
		size_t m_Offset = 0;
	};
}
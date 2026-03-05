#pragma once

namespace SSCppSTLReImp
{
	template<typename T>
	class Vector
	{
	public:

		void PushBack(const T& value) noexcept;
		// TODO: Add more later;

	private:

		T* m_Data;
		size_t m_Size;
		size_t m_Capacity;
	};
}
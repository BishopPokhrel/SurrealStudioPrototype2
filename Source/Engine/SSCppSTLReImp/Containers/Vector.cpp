#include "Vector.h"

namespace SSCppSTLReImp
{
	template<typename T>
	void Vector<T>::PushBack(const T& value) noexcept
	{
		if (m_Size == m_Capacity)
		{
			m_Capacity *= m_Size * 2;
			// TODO: Finish this
			// WIP.
		}
	}
}
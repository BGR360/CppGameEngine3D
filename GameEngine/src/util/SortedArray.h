#ifndef BENGINE_SORTED_ARRAY_H
#define BENGINE_SORTED_ARRAY_H

#include <Engine.h>

#include <vector>

#include <util/Types.h>

using std::vector;

namespace Util
{
	template<typename T>
	class ENGINE_DLL_EXPORT_IMPORT SortedArray : public vector<T>
	{
		bool m_bIsSorted;

	public:
		SortedArray() {}
		virtual ~SortedArray() {}

		class iterator
		{
			uint m_index;

		public:
			virtual ~iterator() {}

			inline iterator& operator++();
			inline iterator& operator++(int);
			inline iterator& operator--();
			inline iterator& operator--(int);

			inline T& operator->();

		private:
			iterator(uint index) : m_index(index) {}
		};

		iterator begin();
		iterator end();

		void sort();
		iterator insert(const T& item);
		iterator find(const T& item);
		void swap(uint indexA, uint indexB);

	};
}

#endif //BENGINE_SORTED_ARRAY_H
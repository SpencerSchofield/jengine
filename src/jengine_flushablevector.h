#ifndef JENGINE_FLUSHABLEVECTOR_H
#define JENGINE_FLUSHABLEVECTOR_H

#include <vector>
#include "jengine_ret.h"
#include <stdexcept>

namespace Jengine {

	template <typename T>
	class FlushableVector
	{
	public:
		FlushableVector();

		void push(
				T value)
		{
			if (this->used < this->vector.size()) {
				this->vector[this->used] = {value};
			} else {
				this->vector.push_back({value});
			}
			this->used++;
		}

		void erase(
				unsigned long index)
		{
			this->used--;
			Ret<T> temp = {this->vector[index].data, false};
			this->vector[index] = this->vector[used];
			this->vector[used] = temp;
		}

		void flush()
		{
			this->vector.erase(this->vector.begin() + this->used, this->vector.end());
		}

		unsigned long size() const
		{
			return this->used;
		}

		T& operator[](
				unsigned long index)
		{
			if (index > this->used) {
				throw std::out_of_range("index");
			}
			return this->vector[index].data;
		}

	private:
		std::vector<Ret<T>> vector;
		unsigned long used {0};
	};


} // namespace Jengine

#endif // JENGINE_FLUSHABLEVECTOR_H

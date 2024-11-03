#pragma once
#include <cassert>
#include <new>

#include "SSEngineDefault/SSNativeKeywords.h"
#include "SSUtilityContainer.h"

namespace SS
{
	template<typename T>
	class PooledList {

	private:
		T* _data = nullptr;
		uint32 _capacity = 0;
		uint32 _size = 0;

	public:
		PooledList(uint32 capacity = 0);
		PooledList(const PooledList<T>& origin);
		PooledList(PooledList<T>&& origin);
		~PooledList();

		void PushBack(const T& newData);
		void PushBack(T&& newData);
		void RemoveAt(int32 Idx);
		void RemoveAtAndFillLast(int32 Idx);


		void Resize(uint32 newSize);
		void Clear();
		void Reserve(uint32 newCapacity);


		FORCEINLINE bool IsFull() const { return _size == _capacity; }
		bool IsValidIndex(int32 idx) const;

		FORCEINLINE uint32 GetSize() const { return _size; }
		FORCEINLINE uint32 GetCapacity() const { return _capacity; }

		FORCEINLINE T* GetData() const { return _data; }
		FORCEINLINE T& operator[](const uint32 idx)  const;
		PooledList<T>& operator=(PooledList<T>&& origin);

	public:
		class iterator {
			friend class PooledList<T>;
		private:
			uint32 _idx;
			const PooledList<T>& _list;

		public:
			iterator& operator++() {
				_idx++;
				return *this;
			}
			iterator& operator--() {
				_idx--;
				return *this;
			}
			bool operator==(const iterator rhs) const { return _idx == rhs._idx; }
			bool operator!=(const iterator rhs) const { return _idx != rhs._idx; }
			T& operator*() { return _list._data[_idx]; }

		private:
			iterator(uint32 idx, PooledList<T>& list) : _idx(idx), _list(list) { }
		};
		FORCEINLINE iterator begin() { return iterator(0, *this); }
		FORCEINLINE iterator end() { return iterator(_size, *this); }


		class const_iterator {
			friend class PooledList<T>;
		private:
			uint32 _idx;
			const PooledList<T>* _list;

		public:
			const_iterator& operator++() {
				_idx++;
				return *this;
			}
			const_iterator& operator--() {
				_idx--;
				return *this;
			}
			bool operator==(const const_iterator rhs) const { return _idx == rhs._idx; }
			bool operator!=(const const_iterator rhs) const { return _idx != rhs._idx; }
			const T& operator*() const { return _list->_data[_idx]; }

		private:
			const_iterator(uint32 idx, const PooledList<T>* list) : _idx(idx), _list(list) { }
		};
		FORCEINLINE const_iterator begin() const { return const_iterator(0, this); }
		FORCEINLINE const_iterator end() const { return const_iterator(_size, this); }
	};


	template <typename T>
	PooledList<T>::PooledList(uint32 capacity)
	{
		_capacity = capacity;
		_size = 0;
		_data = nullptr;
		if (capacity > 0) {
			_capacity = capacity;
			_data = (T*)DBG_MALLOC(sizeof(T) * _capacity);
		}
	}

	template <typename T>
	PooledList<T>::PooledList(const PooledList<T>& origin)
	{
		_size = origin._size;
		_capacity = origin._capacity;
		_data = (T*)DBG_MALLOC(sizeof(T) * _capacity);

		for(uint32 i=0;i < _size;i++)
		{
			new(_data + i) T(origin[i]);
		}
	}

	template <typename T>
	PooledList<T>::PooledList(PooledList<T>&& origin)
	{
		_size = origin._size;
		_capacity = origin._capacity;
		_data = origin._data;
		origin._data = nullptr;
		origin._size = 0;
		origin._capacity = 0;
	}

	template <typename T>
	PooledList<T>::~PooledList()
	{
		for (uint32 i = 0; i < _size; i++)
		{
			_data[i].~T();
		}
		free(_data);
	}

	template <typename T>
	void PooledList<T>::PushBack(const T& newData)
	{
		if (_size >= _capacity)
		{
			Reserve(GetCapacity() * 2);
		}
		new(_data + _size) T(newData);
		_size++;
	}

	template <typename T>
	void PooledList<T>::PushBack(T&& newData)
	{
		if (_size >= _capacity)
		{
			Reserve((GetCapacity() + 1) * 2);
		}
		new(_data + _size) T(SS::forward<T>(newData));
		_size++;
	}

	template <typename T>
	void PooledList<T>::RemoveAt(int32 Idx)
	{
		if(Idx >= _size)
		{
			SS_INTEERUPT();
			return;
		}

		T* dataToRemovePtr = _data + Idx;
		dataToRemovePtr->~T();
		int32 sizeToMove = _size - Idx - 1;
		memmove(dataToRemovePtr, dataToRemovePtr + 1, sizeToMove);
		_size--;
	}

	template <typename T>
	void PooledList<T>::RemoveAtAndFillLast(int32 Idx)
	{
		if (Idx >= _size)
		{
			SS_INTEERUPT();
			return;
		}

		T* dataToRemove = _data + Idx;
		dataToRemove->~T();

		if(_size == Idx + 1)
		{
			_size--;
			return;
		}

		T* lastData = _data + (_size - 1);
		memcpy(dataToRemove, lastData, sizeof(T));
		_size--;
	}

	template <typename T>
	void PooledList<T>::Resize(uint32 newSize)
	{
		assert(newSize <= _capacity);

		for (uint32 i = _size; i < newSize; i++)
			new(_data + i) T();

		for (uint32 i = newSize; i < _size; i++)
			_data[i].~T();

		_size = newSize;
	}

	template <typename T>
	void PooledList<T>::Clear()
	{
		for (uint32 i = 0; i < _size; i++) {
			_data[i].~T();
		}
		_size = 0;
	}

	template <typename T>
	void PooledList<T>::Reserve(uint32 newCapacity)
	{
		if (newCapacity < _capacity)
		{
			return;
		}

		T* newData = (T*)malloc(sizeof(T) * newCapacity);
		memcpy(newData, _data, sizeof(T) * _capacity);
		free(_data);
		_data = newData;
		_capacity = newCapacity;
	}

	template <typename T>
	bool PooledList<T>::IsValidIndex(int32 idx) const
	{
		return 0 <= idx && idx < _size;
	}

	template <typename T>
	T& PooledList<T>::operator[](const uint32 idx) const
	{
		if(idx >= _size)
		{
			SS_INTEERUPT();
		}
		return _data[idx];
	}

	template<typename T>
	PooledList<T>& PooledList<T>::operator=(PooledList<T>&& origin)
	{
		for(int32 i=0;i<_size;i++)
		{
			_data[i].~T();
		}
		free(_data);
		_size = origin._size;
		_capacity = origin._capacity;

		_data = origin._data;
		origin._data = nullptr;
		origin._size = 0;
		origin._capacity = 0;

		return *this;
	}


	// ���� operator= �����
	// TArrayó�� movetemp ����� -> r-value "���� operator overloading" �����
	// TArrayó�� removeatswap �����

}

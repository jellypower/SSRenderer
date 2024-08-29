#pragma once
#include <new>

#include "SSEngineDefault/SSNativeKeywords.h"
#include "SSEngineDefault/SSDebugLogger.h"


namespace SS {
	template<typename T> class PooledLinkedList;

	template<typename T>
	class PooledLinkedListNode {
		friend class PooledLinkedList<T>;
	private:
		PooledLinkedListNode<T>* _prev;
		PooledLinkedListNode<T>* _next;
		T _data;

	public:
		PooledLinkedListNode();
		PooledLinkedListNode(const T& data);
		PooledLinkedListNode(T&& data);

		FORCEINLINE T GetDataValue() { return _data; }
		FORCEINLINE T& GetDataReference() { return _data; }
		FORCEINLINE T* GetDataPtr() { return &_data; }
		FORCEINLINE PooledLinkedListNode<T>* GetPrev() { return _prev; }
		FORCEINLINE PooledLinkedListNode<T>* GetNext() { return _next; }
	};
#pragma region PooledLinkedListNode implementation
	template<typename T>
	PooledLinkedListNode<T>::PooledLinkedListNode(const T& data)
	{
		_data = data;
		_prev = nullptr;
		_next = nullptr;
	}

	template<typename T>
	PooledLinkedListNode<T>::PooledLinkedListNode(T&& data)
	{
		_data = data;
		_prev = nullptr;
		_next = nullptr;

	}

	template<typename T>
	PooledLinkedListNode<T>::PooledLinkedListNode()
	{
		_prev = nullptr;
		_next = nullptr;
	}
#pragma endregion


	template<typename T>
	class PooledLinkedList {
		class iterator {
			friend class PooledLinkedList<T>;
		private:
			PooledLinkedListNode<T>* _ptr;

		public:
			iterator& operator++() {
				_ptr = _ptr->GetNext();
				return *this;
			}
			iterator& operator--() {
				_ptr = _ptr->GetPrev();
				return *this;
			}
			bool operator==(const iterator& rhs) const { return _ptr == rhs._ptr; }
			bool operator!=(const iterator& rhs) const { return _ptr != rhs._ptr; }
			T& operator*() { return _ptr->GetDataReference(); }
			T* operator->() { return _ptr->GetDataPtr(); }
		private:
			iterator(PooledLinkedListNode<T>* ptr) { _ptr = ptr; }
		};

	private:
		uint32 _size;
		uint32 _capacity;
		uint32 _usableAddressTopIdx;
		PooledLinkedListNode<T>** _usableAddressStack;
		PooledLinkedListNode<T>* _pool;
		PooledLinkedListNode<T> _head;
		PooledLinkedListNode<T> _tail;

	public:
		PooledLinkedList(uint32 _capacity);
		~PooledLinkedList();

		void PushBack(const T& item);
		void PushBack(T&& item);
		void PopBack();

		void PushFront(const T& item);
		void PushFront(T&& item);
		void PopFront();

		T& FindAt(uint32 index);
		iterator FindIteratorAt(uint32 index) {
			iterator iter = begin();
			for (uint32 i = 0; i < index; i++)
				++iter;

			return iter;
		}

		void InsertBack(iterator iter, const T& item);
		void InsertBack(iterator iter, T&& item);

		void InsertFront(iterator iter, const T& item);
		void InsertFront(iterator iter, T&& item);

		iterator Erase(iterator iter) {
			PooledLinkedListNode<T>* nodeToDelete = iter._ptr;
			iterator iterToReturn = iterator(nodeToDelete->_prev);

			nodeToDelete->_prev->_next = nodeToDelete->_next;
			nodeToDelete->_next->_prev = nodeToDelete->_prev;
			nodeToDelete->_next = nullptr;
			nodeToDelete->_prev = nullptr;

			nodeToDelete->_data.~T();
			ReleaseUsableAddress(nodeToDelete);
			_size--;

			return iterToReturn;
		}
		void Clear();

		bool IsEmpty();

		FORCEINLINE iterator begin() { return iterator(_head._next); }
		FORCEINLINE iterator end() { return iterator(&_tail); }

	private:
		PooledLinkedListNode<T>* GetNewUsableAddress();
		void ReleaseUsableAddress(PooledLinkedListNode<T>* addrToRelease);
	};

#pragma region PooledLinkedList implementation
	template<typename T>
	PooledLinkedList<T>::PooledLinkedList(uint32 capacity)
	{
		_capacity = capacity;
		_size = 0;
		_usableAddressTopIdx = 0;
		_pool = (PooledLinkedListNode<T>*)DBG_MALLOC(sizeof(PooledLinkedListNode<T>) * _capacity); // TODO: 나중에 malloc으로 바꿔주기
		_usableAddressStack = DBG_NEW PooledLinkedListNode<T>*[_capacity];

		for (uint32 i = 0; i < _capacity; i++)
			_usableAddressStack[i] = (_pool + i);

		_head._next = &_tail;
		_tail._prev = &_head;
	}

	template<typename T>
	PooledLinkedList<T>::~PooledLinkedList()
	{
		Clear();
		free(_pool);
		delete _usableAddressStack;
	}

	template<typename T>
	void PooledLinkedList<T>::PushBack(const T& item)
	{
		if (_size >= _capacity) {
			assert(false);
			return;
		}

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_next = &_tail;
		newAddr->_prev = _tail._prev;

		_tail._prev->_next = newAddr;
		_tail._prev = newAddr;

		_size++;
	}

	template<typename T>
	void PooledLinkedList<T>::PushBack(T&& item)
	{
		if (_size >= _capacity) {
			assert(false);
			return;
		}

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_next = &_tail;
		newAddr->_prev = _tail._prev;

		_tail._prev->_next = newAddr;
		_tail._prev = newAddr;

		_size++;
	}


	template<typename T>
	void PooledLinkedList<T>::PopBack()
	{
		if (_size <= 0) {
			assert(false);
			return;
		}

		PooledLinkedListNode<T>* nodeToDelete = _tail._prev;

		nodeToDelete->_prev->_next = nodeToDelete->_next;
		nodeToDelete->_next->_prev = nodeToDelete->_prev;
		nodeToDelete->_prev = nullptr;
		nodeToDelete->_next = nullptr;

		nodeToDelete->_data.~T();
		ReleaseUsableAddress(nodeToDelete);
		_size--;
	}

	template<typename T>
	void PooledLinkedList<T>::PushFront(const T& item)
	{
		if (_size >= _capacity) {
			assert(false);
			return;
		}

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_prev = &_head;
		newAddr->_next = _head._next;

		_head._next->_prev = newAddr;
		_head._next = newAddr;

		_size++;
	}

	template<typename T>
	void PooledLinkedList<T>::PushFront(T&& item)
	{
		if (_size >= _capacity) {
			assert(false);
			return;
		}

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_prev = &_head;
		newAddr->_next = _head._next;

		_head._next->_prev = newAddr;
		_head._next = newAddr;

		_size++;
	}

	template<typename T>
	void PooledLinkedList<T>::PopFront()
	{
		if (_size <= 0) {
			assert(false);
			return;
		}

		PooledLinkedListNode<T>* nodeToDelete = _head._next;

		nodeToDelete->_prev->_next = nodeToDelete->_next;
		nodeToDelete->_next->_prev = nodeToDelete->_prev;
		nodeToDelete->_prev = nullptr;
		nodeToDelete->_next = nullptr;

		nodeToDelete->_data.~T();
		ReleaseUsableAddress(nodeToDelete);
		_size--;
	}

	template<typename T>
	T& PooledLinkedList<T>::FindAt(uint32 index) {
		PooledLinkedList<T>::iterator iter = begin();
		for (uint32 i = 0; i < index; i++)
			++iter;

		return (*iter);
	}



	template<typename T>
	void PooledLinkedList<T>::InsertBack(iterator iter, const T& item) {
		PooledLinkedListNode<T>* insertStartNode = iter._ptr;

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_prev = insertStartNode;
		newAddr->_next = insertStartNode->_next;

		insertStartNode->_next->_prev = newAddr;
		insertStartNode->_next = newAddr;

		_size++;
	}

	template<typename T>
	void PooledLinkedList<T>::InsertBack(iterator iter, T&& item) {
		PooledLinkedListNode<T>* insertStartNode = iter._ptr;

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_prev = insertStartNode;
		newAddr->_next = insertStartNode->_next;

		insertStartNode->_next->_prev = newAddr;
		insertStartNode->_next = newAddr;

		_size++;
	}

	template<typename T>
	void PooledLinkedList<T>::InsertFront(iterator iter, const T& item) {
		PooledLinkedListNode<T>* insertStartNode = iter._ptr;

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_next = insertStartNode;
		newAddr->_prev = insertStartNode->_prev;

		insertStartNode->_prev->_next = newAddr;
		insertStartNode->_prev = newAddr;

		_size++;
	}

	template<typename T>
	void PooledLinkedList<T>::InsertFront(iterator iter, T&& item) {
		PooledLinkedListNode<T>* insertStartNode = iter._ptr;

		PooledLinkedListNode<T>* newAddr = GetNewUsableAddress();
		new(newAddr) PooledLinkedListNode<T>(item);
		newAddr->_next = insertStartNode;
		newAddr->_prev = insertStartNode->_prev;

		insertStartNode->_prev->_next = newAddr;
		insertStartNode->_prev = newAddr;

		_size++;
	}

	template<typename T>
	void SS::PooledLinkedList<T>::Clear()
	{
		while (!IsEmpty()) {
			PopBack();
		}
	}

	template<typename T>
	inline bool PooledLinkedList<T>::IsEmpty()
	{
		return _size <= 0;
	}

	template<typename T>
	PooledLinkedListNode<T>* PooledLinkedList<T>::GetNewUsableAddress()
	{
		return _usableAddressStack[_usableAddressTopIdx++];
	}

	template<typename T>
	void PooledLinkedList<T>::ReleaseUsableAddress(PooledLinkedListNode<T>* addrToRelease)
	{
		_usableAddressStack[--_usableAddressTopIdx] = addrToRelease;
	}
#pragma endregion
}
#pragma once
#include "SSEngineDefault/SSEngineDefault.h"
#include "SSEngineDefault/SSContainer/SSUtilityContainer.h"
#include "SSEngineDefault/SSContainer/PooledList.h"
#include "BasicHashFunctionCollection.h"

namespace SS
{
	template<typename KeyType, typename ValueType, uint32 HASHMAP_CAPACITY>
	class HashMap
	{
		template<typename HMNKeyType, typename HMNValueType>
		class HashMapBucket
		{
		public:
			SS::pair<HMNKeyType, HMNValueType> _pair;
			HashMapBucket* _next = nullptr;

		public:
			HashMapBucket(const HMNKeyType& Key, const HMNValueType& Value) :
				_pair(Key, Value), _next(nullptr)
			{

			}

			HashMapBucket(HMNKeyType&& Key, HMNValueType&& Value) :
				_pair(Key, Value), _next(nullptr)
			{
					
			}
		};
		typedef HashMapBucket<KeyType, ValueType> HashMapBucket_INL;

		template<typename HMNHKeyType, typename HMNHValueType>
		class HashMapBucketHead
		{
		public:
			HashMapBucketHead(int32 inIdxInArray, int32 inHashValue) :
				_idxInArray(inIdxInArray), _hashValue(inHashValue)
			{ }

			HashMapBucket_INL* _next = nullptr;
			int32 _idxInArray = INVALID_IDX;
			int32 _hashValue = INVALID_IDX;
		};


		typedef HashMapBucketHead<KeyType, ValueType> HashMapBucketHead_INL;


	private:
		SS::PooledList<HashMapBucketHead_INL> _bucketHeadList;
		int32 _hashValueToBucketHeadListIdx[HASHMAP_CAPACITY] = { 0 };
		int32 _cnt = 0;
		// _itemPool은 Key와 Value를 모두 알고있기 때문에 현재 Item이 _hashValueToItemPoolIdx의 어디에 위치했는지 알 수 있다.
		// _hashValueToItemPoolIdx은 HashValue를 기준으로 Item을 찾을 수 있다.

	public:
		explicit HashMap(int32 InCapacity = 0)
		{
			if (InCapacity > 0)
			{
				_bucketHeadList.Reserve(InCapacity);
			}

			for (int32 i = 0; i < HASHMAP_CAPACITY; i++)
			{
				_hashValueToBucketHeadListIdx[i] = INVALID_IDX;
			}
		}

		void Reserve(int32 poolSize)
		{
			_bucketHeadList.Reserve(poolSize);
		}

		void Add(const KeyType& Key, const ValueType& Value)
		{
			const int32 hashValue = HashValue(Key) % HASHMAP_CAPACITY;
			int32 itemPoolIdx = _hashValueToBucketHeadListIdx[hashValue];
			if (itemPoolIdx == INVALID_IDX)
			{
				uint32 itemIdx = _bucketHeadList.GetSize();
				_hashValueToBucketHeadListIdx[hashValue] = itemIdx;

				_bucketHeadList.PushBack(HashMapBucketHead_INL(itemIdx, hashValue));
				
				HashMapBucket_INL* newHashMapNode = DBG_NEW HashMapBucket_INL(Key, Value);
				_bucketHeadList[itemIdx]._next = newHashMapNode;
			}
			else
			{
				HashMapBucket_INL* hashMapNodeItem = _bucketHeadList[itemPoolIdx]._next;
				while(hashMapNodeItem->_next != nullptr)
				{
					if(hashMapNodeItem->_pair.first == Key)
					{
						hashMapNodeItem->_pair.second = Value;
						return;
					}

					hashMapNodeItem = hashMapNodeItem->_next;
				}

				HashMapBucket_INL* newHashMapNode = DBG_NEW HashMapBucket_INL(Key, Value);
				hashMapNodeItem->_next = newHashMapNode;
			}
		}

		void Add(KeyType&& Key, ValueType&& Value)
		{
			const int32 hashValue = HashValue(Key) % HASHMAP_CAPACITY;
			int32 itemPoolIdx = _hashValueToBucketHeadListIdx[hashValue];
			if (itemPoolIdx == INVALID_IDX)
			{
				uint32 itemIdx = _bucketHeadList.GetSize();
				_hashValueToBucketHeadListIdx[hashValue] = itemIdx;

				_bucketHeadList.PushBack(HashMapBucketHead_INL(itemIdx, hashValue));

				HashMapBucket_INL* newHashMapNode = DBG_NEW HashMapBucket_INL(std::move(Key), std::move(Value));
				_bucketHeadList[itemIdx]._next = newHashMapNode;
				_cnt++;
			}
			else
			{
				HashMapBucket_INL* hashMapNodeItem = _bucketHeadList[itemPoolIdx]._next;
				while (hashMapNodeItem->_next != nullptr)
				{
					if (hashMapNodeItem->_pair.first == Key)
					{
						hashMapNodeItem->_pair.second = Value;
						return;
					}

					hashMapNodeItem = hashMapNodeItem->_next;
				}

				HashMapBucket_INL* newHashMapNode = DBG_NEW HashMapBucket_INL(Key, Value);
				hashMapNodeItem->_next = newHashMapNode;
				_cnt++;
			}
		}


		void Remove(const KeyType& Key)
		{
			const int32 hashValue = HashValue(Key) % HASHMAP_CAPACITY;
			const int32 itemPoolIdx = _hashValueToBucketHeadListIdx[hashValue];
			if (itemPoolIdx == INVALID_IDX)
			{
				return;
			}


			HashMapBucket_INL* hashMapNode = _bucketHeadList[itemPoolIdx]._next;
			HashMapBucket_INL* PrevNode = nullptr;
			HashMapBucket_INL* CurNode = nullptr;

			if(hashMapNode->_pair.first == Key)
			{
				_bucketHeadList[itemPoolIdx]._next = hashMapNode->_next;
				delete hashMapNode;
				_cnt--;
				goto lb_EMPTYHashMapNodeHead;
			}


			PrevNode = hashMapNode;
			CurNode = PrevNode->_next;

			while (CurNode != nullptr)
			{
				if(CurNode->_pair.first == Key)
				{
					PrevNode->_next = CurNode->_next;
					delete CurNode;
					_cnt--;
					return;
				}

				PrevNode = PrevNode->_next;
				CurNode = CurNode->_next;
			}
			

lb_EMPTYHashMapNodeHead:
			if (_bucketHeadList[itemPoolIdx]._next == nullptr)
			{
				_bucketHeadList.RemoveAtAndFillLast(itemPoolIdx);
				_hashValueToBucketHeadListIdx[hashValue] = INVALID_IDX;

				if (_bucketHeadList.GetSize() == 0)
				{
					return;
				}

				// TODO: 여기가 뭔가 이상하다. 여기서 계속 보자.
				if (_bucketHeadList.IsValidIndex(itemPoolIdx)) {
					HashMapBucketHead_INL& replacedHead = _bucketHeadList[itemPoolIdx];
					_hashValueToBucketHeadListIdx[replacedHead._hashValue] = itemPoolIdx;
					replacedHead._idxInArray = itemPoolIdx;
				}
			}

		}
		
		ValueType* Find(const KeyType& Key)
		{
			const int32 hashValue = HashValue(Key) % HASHMAP_CAPACITY;
			int32 itemPoolIdx = _hashValueToBucketHeadListIdx[hashValue];
			if (itemPoolIdx == INVALID_IDX)
			{
				return nullptr;
			}

			HashMapBucket_INL* hashMapNode = _bucketHeadList[itemPoolIdx]._next;
			do
			{
				if(hashMapNode->_pair.first == Key)
				{
					return &hashMapNode->_pair.second;
				}

				hashMapNode = hashMapNode->_next;
			} while (hashMapNode != nullptr);

			return nullptr;
		}
	};
}
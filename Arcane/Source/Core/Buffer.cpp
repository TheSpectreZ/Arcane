#include "Buffer.h"
#include "Utility.h"

namespace arc
{
	void MemoryBuffer::allocate(u64 capacity, bool bKeepData)
	{
		if (mCapacity >= capacity)
			return;

		u8* alloc = new u8[capacity];
	
		if (!empty())
		{
			if (bKeepData) 
			{
				memcpy(alloc, mData, mSize);
			}
			
			delete[] mData;
		}
		
		mData = alloc;
		mCapacity = capacity;
	}

	void MemoryBuffer::fill(u8* data, u64 size)
	{
		allocate(size, false);
		memcpy(mData, data, size);
		mSize = size;
	}

	void MemoryBuffer::fill(u8 value, u64 size)
	{
		allocate(size, false);
		memset(mData, value, size);
		mSize = size;
	}

	void MemoryBuffer::shrink_to_size()
	{
		if (mSize < mCapacity)
		{
			allocate(mSize);
		}
	}

	void MemoryBuffer::clear()
	{
		delete[] mData;
		mCapacity = 0;
		mSize = 0;
	}

	bool MemoryBuffer::empty()
	{
		return mSize == 0 || mData == nullptr;
	}

	//////////////////////////////////////////////////////////

	void ArrayBufferInterface::clear()
	{
		MemoryBuffer::clear();

		mElementCount = 0;
		mElementIndex = 0;
	}

	void ArrayBufferInterface::resize(u64 count)
	{
		allocate(count * mElementStride);
		mElementCount = count;
	}

	void ArrayBufferInterface::ipush_back(u8* pElement)
	{
		if (mElementIndex >= mElementCount)
		{
			expand(1);
		}

		u64 offset = mElementIndex * mElementStride;
		
		memcpy(&mData + offset, pElement, mElementStride);

		mElementIndex++;
	}
	
	void ArrayBufferInterface::ipop_back()
	{
		mElementIndex--;
	}

	const u8* ArrayBufferInterface::element_at(u64 Index) const
	{
		__ARC_ASSERT(Index < mElementCount, "ArrayBufferInterface: element_at index out of bounds\nIndex: {}\nElement-Count: {}", Index, mElementCount)
		return mData + Index * mElementStride;
	}

	u8* ArrayBufferInterface::element_at(u64 Index)
	{
		__ARC_ASSERT(Index < mElementCount, "ArrayBufferInterface: element_at index out of bounds\nIndex: {}\nElement-Count: {}", Index, mElementCount)
		return mData + Index * mElementStride;
	}

	void ArrayBufferInterface::expand(u64 NumElements)
	{
		resize(mElementCount + arc::Max(mElementCount / 2, NumElements));
	}
}
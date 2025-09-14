#pragma once
#include "Core/Type.h"
#include "Core/Assert.h"

#ifdef ARC_CORE_EXPORT
#define ARC_CORE_API __declspec(dllexport)
#else
#define ARC_CORE_API __declspec(dllimport)
#endif // ARC_CORE_EXPORT

namespace arc
{
	class ARC_CORE_API MemoryBuffer
	{
	public:
		MemoryBuffer() = default;
		MemoryBuffer(const MemoryBuffer& Other) { *this = Other; }
		MemoryBuffer(MemoryBuffer&& Other) noexcept { *this = std::move(Other); }

		virtual ~MemoryBuffer() { clear(); }

		MemoryBuffer& operator=(const MemoryBuffer& Other)
		{
			this->clear();
			this->fill(Other.mData, Other.mSize);
			return *this;
		}

		MemoryBuffer& operator=(MemoryBuffer&& Other) noexcept
		{
			this->clear();

			mData = Other.mData;
			mSize = Other.mSize;
			mCapacity = Other.mCapacity;

			Other.mData = nullptr;
			Other.mSize = 0;
			Other.mCapacity = 0;

			return *this;
		}

		virtual void clear();

		void allocate(u64 capacity, bool bKeepData = true);
		void fill(u8* data, u64 size);
		void fill(u8 value, u64 size);
		void shrink_to_size();
		
		bool empty();

		const u8* data() const	{ return mData; }
		u8*		  data()		{ return mData; }

		u64 size()	   const	{ return mSize; }
		u64 capacity() const	{ return mCapacity; }
	protected:
		u8* mData = nullptr;
		u64 mCapacity = 0;
		u64 mSize = 0; 

		u64 available_capacity() const { return mCapacity - mSize; }
	};

	//
	//

	class ARC_CORE_API ArrayBufferInterface : public MemoryBuffer
	{
	public:
		ArrayBufferInterface() = default;
		ArrayBufferInterface(const ArrayBufferInterface& Other) { *this = Other; }
		ArrayBufferInterface(ArrayBufferInterface&& Other) noexcept { *this = std::move(Other); }

		ArrayBufferInterface& operator=(const ArrayBufferInterface& Other)
		{
			MemoryBuffer::operator=(Other);
			
			mElementStride = Other.mElementStride;
			mElementIndex = Other.mElementIndex;
			mElementCount = Other.mElementCount;

			return *this;
		}

		ArrayBufferInterface& operator=(ArrayBufferInterface&& Other) noexcept
		{
			MemoryBuffer::operator=(std::move(Other));

			mElementStride = Other.mElementStride;
			mElementIndex = Other.mElementIndex;
			mElementCount = Other.mElementCount;

			Other.mElementStride = 0;
			Other.mElementIndex = 0;
			Other.mElementCount = 0;
			
			return *this;
		}

		virtual void clear() override;

		void resize(u64 count);
	protected:
		u64 mElementStride	= 0;
		u64 mElementIndex	= 0;
		u64 mElementCount	= 0;

		const u8* element_at(u64 Index) const;
		u8*		  element_at(u64 Index);

		void ipush_back(u8* pElement);
		void ipop_back();

		virtual void expand(u64 NumElements);	
	};
	
	//
	//

	class ARC_CORE_API RawArrayBuffer : public ArrayBufferInterface
	{
	public:
		RawArrayBuffer() = default;

		RawArrayBuffer(u64 elementSize, u64 initialElementCount)
		{
			Initialize(elementSize, initialElementCount);
		}

		inline void Initialize(u64 elementStride, u64 initialElementCount)
		{
			mElementStride = elementStride;
			resize(initialElementCount);
		}

		inline void push_back(void* valuePtr)
		{
			ArrayBufferInterface::ipush_back((u8*)valuePtr);
		}

		inline void pop_back()
		{
			ArrayBufferInterface::ipop_back();
		}

		inline void* operator[](u64 Index)
		{
			return reinterpret_cast<void*>(element_at(Index));
		}

		inline const void* operator[](u64 Index) const
		{
			return reinterpret_cast<const void*>(element_at(Index));
		}
	};

	//
	//

	template<typename T>
	class TArrayBuffer : public ArrayBufferInterface
	{
	public:
		TArrayBuffer()
		{
			resize(4);
		}

		inline void push_back(const T& value)
		{
			ArrayBufferInterface::ipush_back(&value);
		}

		inline void pop_back()
		{
			ArrayBufferInterface::ipop_back();
		}

		inline T& operator[](u64 Index)
		{
			return *(reinterpret_cast<T*>(element_at(Index)));
		}
		
		inline const T& operator[](u64 Index) const
		{
			return *(reinterpret_cast<const T*>(element_at(Index)));
		}
	};

	template<typename T>
	class TMemorySpan
	{
	public:
		TMemorySpan(u8* pData, u64 count)
			:mData(pData), mCount(count)
		{}
	private:
		const u8* mData;
		u64 mCount;
	};
}
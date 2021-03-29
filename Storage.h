#ifndef STORAGE_H
#define STORAGE_H
#include <memory>
#include <cstring>
using namespace std;
namespace lab11
{
    template<typename T>
    class Storage
    {
    public:
        Storage(unsigned int length);
        Storage(unsigned int length, const T& initialValue);
        Storage(const Storage& other);
        Storage(Storage&& other);
        Storage<T>& operator=(const Storage& rhs);
        Storage<T>& operator=(Storage&& rhs);
        ~Storage() = default;

        bool Update(unsigned int index, const T& data);
        const std::unique_ptr<T[]>& GetData() const;
        unsigned int GetSize() const;
    private:
        unique_ptr<T[]> mArray;
        unsigned int mCapacity;
    };

    template<typename T>
    Storage<T>::Storage(unsigned int length)
        : mCapacity(length)
        , mArray(make_unique<T[]>(length))
    {
    }

    template<typename T>
    Storage<T>::Storage(unsigned int length, const T& initialValue)
        : mCapacity(length)
        , mArray(make_unique<T[]>(length))
    {
        auto nakedPointer = mArray.get();
        for (unsigned int i = 0; i < mCapacity; ++i)
        {
            nakedPointer[i] = initialValue;
        }
    }

    template <typename T>
    Storage<T>::Storage(const Storage& other)
        : mCapacity(other.mCapacity)
        , mArray(make_unique<T[]>(other.mCapacity))
    {
        auto newNakedPointer = mArray.get();
        auto oldNakedPointer = other.mArray.get();
        memcpy(newNakedPointer, oldNakedPointer, mCapacity * sizeof(T));
    }

    template <typename T>
    Storage<T>::Storage(Storage&& other)
        : mCapacity(other.mCapacity)
        , mArray(std::move(other.mArray))
    {
        other.mArray.reset();
        other.mCapacity = 0;
    }

    template <typename T>
    Storage<T>& Storage<T>::operator=(const Storage& rhs)
    {
        if (&rhs == this)
        {
            return *this;
        }
        mCapacity = rhs.mCapacity;
        if (mArray != nullptr)
        {
            mArray.reset();
        }
        auto newNakedPointer = mArray.get();
        auto oldNakedPointer = rhs.mArray.get();
        memcpy(newNakedPointer, oldNakedPointer, mCapacity * sizeof(T));
        return *this;
    }

    template <typename T>
    Storage<T>& Storage<T>::operator=(Storage&& rhs)
    {
        if (&rhs == this)
        {
            return *this;
        }
        mCapacity = rhs.mCapacity;
        mArray = std::move(rhs.mArray);
        rhs.mArray.reset();
        rhs.mCapacity = 0;
        return *this;
    }

    template<typename T>
    bool Storage<T>::Update(unsigned int index, const T& data)
    {
        if (index >= mCapacity)
        {
            return false;
        }
        mArray[index] = data;
        return true;
    }

    template<typename T>
    const std::unique_ptr<T[]>& Storage<T>::GetData() const
    {
        return mArray;
    }

    template<typename T>
    unsigned int Storage<T>::GetSize() const
    {
        return mCapacity;
    }
}
#endif // STORAGE_H

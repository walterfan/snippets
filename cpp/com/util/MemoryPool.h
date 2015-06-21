#include <stdio.h>

template <class T>
class MemoryPool
{
public:
    MemoryPool(size_t nSize = EXPANSION_SIZE);
    ~MemoryPool();

    inline void* Alloc(size_t nSize);
    inline void Free(void* pElement);

private:
    MemoryPool<T>* m_pNext;
    enum {EXPANSION_SIZE = 32};

    void ExpandFreeList(int nSize = EXPANSION_SIZE);
};

template <class T>
void MemoryPool<T>::ExpandFreeList(int nSize)
{
    
}
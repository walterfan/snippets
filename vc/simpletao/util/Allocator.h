#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

//http://www.codeproject.com/Articles/4795/C-Standard-Allocator-An-Introduction-and-Implement

class MemPool
{
private:
    const int m_nMemBlockSize;
    const int m_nItemSize;
 
    struct _FreeNode {
        _FreeNode* pPrev;
        BYTE data[m_nItemSize - sizeof(_FreeNode*)];
    };
 
    struct _MemBlock {
        _MemBlock* pPrev;
        _FreeNode data[m_nMemBlockSize/m_nItemSize];
    };
 
    _MemBlock* m_pMemBlockHeader;
    _FreeNode* m_pFreeNodeHeader;
 
public:
   MemPool(int nItemSize, int nMemBlockSize = 2048)
       : m_nItemSize(nItemSize), m_nMemBlockSize(nMemBlockSize),
         m_pMemBlockHeader(NULL), m_pFreeNodeHeader(NULL)
   {
   }
};


template<typename T>
class CAllocator
{
public:
	CAllocator(void);
	~CAllocator(void);
public : 
    //    typedefs
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public : 
    //    convert an allocator<T> to allocator<U>
    template<typename U>
    struct rebind {
        typedef Allocator<U> other;
    };

public : 
    inline explicit Allocator() {}
    inline ~Allocator() {}
    inline explicit Allocator(Allocator const&) {}
    template<typename U>
    inline explicit Allocator(Allocator<U> const&) {}

    //    address
    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    inline pointer allocate(size_type cnt, 
       typename std::allocator<void>::const_pointer = 0) { 
      return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T))); 
    }
    inline void deallocate(pointer p, size_type) { 
        ::operator delete(p); 
    }

    //    size
    inline size_type max_size() const { 
        return std::numeric_limits<size_type>::max() / sizeof(T);
 }

    //    construction/destruction
    inline void construct(pointer p, const T& t) { new(p) T(t); }
    inline void destroy(pointer p) { p->~T(); }

    inline bool operator==(Allocator const&) { return true; }
    inline bool operator!=(Allocator const& a) { return !operator==(a); }
};    //    end of class Allocator 

#endif
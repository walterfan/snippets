/*---------------------------------------------------------
*
* Filename: SmartPtr.h
* Description: 
*    Smart Pointer , 
*    modified from Sandu Turcan,  idlsoft@hotmail.com
*
* Version:1.0
* Create date: 05/03/2007
*
-----------------------------------------------------------*/
#ifndef __SMARTPTR_H__
#define __SMARTPTR_H__

template <class T> class SmartPtr;

/////////////////////////////////////////////////////////
// IRefCount
// is an interface for reference counting
// Classes can implement it themselves,
// or SmartPtr will provide its internal implementation of IRefCount
//-- AddRef after new
//-- AddRef before using it
//-- Release after used it
//-- Release if not use it any more
//////////////////////////////////////////////////////////
template <class T> 
class IRefCount 
{
    friend class SmartPtr<T>;
public:
    virtual void AddRef() = 0;
    virtual void Release() = 0;
    virtual T * GetPtr() const = 0;
};

/////////////////////////////////////////
// IRefCountImpl
// is a standart implementation of IRefCount
// To use it just derive your class from it:
// class CMyObject : public IRefCountImpl<CMyObject> { ... };
// Reminder: implementing IRefCount is optional but it would reduce
// memory fragmentation. 
template <class T> 
class IRefCountImpl : public IRefCount<T> 
{
private:
    int m_counter;
public:
    virtual void AddRef() 
    {
        m_counter++; 
    }
    virtual void Release()
    {
        m_counter--;
        if(m_counter<=0)
        {
            DestroyRef();
        }
    }
    virtual T * GetPtr() const
    {
        return ((T *)this);
    }
    virtual void DestroyRef() 
    { 
        if(GetPtr()!=NULL)
            delete GetPtr();
    }

    int Count()
   {
    return m_counter;
   }

protected:
    IRefCountImpl()
    {
        m_counter = 0;
    }
};

/////////////////////////////////////////
// SmartPtr
// Usage:
// ----------------------
// 1. In a program block
// ----------------------
// SmartPtr<CMyObject> ptr1(new CMyObject); // creates object 1
// SmartPtr<CMyObject> ptr2(new CMyObject); // creates object 2
// ptr1 = ptr2;             // destroys object 1
// ptr2 = NULL;
// ptr1 = new CMyObject;    // creates object 3, destroys object 2
// ptr1->methodcall(...);
// CMyObject o1;
// // ptr1 = &o1;  // DON'T ! only memory allocated by new operator should be used
// CMyObject *o2 = new CMyObject;
// ptr1 = o2;
// //ptr2 = o2;  // DON'T ! unless CMyObject implements IRefCount
//               // try to use ptr1 = ptr2 instead, it's always safe;
// ----------------------
// 2. in a function call
// ----------------------
// void f(CMyObject *o) {...}
// ...
// SmartPtr<CMyObject> ptr(new CMyObject)
// f(ptr);
// ----------------------
// 3. As a return value
// ----------------------
// SmartPtr<CMyObject> f()
// {
//      SmartPtr<CMyObject> ptr(new CMyObject);
//      return ptr;
// }
template <class T> 
class SmartPtr 
{
private:
    IRefCount<T> *m_refcount;

    /////////////////////////////////////////
    // RefCounter
    // An internal implementation of IRefCount
    // for classes that don't implement it
    // SmartPtr will automatically choose between its internal and 
    // class' implementation of IRefCount
    class RefCounter : public IRefCountImpl<T> 
    {
    private:
            T *m_ptr;
    protected:
            virtual T * GetPtr() const
            {
                return m_ptr;
            }
            
            virtual void DestroyRef() 
        {
            delete this;
        }
            
    public:
        RefCounter(T *ptr)
        {
            m_ptr = ptr;
        }
        virtual ~RefCounter()
        {
            IRefCountImpl<T>::DestroyRef();
        }
    };
    // this method is called if T does not implement IRefCount
    void Assign(void *ptr)
    {
        if(ptr==NULL)
        {   
            Assign((IRefCount<T> *)NULL);
        }
        else
        {
            Assign(new RefCounter(static_cast<T *>(ptr)));
        }
    }
    // this method is picked over Assign(void *ptr)
    // if T implements IRefCount.
    // This allows some memory usage optimization
    void Assign(IRefCount<T> *refcount)
    {
        if(refcount!=NULL) 
            refcount->AddRef();
        IRefCount<T> *oldref = m_refcount;
        m_refcount = refcount;
        if(oldref!=NULL) 
            oldref->Release();
    }
public:
    SmartPtr()
    {
        m_refcount = NULL;
    }
    SmartPtr(T * ptr)
    {
        m_refcount = NULL;
        Assign(ptr);
    }
    SmartPtr(const SmartPtr &sp)
    {
        m_refcount = NULL;
        Assign(sp.m_refcount);
    }
    virtual ~SmartPtr()
    {
        Assign((IRefCount<T> *)NULL);
    }

    // get the contained pointer, not really needed but...
    T *GetPtr() const
    {
        if(m_refcount==NULL) return NULL;
        return m_refcount->GetPtr();
    }

    // assign another smart pointer
    SmartPtr & operator = (const SmartPtr &sp) 
    {
        Assign(sp.m_refcount); 
        return *this;
    }
    // assign pointer or NULL
    SmartPtr & operator = (T * ptr) 
    {
        Assign(ptr); 
        return *this;
    }
    // to access members of T
    T * operator ->()
    {
        WFASSERT(GetPtr()!=NULL);
        return GetPtr();
    }
    // conversion to T* (for function calls)
    operator T* () const
    {
        return GetPtr();
    }

    // utilities
    bool operator !()
    {
        return GetPtr()==NULL;
    }
    bool operator ==(const SmartPtr &sp)
    {
        return GetPtr()==sp.GetPtr();
    }
    bool operator !=(const SmartPtr &sp)
    {
        return GetPtr()!=sp.GetPtr();
    }
};


#endif

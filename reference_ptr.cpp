#include <iostream>

template<typename T>
class Reference
{
public:
    typedef T value_type;

public:
    Reference(T *ref):
        m_referenced(ref)
    {
        m_count = new size_t;
        *m_count = 1;
    }

    Reference(const Reference& rhs):
        m_referenced(rhs.m_referenced),
        m_count(rhs.m_count)
    {
        increase_count();
    }

    Reference& operator=(const Reference& rhs)
    {
        decrease_count();
        m_referenced = rhs.m_referenced;
        m_count = rhs.m_count;
        increase_count();
    }

    T& operator*() const 
    {
        return *m_referenced;
    }

    T* operator->() const
    {
        return m_referenced;
    }
    
    ~Reference()
    {
        decrease_count();
    }

private:
    void decrease_count() 
    { 
        --(*m_count);
        if(!*m_count)
        {
            delete m_referenced;
            delete m_count;
        }
    }
    
    void increase_count()
    {
        ++(*m_count);
    }

private:
    T *m_referenced;
    size_t *m_count;
};

struct Foo
{
    int a;
};

int main()
{
    Reference<int> a((new int));
    Reference<int> b((new int));
    a = b;
    return 0;

}

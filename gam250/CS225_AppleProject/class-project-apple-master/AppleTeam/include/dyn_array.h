#include <assert.h>
template<typename T>
class dyn_array
{
public:
    T operator[](int i) 
    { 
        assert(i < length);
        return heap[i];
    }
    size_t size()
    {
        return length;
    }
    void* operator new(size_t size)
    {
        heap = new T;
        length = size;
    }
private:
    T* heap = nullptr;
    size_t length = 0;
};
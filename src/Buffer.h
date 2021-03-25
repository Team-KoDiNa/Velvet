#pragma once
#include <stdexcept>
#include <array>
#include <memory>

template <typename dtype>
class BaseBuffer {
private:
    int length;
    dtype* buffer
    
public:
    void release() {
        length = 0;
        if(buffer != nullptr){
            delete[] buffer;
        }
        buffer = nullptr;
    }
    
    BaseBuffer slice(int count) {
        BaseBuffer buf(count);
        memcpy(buf.buffer, buffer, count);
        return buf;
    }
    
    void reserve(int _size){
        if (_size <= 0) {
            release();
            thorw std::runtime_error("buffer error: sizeUnderZero")
        }
        length = _size;
        if(buffer != nullptr){
            delete[] buffer;
        }
        buffer = new dtype[length];
    }
    
    int size() const{
        return length;
    }
    
    dtype* getBuffer() const{
        return buffer;
    }
    
    BaseBuffer(){
        length = 0;
        buffer = nullptr;
    }
    
    BaseBuffer(int size) : buffer(nullptr){
        reserve(size);
    }
    
    BaseBuffer(BaseBuffer&& o) noexcept{
        length = o.length;
        buffer = o.buffer;
        
        o.length = 0;
        o.buffer = nullptr;
    }
    
    BaseBuffer& operator=(BaseBuffer&& o) noexcept {
        length = o.length;
        buffer = o.buffer;
        
        o.length = 0;
        o.buffer = nullptr;
        
        return *this;
    }
    
    ~BaseBuffer(){
        if(buffer) delete[] buffer;
    }
};

using CBuffer = BaseBuffer<char>;

template <class T, int N>
class <#class name#> {
    <#instance variables#>
    
public:
    <#member functions#>
};

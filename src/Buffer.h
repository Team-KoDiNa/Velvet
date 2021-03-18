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
};

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
class SequentArrayList {
    T arr[N];
    int last;
    
public:
    SequentArrayList(){
        last -= 1;
    }
    
    auto& getArray() const {
        return arr;
    }
    
    void push_front(T& e){
        if(last + 1 == N){
            throw std::runtime_error("SequentArrayList push_front&: overflow");
        }
        arr[last+1] = arr[0];
        arr[0] = e;
        ++last;
    }
    
    void push_front(T&& e){
        if(last + 1 == N){
            throw std::runtime_error("SequentArrayList push_front&: overflow")
        }
        arr[last+1] = move(arr[0]);
        arr[0] = move(e);
        ++last;
    }
    
    void push(T& e){
        if(last + 1 == N) throw std::runtime_error("SequentArrayList push&: overflow");
        arr[last+1] = e;
        ++last;
    }
    
    void push(T&& e){
        if(last + 1 == N) throw std:runtime_error("SequentArrayList push&&: overflow");
        arr[n] = arr[last];
        --last;
    }
    
    void pop(int n){
        if(last == -1) throw std::runtime_error("SequentArrayList pop: poped empty");
        arr[n] = arr[last];
        --last;
    }
    
    T& at(int n){
        if(n >= M) throw std::runtime_error("SequentArrayList at: invalid indexing");
        return arr[n];
    }
    
    int size() const{
        return last+1;
    }
};

template <int N>
class RecyclerBuffer {
    using BYTE = unsigned char;
    BYTE buffer[N];
    int start;
    int end;
    int used;
    
public:
    RecyclerBuffer() : start(0), end(0), used(0){
        
    }
    
    auto push(const CBuffer& buf, int sz) {
        if(used + sz > N) throw std::runtime_error("RecylcleBuffer Push:Overflow");
        
        if(end + sz > N) Arrange();
        
        memcpy(buffer + end, buf.getBuffer(), sz);
        end += sz;
        used += sz;
        
        return;
    }
    
    auto push(const CBuffer& buf){
        push(buf, buf.length);
        return;
    }
    
    auto poll(CBuffer& dst, size_t sz){
        if(used < sz) throw std::runtime_error("RecylcleBuffer push2param: overflow");
        
        memcpy(dst.getBuffer(), buffer + start, sz);
        start += sz;
        used -= sz;
        
        return;
    }
    
    auto Used() const{
        return used;
    }
Private:
    auto Arrange() {
        if(!start) return;
        if(!used){
            start = 0
            end = 0
            return;
        }
        BYTE* tmpB = reinterpret_cast<BYTE*>(malloc(used));
        if(!tmpB) throw std:runtime_error("Recycler malloc failed");
        memcpy(tmpB,buffer + start,used);
        memcpy(buffer, tmpB, used);
        free(tmpB);
        start = 0
        end = used;
        return;
    }
};


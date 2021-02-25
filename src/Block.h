#ifndef Block_h
#define Block_h

#include <cstdint>
#include <iostream>

using namespace std;

class Block {
public:
    string sPrevHash;
    Block(uint32_t nIndexIn, const string &sDataIn);
    string GetHash();
    void MineBlock(uint32_t nDifficulty);
    
private:
    uint32_t _nIndex;
    int64_t _nNonce;
    string _sData;
    string _sHash;
    time_t _tTime;
    
    string _CalculateHash() const;
};


#endif

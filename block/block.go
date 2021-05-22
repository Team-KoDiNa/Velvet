package velvet

import (
	"bytes"
	"crypto/sha256"
	"strconv"
	"time"
)

const BlockLimit = 10000000000000000

type Block struct {
	prevHash   []byte
	hash       []byte
	data       []byte
	nonce      uint
	difficulty uint
	timestamp  int64
}

func NewBlock(data string, prevHash []byte) *Block {
	block := &Block{prevHash: prevHash, hash: nil, data: []byte(data), nonce: 0, difficulty: 0, timestamp: time.Now().Unix()}
	return block
}

func (b *Block) InitHash() {
	timestamp := []byte(strconv.FormatInt(b.timestamp, 10))
	headers := bytes.Join([][]byte{b.prevHash, b.data, timestamp}, []byte{})
	hash := sha256.Sum256(headers)
	b.hash = hash[:]
}

package velvet

import (
	"bytes"
	"math/big"
	"strconv"
)

type PoW struct {
	block  *Block
	target *big.Int
}

func TargetBits() int {
	targetbits := 5
	if targetbits < 256 {
		targetbits = targetbits * NewBlockchain().isHalving()
	} else {
		targetbits = 256
	}
	return targetbits
}

func NewPoW(b *Block) *PoW {
	target := big.NewInt(1)
	target.Lsh(target, uint(256-TargetBits()))

	pow := &PoW{block: b, target: target}
	return pow
}

func IntToHex(n int64) []byte {
	return []byte(strconv.FormatInt(n, 16))
}

func (pow *PoW) prepareData(nounce int) []byte {
	data := bytes.Join(
		[][]byte{
			pow.block.prevHash,
			pow.block.data,
			IntToHex(pow.block.timestamp),
			IntToHex(int64(TargetBits())),
			IntToHex(int64(nounce)),
		},
		[]byte{},
	)
	return data
}

package velvet

type BlockChain struct {
	blocks []*Block
}

var halving = 1

func (bc *BlockChain) AddBlock(data string) {
	prevBlock := bc.blocks[len(bc.blocks)-1]
	newBlock := NewBlock(data, prevBlock.prevHash)
	bc.blocks = append(bc.blocks, newBlock)
}

func NewGenesisBlock() *Block {
	return NewBlock("Genesis Block", []byte{})
}

func NewBlockchain() *BlockChain {
	return &BlockChain{[]*Block{NewGenesisBlock()}}
}

func (bc *BlockChain) isHalving() int {
	if len(bc.blocks)%230000 == 0 {
		halving = halving * 2
	}
	return halving
}

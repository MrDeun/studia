package main

import (
	"log"
	"os"
	"slices"
	"strconv"
)

var l log.Logger

func generatePowerNumbers(a int64, bitsB []byte, modulo int64) []int64 {
	len_bitsB := len(bitsB)
	new_slice := make([]int64, len_bitsB)
	new_slice[0] = a % modulo
	for i := 1; i < len_bitsB; i++ {
		new_slice[i] = (new_slice[i-1] * new_slice[i-1]) % modulo
	}
	// l.Printf("%v", new_slice)
	slices.Reverse(new_slice)
	// l.Printf("%v", new_slice)
	return new_slice
}
func ModuloPower(a, b, n int64) int64 {
	l = *log.New(os.Stderr, "MODULO CHECK: ", log.LstdFlags)
	binaryB := []byte(strconv.FormatInt(b, 2))
	for i := range binaryB {
		binaryB[i] -= '0'
	}
	fragments := generatePowerNumbers(a, binaryB, n)
	result := int64(1)
	for i, v := range binaryB {
		if v == 1 {
			result *= fragments[i]
		}
	}
	return result % n
}

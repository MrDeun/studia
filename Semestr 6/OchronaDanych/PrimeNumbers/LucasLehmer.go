package main

import (
	"fmt"
	"log"
	"os"
	"slices"
)

var _is_prime = []uint{2, 3, 5, 7, 11, 13, 17, 19, 23, 31}
var l log.Logger

func uint_pow(x, y uint) uint {
	var res uint = 1
	var i uint
	for i = 0; i < y; i++ {
		res *= x
	}
	return res
}

func lucas_lehmer_test(mersen, p uint) bool {
	var s uint = 4
	var i uint
	for i = 0; i < p; i++ {
		// l.Printf("%d\n", s)
		s = (s<<1 - 2) % mersen
	}

	return s%mersen == 0
}

func main() {
	var i uint
	l = *log.New(os.Stderr, "", 0)
	for i = 0; i < 32; i++ {
		mersen := uint_pow(uint(2), i) - 1
		if slices.Contains(_is_prime, mersen) {
			fmt.Printf("2^%d - 1 is prime number - %t\n", i, lucas_lehmer_test(mersen, i))
		}
	}

}

package main

import (
	"fmt"
	"log"
	"math/rand"
	"os"
)

var alphabet = []byte("abcdefghijklmnopqrstuvwxyz")

func generateStr(str_size int, r *rand.Rand) string {
	buf := make([]byte, str_size)
	for i := 0; i < str_size; i++ {
		random_choice := r.Int() % 26
		buf[i] = alphabet[random_choice]
	}
	return string(buf)
}

func countCollisions(hashes []uint32) int {
	collisions := 0
	for i := range hashes {
		for j := range hashes {
			if hashes[i] == hashes[j] && i != j {
				collisions++
			}
		}
	}
	return collisions / 2
}

func adler32(_str string) uint32 {
	A := uint16(1)
	B := uint16(0)
	for _, c := range _str {
		A = (A + uint16(c)) % 65521
		B = (B + A) % 65521
	}
	return uint32((uint32(B) << 16) | uint32(A))
}

func B5381(_str string) uint32 {
	hash := uint32(5381)
	for _, c := range _str {
		hash = hash << 5
		hash = hash + uint32(c)
	}
	return hash
}

func main() {
	if len(alphabet) != 26 {
		log.Fatal("Alphabet is not complete!")
		os.Exit(1)
	}

	src := rand.NewSource(256)
	r := rand.New(src)

	generated_strings := make([]string, 100000)
	B5381_hashes := make([]uint32, 100000)
	ADLER32_hashes := make([]uint32, 100000)
	for i := range generated_strings {
		generated_strings[i] = generateStr(8, r)
		B5381_hashes[i] = B5381(generated_strings[i])
		ADLER32_hashes[i] = adler32(generated_strings[i])
	}

	fmt.Printf("\nB5381 collision count: %d\nADLER32_hashes: %d", countCollisions(B5381_hashes), countCollisions(ADLER32_hashes))

}

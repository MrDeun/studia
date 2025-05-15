package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
)

var alphabet = []byte("abcdefghijklmnopqrstuvwxyz")

func hashToStr(hash uint32) string {
	res := ""
	str_hash := strconv.Itoa(int(hash))
	for _, digit := range str_hash {
		res += string(alphabet[digit%26])
	}
	return res
}

func generateStr(str_size int, r *rand.Rand) string {
	buf := make([]byte, str_size)
	for i := 0; i < str_size; i++ {
		random_choice := r.Int() % 26
		buf[i] = alphabet[random_choice]
	}
	return string(buf)
}
func B5381(_str string) uint32 {
	hash := uint32(5381)
	for _, c := range _str {
		hash = hash << 5
		hash = hash + uint32(c)
	}
	return hash
}

func generateHashingTable(str_count, max_iter int) map[string]uint32 {
	randSource := rand.NewSource(64)
	randGen := rand.New(randSource)

	hashing_table := make(map[string]uint32, str_count)

	for i := 0; i < str_count; i++ {
		og_phrase := generateStr(8, randGen)
		hash := uint32(0)
		phrase := og_phrase
		for j := 0; j < max_iter; j++ {
			hash = B5381(phrase)
			phrase = hashToStr(hash)
		}
		hashing_table[phrase] = hash
	}
	return hashing_table
}

func saveToFile(table map[string]uint32) {
	file, err := os.Create("table.csv")
	defer file.Close()
	if err != nil {
		panic(err)
	}
	w := bufio.NewWriter(file)
	for k, v := range table {
		record := fmt.Sprintf("%s,%d\n", k, v)
		w.WriteString(record)
	}
}

func main() {
	table := generateHashingTable(100000, 10)
	saveToFile(table)
}

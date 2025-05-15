package main

import (
	"bufio"
	"fmt"
	"io"
	"math/rand"
	"os"
	"strconv"
	"strings"
)

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
func loadTable(filename string) map[string]uint32 {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	table := make(map[string]uint32)
	r := bufio.NewReader(file)
	for {
		record, err := r.ReadString('\n')
		if err == io.EOF {
			break
		} else if err != nil {
			panic(err)
		}
		foo := strings.Split(record, ",")
		phrase := foo[0]
		hash, err := strconv.Atoi(foo[1])
		if err != nil {
			panic(err)
		}

		table[phrase] = uint32(hash)
	}

	return table
}

func iterateThroughTable(k string, max_iter int) string {

}

func main() {
	table := loadTable("table.csv")
	finding_phrase := ""
	fmt.Print("Input your phrase: ")
	fmt.Scan(&finding_phrase)
	my_hash := B5381(finding_phrase)

	for k, v := range table {
		if v == my_hash {
			found_str := iterateRecord(k, 10)
		}
	}

}

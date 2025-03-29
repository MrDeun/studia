package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func find_distances(data []byte, min_len int) []int {
	var distances []int
	var indexes map[[]byte][]int
	for i := 0; i < len(data)-min_len; i++ {
		frag := data[i : i+min_len]
		indexes[frag] = []int{}
	}

	for _, v := range indexes {
		if len(v) > 1 {
			for i := 0; i < len(v); i++ {
				for j := i + 1; j < len(v); j++ {
					distances = append(distances, v[j]-v[i])
				}
			}
		}
	}

	return distances
}

func main() {
	filename := ""
	fmt.Print("Enter a filename of your encrypted file: ")
	fmt.Scan(&filename)

	raw_data, err := os.ReadFile(filename)
	if err != nil {
		log.Fatal(err.Error())
	}
	raw_data = []byte(strings.ToUpper(string(raw_data)))

	var min_len int
	var max_val int

}

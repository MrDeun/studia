package main

import (
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
)

func create_ratio(data []byte) map[byte]float64 {
	size := len(data)
	count_map := make(map[byte]int, size)
	for _, v := range data {
		count_map[v]++
	}
	percent_map := make(map[byte]float64, size)
	for key, value := range count_map {
		percent_map[key] = float64(value) / float64(size)
	}

	return percent_map
}

func main() {
	fmt.Println("Hello to encryption checking!")
	filename := ""

	fmt.Print("Insert encrypted filename: ")
	fmt.Scan(&filename)
	encrypted, err := os.ReadFile(filename)
	if err != nil {
		log.Fatal(err)
	}
	encrypted = []byte(strings.ToUpper(string(encrypted)))

	fmt.Print("Insert pattern filename: ")
	fmt.Scan(&filename)
	pattern, err := os.ReadFile(filename)
	if err != nil {
		log.Fatal(err)
	}
	pattern = []byte(strings.ToUpper(string(pattern)))

	encrypted_percent := create_ratio(encrypted)
	pattern_percent := create_ratio(pattern)

	keys := []byte{}
	for k, _ := range encrypted_percent {
		keys = append(keys, k)
	}

	for k, _ := range pattern_percent {
		if !slices.Contains(keys, k) {
			keys = append(keys, k)
		}
	}
	fmt.Println("KEY \t ENCRYPTED \t PATTERN")
	for _, k := range keys {
		fmt.Printf("%s \t %f \t %f\n", string(k), encrypted_percent[k], pattern_percent[k])
	}

}

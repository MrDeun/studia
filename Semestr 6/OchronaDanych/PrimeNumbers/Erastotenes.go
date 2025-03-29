package main

import (
	"fmt"
	"slices"
)

func create_slice_numbers(v int) []uint {
	res := []uint{}
	for i := 2; i < v; i++ {
		res = append(res, uint(i))
	}

	for i := 0; i < len(res); i++ {
		prime := res[i]
		for j := i + 1; j < len(res); j++ {
			if res[j]%prime != 0 {
				res[j] = 0
			}
		}
		slices.Sort(res)
		index_of_not_zero := slices.Index(res, 2)
		res = res[index_of_not_zero : len(res)-1]
	}

	return res
}

func main() {
	arr := create_slice_numbers(1000)
	fmt.Printf("%v", arr)
}

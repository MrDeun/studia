package main

import "fmt"

func Shift(nums []byte, k int) []byte {
	if k == 0 || len(nums) == 0 {
		return nums
	}
	r := (len(nums) - k%len(nums)) % len(nums)
	nums = append(nums[r:], nums[:r]...)
	return nums
}

func create_matrix(alphabet []byte) [][]byte {
	result := make([][]byte, len(alphabet))
	for i := 0; i < len(alphabet); i++ {
		copy_alphabet := alphabet
		copy_alphabet = Shift(copy_alphabet, -i)
		result[i] = copy_alphabet
	}
	return result
}

func main() {
    alphabet := []byte("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
    matrix := create_matrix(alphabet)
    for _, row := range matrix{
        str_row := string(row)
        fmt.Printf("%s\n",str_row)
    }
}

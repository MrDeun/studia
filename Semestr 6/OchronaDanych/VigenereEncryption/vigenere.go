package main

import (
	"errors"
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
)

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

func encrypt(encryption_matrix [][]byte, to_encrypt []byte, password []byte) ([]byte, error) {
	alphabet := encryption_matrix[0]
	for _, letter := range password {
		if !slices.Contains(alphabet, letter) {
			err := errors.New(fmt.Sprintf("Password contains a character '%s' that doesn't exist in the alphabet!", string(letter)))
			return nil, err
		}
	}
	result := []byte{}
	for i, c := range to_encrypt {
		if !slices.Contains(alphabet, c) {
			result = append(result, c)
			continue
		}
		row := slices.Index(alphabet, c)
		column_index := slices.Index(alphabet, password[i%len(password)])
		column := slices.Index(alphabet, encryption_matrix[column_index][0])
		fmt.Printf("row: %d \t column: %d \n", row, column)
		new_letter := encryption_matrix[column][row]
		result = append(result, new_letter)
	}

	return result, nil
}

func decrypt(encryption_matrix [][]byte, to_encrypt []byte, password []byte) ([]byte, error) {
	panic("Decryption not implemented yet!")
	alphabet := encryption_matrix[0]
	for _, letter := range password {
		if !slices.Contains(alphabet, letter) {
			err := errors.New(fmt.Sprintf("Password contains a character '%s' that doesnt exist in the alphabet!", string(letter)))
			return nil, err
		}
	}
	return nil, nil
}

func main() {
	alphabet_s := "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	alphabet := []byte(alphabet_s)
	encryption_matrix := create_matrix(alphabet)

	var choice = 9

	filename := ""
	fmt.Print("\nEnter an filename of text:")
	fmt.Scan(&filename)
	file_data, err := os.ReadFile(filename)
	if err != nil {
		log.Fatal(err)
		os.Exit(1)
	}
	file_data = []byte(strings.ToUpper(string(file_data)))

	password := ""
	fmt.Print("\nEnter your password: ")
	fmt.Scan(&password)
	password = strings.ToUpper(password)
	for choice != 0 && choice != 1 {
		fmt.Print("Select an encryption/decryption [1/2]: ")
		fmt.Scan(&choice)
	}

	switch choice {
	case 0:
		result, err := encrypt(encryption_matrix, file_data, []byte(password))
		if err != nil {
			log.Fatal(err)
			os.Exit(1)
		}
		os.WriteFile("encrypted.txt", result, 0644)
	case 1:
		result, err := decrypt(encryption_matrix, file_data, []byte(password))
		if err != nil {
			log.Fatal(err)
			os.Exit(1)
		}
		os.WriteFile("decrypted.txt", result, 0644)
	default:
		fmt.Errorf("Incorrect option has been selected")
		os.Exit(1)
	}
	os.Exit(0)
}

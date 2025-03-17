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

func decrypt(encryption_matrix [][]byte, to_decrypt []byte, password []byte) ([]byte, error) {
	// panic("Decryption not implemented yet!")
	alphabet := encryption_matrix[0]
	for _, letter := range password {
		if !slices.Contains(alphabet, letter) {
			err := errors.New(fmt.Sprintf("Password contains a character '%s' that doesnt exist in the alphabet!", string(letter)))
			return nil, err
		}
	}
	result := []byte{}
	for index_c, c := range to_decrypt {
		if !slices.Contains(alphabet, c) {
			result = append(result, c)
		} else {
			password_char := password[index_c%len(password)]
			index_encrypted_row := slices.Index(alphabet, password_char)
			index_password_char := slices.Index(encryption_matrix[index_encrypted_row], c)
			result = append(result, alphabet[index_password_char])
		}
	}
	return result, nil
}

var alphabet = []byte("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
var encryption_matrix = create_matrix(alphabet)

func print_encryption_matrix(encrypt [][]byte) {
	for _, row := range encrypt {
		for _, c := range row {
			fmt.Printf("%c ", c)
		}
		fmt.Println("")
	}
}

func main() {

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
	for choice != 1 && choice != 2 {
		fmt.Print("Select an encryption/decryption [1/2]: ")
		fmt.Scan(&choice)
	}

	switch choice {
	case 1:
		result, err := encrypt(encryption_matrix, file_data, []byte(password))
		if err != nil {
			log.Fatal(err)
			os.Exit(1)
		}
		os.WriteFile("encrypted.txt", result, 0644)
	case 2:
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
	print_encryption_matrix(encryption_matrix)
	os.Exit(0)
}

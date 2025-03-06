package main

import (
	"fmt"
	"log"
	"os"
	"slices"
	"strings"
)

func encrypt(alphabet []byte, input int, shift_count int) byte {
	return (alphabet[((int(input) + shift_count) % len(alphabet))])
}

func decrypt(alphabet []byte, input int, shift_count int) byte {
	return (alphabet[((int(input) - shift_count) % len(alphabet))])
}

func encrypt_whole(input_str []byte, alphabet []byte, shift_count int) []byte {
	buf := []byte{}
	for _, v := range input_str {
		log.Printf("%s", string(v))
		if slices.Contains(alphabet, v) {
			index := slices.Index(alphabet, v)
			buf = append(buf, encrypt(alphabet, index, shift_count))
		} else {
			buf = append(buf, v)
		}
	}
	return buf
}

func decrypt_whole(input_str []byte, alphabet []byte, shift_count int) []byte {
	buf := []byte{}
	for _, v := range input_str {
		log.Printf("%s", string(v))
		if slices.Contains(alphabet, v) {
			index := slices.Index(alphabet, v)
			buf = append(buf, decrypt(alphabet, index, shift_count))
		} else {
			buf = append(buf, v)
		}
	}
	return buf
}

func main() {
	alphabet_s := "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	alphabet := []byte(alphabet_s)
	fmt.Println("Hello to Caesar Code decrypt/encrypt!")
	// fmt.Printf("The alphabet is: %v\n", alphabet)

	filename := ""
	fmt.Print("Input a file name: ")
	fmt.Scan(&filename)

	original_msg, err := os.ReadFile(filename)
	if err != nil {
		fmt.Println("Error! File not found!")
		os.Exit(1)
	}
	original_msg = []byte(strings.ToUpper(string(original_msg)))

	choice := 9
	for (choice != 1) && (choice != 2) {
		fmt.Print("Choose encrypt/decrypt [1/2]: ")
		fmt.Scanf("%d", &choice)
	}

	shift_count := 0
	fmt.Print("Input shift count: ")
	fmt.Scan(&shift_count)
	msg := []byte{}
	if choice == 1 {
		msg = encrypt_whole(original_msg, alphabet, shift_count)
	} else if choice == 2 {
		msg = decrypt_whole(original_msg, alphabet, shift_count)
	} else {
		log.Panic("Unknown operation on message!")
	}

	os.WriteFile("result.txt", msg, 0644)

	os.Exit(0)
}

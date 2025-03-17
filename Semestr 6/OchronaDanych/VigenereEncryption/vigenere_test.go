package main

import (
	"log"
	"testing"
)

var password = []byte("BA9")

var non_encrypted = []string{
	"6CDB;C",
	"D23#4",
	"999",
}

var encrypted = []string{
	"CCCC;C",
	"C33#3",
	"A98",
}

func TestEncrypt(t *testing.T) {
	for i, to_encrypt := range non_encrypted {
		result, err := encrypt(encryption_matrix, []byte(to_encrypt), password)
		if string(result) != encrypted[i] {
			t.Errorf("Error! Expeteced %s, got %s", encrypted[i], string(result))
			if err != nil {
				log.Fatal(err.Error())
			}
		}
	}
}

func TestDecrypt(t *testing.T) {
	for i, to_decrypt := range encrypted {
		result, err := decrypt(encryption_matrix, []byte(to_decrypt), password)
		if string(result) != non_encrypted[i] {
			t.Errorf("Error! Expeteced %s, got %s", non_encrypted[i], string(result))
			if err != nil {
				log.Fatal(err.Error())
			}
		}
	}
}

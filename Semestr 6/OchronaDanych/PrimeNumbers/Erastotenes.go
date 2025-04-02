package main

import (
	"fmt"
)

// SieveOfEratosthenes returns all prime numbers up to n
func SieveOfEratosthenes(n int) []int {
	// Initialize a boolean array "isPrime[0..n]" and set all entries to true.
	// A value in isPrime[i] will finally be false if i is Not a prime, else true.
	isPrime := make([]bool, n+1)
	for i := range isPrime {
		isPrime[i] = true
	}

	// 0 and 1 are not prime numbers
	if n >= 0 {
		isPrime[0] = false
	}
	if n >= 1 {
		isPrime[1] = false
	}

	// Start from the smallest prime number, which is 2
	for p := 2; p*p <= n; p++ {
		// If isPrime[p] is not changed, then it is a prime
		if isPrime[p] == true {
			// Update all multiples of p as non-prime
			for i := p * p; i <= n; i += p {
				isPrime[i] = false
			}
		}
	}

	// Create a slice to store all the prime numbers
	var primes []int
	for p := 2; p <= n; p++ {
		if isPrime[p] == true {
			primes = append(primes, p)
		}
	}

	return primes
}

func main() {
	limit := 100 // Find primes up to 100
	primes := SieveOfEratosthenes(limit)
	fmt.Printf("Prime numbers up to %d are: %v\n", limit, primes)
}

package main

//Fibonacci Sequence

import (
	"log"
	"os"
)

func init() {
	log.SetOutput(os.Stdout)
}

func fib1(n int) int {
	log.Printf("* fib 1: %d", n)
	if n < 1 {
		return -1
	}
	if n == 1 || n == 2 {
		return 1
	}

	return fib1(n-1) + fib1(n-2)
}

func main() {
	log.Printf("--- fabonacci sequence --")
	var sum = fib1(10)
	log.Printf("# fabonacci sum: %d", sum)
}

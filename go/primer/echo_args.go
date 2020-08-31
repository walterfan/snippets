package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func init() {
	log.SetOutput(os.Stdout)
}

func main() {
	var s, sep = "", ""
	fmt.Println("* 1. s += sep + os.Args[i]")
	for i := 1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}

	fmt.Println(s)
	s = ""
	for _, arg := range os.Args[1:] {
		s += sep + arg
		sep = " "
	}
	fmt.Println("* 2. s += sep + arg")
	fmt.Println(s)

	fmt.Println("* 3. strings.Join(os.Args[1:]")
	fmt.Println(strings.Join(os.Args[1:], " "))

}

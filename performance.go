package main

import ( "fmt" 
		 "time" 
	   )

func main() {
	start := time.Now()
	sum := 0
	sum2 := 0
	sum3 := 0
	wait := time.Duration(10)*time.Second // Pause for 10 seconds
	for i := 0; i < 1500000000; i++ {
		sum += i
		for k := 0; k < 5; k++ {
			sum2 += k
			for n := 0; n < k; n++ {
				sum3 += n
			}
		}
	}
	fmt.Println(sum)
	fmt.Println(sum2)
	fmt.Println(sum3)
	executionTime := time.Since(start)
	fmt.Println(executionTime)
	time.Sleep(wait)
}

package main

import (
	"fmt"
)

func merge(a []int, start, mid, end int) {

	L := append([]int{}, a[start:mid]...)
	R := append([]int{}, a[mid:end]...)

	p1 := 0
	p2 := 0
	k := start

	for ; k < end && p1 < len(L) && p2 < len(R); k++ {
		if L[p1] <= R[p2] {
			a[k] = L[p1]
			p1++
		} else {
			a[k] = R[p2]
			p2++
		}
	}

	for ; p1 < len(L); p1++ {
		a[k] = L[p1]
		k++
	}

	for ; p2 < len(R); p2++ {
		a[k] = R[p2]
		k++
	}

}

func mergeSort(a []int, start, end int) {
	if start >= (end - 1) {
		return
	}

	mid := start + (end-start)/2
	mergeSort(a, 0, mid)
	mergeSort(a, mid, end)
	merge(a, 0, mid, end)
}

func MergeSort(a []int) {
	mergeSort(a, 0, len(a))
}

func main() {
	s := []int{2, 1}
	MergeSort(s)
	fmt.Print(s)
}

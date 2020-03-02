package main

import "testing"

func TestMergeSort(t *testing.T) {
	a := []int{0, 1, 0, -3, 6, 2, 1, 9}
	MergeSort(a)

	growing := true
	for i := 0; i < len(a); i++ {
		if i > 0 && a[i] < a[i-1] {
			growing = false
			break
		}
	}
	if !growing {
		t.Errorf("TestMergeSort failed.")
	}
}

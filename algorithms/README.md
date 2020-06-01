<div align="center">	
	<img src="./.github/algorithms.png" alt="algorithmsimg" width="50%"/>	
</div>

<div align="center">
	<h1>Algorithms 📝</h1>
</div>

<div align="center">	
	<a href="https://github.com/felipejsborges/cs50_challenges#cs50x-challenges-">Back to all projects</a>
</div>

### What is? 🤔
Basically, an algorithm is a sequence of instructions to solve problems, or a set of rules that precisely defines a sequence of operations. For example, in computation, we can use a language to set this rules/instructions to find a item on a list or sort them.
<hr>

### Which technologies were used? 💻
- C language
<hr>

### What algorithms I can find here? ✅

### Linear Search

**Pseudocode:**
```
repeat, starting at the first element
	if it is what we are looking for, stop. otherwise, move to the next element
```
**Scenario:**
- worst-case: we have to look through the entire array -> O(n)
- best-case: the target is the first element of the array -> Ω(1)<br>
<br>
<a href="https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#linearsearch.c">Test it!</a>
<hr>

### Binary Search

**Pseudocode:**
```
repeat until the (sub)array is of size 0
	calculate the middle pointo of the current (sub)array, if the target is at the middle, stop
	otherwise, if the target is less than the middle point, repeat changing the end point to be the previous element of the middle point
	otherwise, if the target is greater than the middle point, repeat changing the start point to be the next element of the middle point
```

**Scenario:**
- worst-case: we have to divide the array repeatedly to find the target until the middle point is the last possible division -> O(log n)
- best-case: the target is at the first middle point -> Ω(1)
<br>
<a href="https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#binarysearch.c">Test it!</a>
<hr>

### Bubble Sort

**Pseudocode:**
```
set swap counter to a non-zero value
repeat until the swap counter is 0
	reset the swap counter to 0
	look at each adjacent pair
		if two adjacent elements are not in order, swap them and add one to the swap counter
```

**Scenario:**
- worst-case: the array is in reverse order and we have to bubble each n elements and do it n times -> O(n²)
- best-case: the array is already sorted and we just moving line between sorted elements -> Ω(n)
<br>
<a href="https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#bubblesort.c">Test it!</a>
<hr>

### Insertion Sort

**Pseudocode:**
```
call the first element of the array "sorted"
Repeat util all elements are sorted
	Look at the next unsorted element and call it "sorted" by shifting the requisite number of elements
```

**Scenario:**
- worst-case: the array is in reverse order and we have to shift each n elements n positions each time -> O(n²)
- best-case: the array is already sorted and we just moving line between sorted elements -> Ω(n)
<br>
<a href="https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#insertionsort.c">Test it!</a>
<hr>

### Selection Sort

**Pseudocode:**
```
repeat until no unsorted elements remain
	search the unsorted part of the data to find the smallest value then swap it with the first element of the unsorted part
```

**Scenario:**
- worst-case: we have to iterate over each of n elements and must repeat this n times
- best-case: the same -> Θ(n²)
<br>
<a href="https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#selectionsort.c">Test it!</a>
<hr>

### Merge Sort

**Pseudocode:**
```
If only one item
  Return
Else
    Sort left half of items
    Sort right half of items
    Merge sorted halves
```

**Scenario:**
- worst-case: we have to iterate over each of n elements and must repeat this n times
- best-case: the same -> Θ(n log n)
<br>
Test coming soon!
<hr>

by Felipe Borges<br>
[LinkedIn](https://www.linkedin.com/in/felipejsborges) | [GitHub](https://github.com/felipejsborges)

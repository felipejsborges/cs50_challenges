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
#### Linear Search
**Pseudocode**
- repeat, starting at the first element
  - if it is what we are looking for, stop. otherwise, move to the next element 
**scenario - O(n), Ω(1)**
- worst-case: we have to look through the entire array
- best-case: the target is the first element of the array
**[Test it!](https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#linearsearch.c)**
<br>
##### Binary Search
**Pseudocode**
- repeat until the (sub)array is of size 0
  - calculate the middle pointo of the current (sub)array, if the target is at the middle, stop
  - otherwise, if the target is less than the middle point, repeat changing the end point to be the previous element of the middle point
  - otherwise, if the target is greater than the middle point, repeat changing the start point to be the next element of the middle point
**scenario - O(log n), Ω(1)**
- worst-case: we have to divide the array repeatedly to find the target until the middle point is the last possible division
- best-case: the target is at the first middle point
**[Test it!](https://repl.it/@FelipeBorges3/AdoredUnfitFilesize#binarysearch.c)**
<br>
#### Sorting
<hr>

by Felipe Borges<br>
[LinkedIn](https://www.linkedin.com/in/felipejsborges) | [GitHub](https://github.com/felipejsborges)

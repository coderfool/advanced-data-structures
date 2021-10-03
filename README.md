# Advanced Data Structures
Implementation of some commonly used advanced data structures in competitive programming

## 1. DisjointSet

Disjoint sets of integers

### Constructor: DisjointSet (int N)
Creates N disjoint sets of one element each from 0 to N - 1

### Methods

#### int root (int node)
Returns root element of the set to which `node` belongs. Also performs path compression.

#### void join (int node1, int node2)
Unions (by size) the disjoint sets of `node1` and `node2`. If they are already in the same set, it does nothing.

#### bool find (int node1, int node2)
Returns true if `node1` and `node2` are in the same set.

#### int size (int node)
Returns size of the set to which `node` belongs.

## 2. OrderStatisticTree

An augmented AVL tree of integers with duplicate elements allowed and additional operations to get order of a given value and selecting Kth smallest element

### Methods

#### void insert (int val)
Inserts `val` into the tree.

#### void remove (int val)
Removes one occurence of `val` from the tree. If not present, it does nothing.

#### int rank (int val)
Returns number of elements in the tree (including duplicates) that are strictly smaller than `val`.

#### int count (int val)
Returns frequency of `val` in the tree.

#### int size()
Returns number of elements in the tree including duplicates.

#### int size_distinct()
Returns number of distinct elements in the tree.

#### int min_value()
Returns minimum value in the tree. If tree is empty, it returns `INT_MIN`.

#### int max_value()
Returns maximum value in the tree. If tree is empty, it returns `INT_MAX`.

#### int select (int k)
Returns Kth smallest element, considering duplicate elements. If `k` is larger than size of tree, it returns `INT_MIN`.

#### int select_distinct (int k)
Returns Kth smallest element, only considering distinct elements. If `k` is larger than number of distinct elements in the tree, it returns `INT_MIN`.

## 3. SegmentTreeMin

Segment tree of integers that supports Range Minimum Query and range updates using lazy propagation. It uses 0-based indexing.

### Constructor: SegmentTreeMin (vector\<int\> arr)
Builds the segment tree from the vector `arr`.

### Methods

#### int minimum (int left, int right)
Returns minimum element from the range `arr[left]` to `arr[right]` (inclusive). If `left` is greater than `right`, it returns `INT_MAX`.

#### void set (int index, int val)
Sets the value of `arr[index]` to `val`.

#### void increment (int left, int right, int val)
Adds `val` to all the elements in the range `arr[left]` to `arr[right]` (inclusive). If `left` is greater than `right`, it does nothing.

## 4. Trie

Supports insertion, counting words and counting prefixes of strings only consisting of letters a-z.

### Constructor: Trie()
Creates an empty trie

### Methods

#### void insert (string str)
Inserts `str` into the trie.

#### int word_count (string word)
Returns frequency of `word` in the trie.

#### int prefix_count (string prefix)
Returns number of words that start with `prefix`.


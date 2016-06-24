/**
 * Created by daniel on 6/22/16.
 */
package edu.evansdaniel.collections;

public class MaxHeap {

    private static final int INIT_CAPACITY = 20;
    /**
     * array maintained with the max heap property
     */
    private HeapData[] heap;
    /**
     * represents the number of elements in the array
     */
    private int heapSize;

    private int numChildren = 2;

    /**
     * array is converted to a max heap by calling
     * buildMaxHeap
     *
     * @param a any array, ordered or unordered
     */
    public MaxHeap(HeapData[] a, int numChildren, int initSize) {
        validateArray(a);

        if (initSize < 0)
            initSize = INIT_CAPACITY;

        this.numChildren = numChildren;
        initHeap(a, initSize);

        this.heapSize = a.length;

        heap = buildMaxHeap(heap);
    }

    public MaxHeap(HeapData[] a, int numChildren) {
        validateArray(a);
        this.numChildren = numChildren;
        heapSize = a.length;
        initHeap(a, a.length * 2 + 1);
        heap = buildMaxHeap(heap);
    }


    public MaxHeap(int initSize, int numChildren) {
        if (initSize < 0)
            initSize = INIT_CAPACITY;

        this.numChildren = numChildren;
        heapSize = 0;
        heap = new HeapData[initSize];
    }

    public MaxHeap() {

        this(INIT_CAPACITY, 2);
    }

    /**
     * @param a       the array that is either being converted into a max heap,
     *                maintained as a max heap, or checked if it is a max heap
     * @param parentI the index of the parent node
     * @param leftI   the index of the left child node
     * @param rightI  the index of the right child node
     * @return the largest index of the node (either parent, right, or left  node)
     * with the highest priority
     */
    private static int largest(HeapData[] a, int heapSize, int parentI,
                               int leftI, int rightI) {
        int largest;
        // if the largest is the left child
        if (leftI < heapSize && a[leftI].priority > a[parentI].priority)
            largest = leftI;

            // otherwise set the largest to the parent
        else largest = parentI;

        // if the largest is the right child
        // 2nd check for out of bounds is necessary
        // b/c this if statement is not nested in the other one
        if (rightI < heapSize && a[rightI].priority > a[largest].priority)
            largest = rightI;

        // return index of parent, right child, or left child, whichever is largest
        return largest;
    }

    /**
     * check if a is a max heap
     *
     * @param a any HeapData array
     * @return true if a satisfies the max heap property, false if not
     */
    public boolean isMaxHeap(HeapData[] a) {

        for (int i = parent(a.length); i >= 0; --i) {
            int l = childD(i, 1);
            int r = childD(i, 2);

            int largest = MaxHeap.largest(a, a.length, i, l, r);
            if (largest != i)
                return false;
        }
        // if we get through the loop, that means that every parent node
        // a is >= to both its right and left child node, satisfying
        // the max heap property
        return true;
    }

    public void setHeapChildren(int numChildren) {
        this.numChildren = numChildren;
        buildMaxHeap(heap);
    }

    /**
     * Precondition: the array must be a binary max heap
     *
     * @param i the index of the parent node of leftChild(i)
     * @return index of left child node of the node heap[i]
     */
    // if binary heap, this gets the leftChild; else it is undefined
    public int leftChild(int i) {
        return numChildren * i + 1;
    }

    /**
     * the d child of the node at index p
     *
     * @param p index of the parent node
     * @param d the d child of the the node at index p
     * @return the index of child d of node at index p
     * <p>
     * precondition: d > 0 && d <= numChildren
     * precondition: p must be a vaild index in the array
     */
    public int childD(int p, int d) {
        if (d > numChildren)
            throw new IllegalArgumentException("d cannot be greater than" +
                    " numChildren: d=" + d + ", numChildren=" + numChildren);
        return p * numChildren + d;
    }

    /**
     * Precondition: the array must be a binary max heap
     *
     * @param i the index of the parent node of leftChild(i)
     * @return index of left child node of the node heap[i]
     */
    // if binary heap, this gets the rightChild; else it is undefined
    int rightChild(int i) {
        return (i + 1) * numChildren;
    }

    public int parent(int ci) {
        // the parent of nodes at indices 1 and 2 is the node at index 0
        if (ci <= numChildren)
            return 0;
        double p = ci / (numChildren * 1.0);
        // fixes a boundary case where ci == to the numChildren child of some parent
        // test it on a 3-ary heap with ci == 6 and this will make sense
        if (p == Math.floor(p))
            return (int) --p;
        else
            return (int) Math.floor(p);
    }

    private void validateArray(HeapData[] a) {
        if (a == null)
            throw new NullPointerException("a cannot be null");
    }

    private void initHeap(HeapData[] a, int initSize) {
        heap = new HeapData[initSize + a.length];
        System.arraycopy(a, 0, heap, 0, a.length);
    }

    public HeapData[] toArray() {
        HeapData[] retVal = new HeapData[heapSize];
        System.arraycopy(heap, 0, retVal, 0, heapSize);
        return retVal;
    }

    private HeapData[] buildMaxHeap(HeapData[] a) {
        // start at the last node that has a child
        int n = parent(heapSize);
        // loop through a[n - 1] nodes and ensure that
        // the max heap property is maintained
        for (int i = n; i >= 0; --i) {
            maxHeapify(i, a);
        }
        return a;
    }

    /**
     * sorts a binary max heap ascending
     * runs in O(n*lg(n)) time
     */
    public void heapSort() {
        int originalHeapSize = heapSize;
        /**
         * the below call to buildMaxHeap is only necessary if
         * if the array does not already satisfy the max heap property
         */
        // buildMaxHeap(heap);
        for (int i = heapSize - 1; i >= 0; --i) {
            swap(heap, 0, i);
            --heapSize;
            maxHeapify(0);
        }
        heapSize = originalHeapSize;
    }

    private int[] swap(HeapData[] a, int x, int y) {

        HeapData temp = a[x];
        a[x] = a[y];
        a[y] = temp;
        // return the indices if needed
        int[] tmp = {x, y};
        return tmp;
    }

    /**
     * inserts data into the heap while maintaining the max heap property
     * amortized cost is O(d) time, where d is the depth of the newly inserted node
     * occasionally it will cost O(n) when the array must be resized
     *
     * @param data data to insert
     */
    public void add(HeapData data) {
        if (heapSize == heap.length)
            ensureCapacity(heap.length * 2 + 1);
        // insert at heapSize index
        heap[heapSize] = data;
        // heapSize is kept 1 in front of the valid element range
        ++heapSize;
        // look at the definition to see what this does
        reheapify(heapSize - 1);
    }

    public void heapIncreaseKey(int index, int key) {
        if (key < heap[index].priority)
            throw new IllegalArgumentException("the current key: " +
                    heap[index].priority + " is greater than the specified key: " + key);

        heap[index].priority = key;
        while (index >= 0 && heap[parent(index)].priority < heap[index].priority) {
            swap(heap, index, parent(index));
            index = parent(index);
        }

    }

    public void reheapify(int index) {
        while (index >= 0 && heap[parent(index)].priority < heap[index].priority) {
            swap(heap, index, parent(index));
            index = parent(index);
        }
    }

    /**
     * removes all elements by reducing the valid element range (0 -> heapSize)
     * to (0 -> heapSize = 0)
     */
    public void clear() {
        heapSize = 0;
    }

    public boolean isEmpty() {

        return heapSize == 0;
    }

    /**
     * does not effect the member variables i.e. a const
     * function in C++
     *
     * @return the data value of the element that
     * used to be on top of the list
     */
    public int peak() {
        return heap[0].data;
    }

    /**
     * Removes and returns the element on the top of the heap
     * Costs O(h) time, where h is the max height of the tree.
     * Equivalently, it costs lg(n) time where n = heapSize
     *
     * @return the data value of the element that
     * used to be on top of the list
     */
    public int pop() {

        int top = peak();
        // swap the first element with the last
        // element in the array
        swap(this.heap, 0, heapSize - 1);
        // remove what used to be the first element
        // restore the max heap property
        reheapify(heapSize - 1);
        --heapSize;
        return top;
    }

    private void ensureCapacity(int capacity) {
        if (capacity <= heapSize)
            return;

        HeapData[] bigger = new HeapData[capacity];

        for (int i = 0; i < heapSize; ++i)
            bigger[i] = heap[i];

        heap = bigger;
    }

    private void maxHeapify(int i, HeapData[] a) {
        // maxCi is the index of the child with the greatest priority
        int maxCi = i;
        // on 1st iteration, ci is the index of the first child of
        // of the node at index i.
        // we can ++ci because the children of the node at index i are
        // sequentially ordered, this prevents any kind of call to childD
        for (int ci = childD(i, 1); ci < heapSize && ci <= childD(i, numChildren); ++ci) {
            if ((a[ci].priority > a[maxCi].priority))
                maxCi = ci;
        }

        // if the largest is not the parent
        if (maxCi != i) {
            swap(a, i, maxCi);
            maxHeapify(maxCi, a);
        }
    }

    private void maxHeapify(int i) {
        if (this.heap == null)
            throw new NullPointerException("heap is null");

        maxHeapify(i, this.heap);
    }

    private int largest(HeapData[] a, int parentI,
                        int leftI, int rightI) {
        return largest(a, heapSize, parentI, leftI, rightI);
    }
}

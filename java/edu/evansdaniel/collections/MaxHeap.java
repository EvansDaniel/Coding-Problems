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

    /**
     * array is converted to a max heap by calling
     * buildMaxHeap
     *
     * @param a any array, ordered or unordered
     */
    public MaxHeap(HeapData[] a, int initSize) {
        validateArray(a);

        if (initSize < 0)
            initSize = INIT_CAPACITY;

        initHeap(a, initSize);

        this.heapSize = a.length;

        heap = buildMaxHeap(heap);
    }

    public MaxHeap(HeapData[] a) {
        validateArray(a);
        heapSize = a.length;
        initHeap(a, a.length * 2 + 1);
        heap = buildMaxHeap(heap);
    }


    public MaxHeap(int initSize) {
        if (initSize < 0)
            initSize = INIT_CAPACITY;
        heapSize = 0;
        heap = new HeapData[initSize];
    }

    public MaxHeap() {
        this(INIT_CAPACITY);
    }

    /**
     * check if a is a max heap
     *
     * @param a any HeapData array
     * @return true if a satisfies the max heap property, false if not
     */
    public static boolean isMaxHeap(HeapData[] a) {

        for (int i = parent(a.length); i >= 0; --i) {
            int l = leftChild(i);
            int r = rightChild(i);

            int largest = MaxHeap.largest(a, a.length, i, l, r);
            if (largest != i)
                return false;
        }
        // if we get through the loop, that means that every parent node
        // a is >= to both its right and left child node, satisfying
        // the max heap property
        return true;
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
     * Precondition: the array must be a max heap
     *
     * @param i the index of the parent node of leftChild(i)
     * @return index of left child node of the node heap[i]
     */
    static int leftChild(int i) {
        return 2 * i + 1;
    }

    /**
     * Precondition: the array must be a max heap
     *
     * @param i the index of the parent node of leftChild(i)
     * @return index of left child node of the node heap[i]
     */
    static int rightChild(int i) {
        return (i + 1) * 2;
    }

    /**
     * Precondition: the array must be a max heap
     *
     * @param i index of a node that is a child of parent(i)
     * @return parent of heap[i]
     */
    static int parent(int i) {
        // the parent of nodes at indices 1 and 2 is the node at index 0
        if (i < 3)
            return 0;
        // if the node's priority is even
        if (i % 2 == 0)
            return (int) (Math.floor(i / 2.0) - 1);
            // if it's odd
        else
            return (int) Math.floor(i / 2.0);
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

        heap[heapSize] = data;
        ++heapSize;

        // call maxHeapify on the parent of the newly added node
        // then continue to call it on the parent of the parent of the
        // newly added node until the loop iterates to the root
        // this costs O(d), where d is the depth of the newly inserted node
        boolean done = false;
        for (int i = parent(heapSize - 1); i >= 0 && !done; i = parent(i)) {
            maxHeapify(i);
            if (i == 0)
                done = true;
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
     * <p>
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
        swap(this.heap, 0, heapSize);
        // remove what used to be the first element
        --heapSize;
        // restore the max heap property
        maxHeapify(0);
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

        // get indices of the left and right child
        int l = leftChild(i);
        int r = rightChild(i);

        int largest = MaxHeap.largest(a, heapSize, i, l, r);

        // if the largest is not the parent
        if (largest != i) {
            swap(a, i, largest);
            maxHeapify(largest, a);
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

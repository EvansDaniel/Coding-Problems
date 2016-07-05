import edu.evansdaniel.collections.HeapData;
import edu.evansdaniel.collections.MaxHeap;

/**
 * Created by daniel on 6/20/16.
 */
public class Main {

    public static void main(String[] args) {

        HeapData[] hd = new HeapData[5];
        System.out.println("before max heap: ");
        for (int i = 0; i < hd.length; i++) {
            hd[i] = new HeapData(i, (int) Math.round(Math.random() * 100));
            System.out.println(hd[i]);
        }
        System.out.println();

        // interestingly when MaxHeap(hd,1) is called
        // we get a sorted array descending
        MaxHeap heap = new MaxHeap(hd, 4);

        hd = heap.toArray();

        System.out.println("\nMax heap: ");
        for (int i = 0; i < hd.length; i++) {
            System.out.print(hd[i].getPriority() + "  ");
        }
        heap.setHeapChildren(2);


        heap.add(new HeapData(1, 1));

        hd = heap.toArray();

        System.out.println("\nMax heap after resetting children and adding element: ");
        for (int i = 0; i < hd.length; i++) {
            System.out.print(hd[i].getPriority() + "  ");
        }

        // heap sort still works because it is written in terms
        // of maxHeapify, so if maxHeapify works, heapSort works
        heap.heapSort();

        hd = heap.toArray();

        System.out.println("\nMax heap after heapSort: ");
        for (int i = 0; i < hd.length; i++) {
            System.out.print(hd[i].getPriority() + "  ");
        }
    }
}

import edu.evansdaniel.collections.HeapData;
import edu.evansdaniel.collections.MaxHeap;

/**
 * Created by daniel on 6/20/16.
 */
public class Main {

    public static void main(String[] args) {

        HeapData[] hd = new HeapData[10];
        System.out.println("before max heap: ");
        for (int i = 0; i < hd.length; i++) {
            hd[i] = new HeapData(i, i);
            System.out.print(hd[i].getPriority() + "    ");
        }
        System.out.println();

        MaxHeap heap = new MaxHeap(hd);

        hd = heap.toArray();

        System.out.println("Max heap: ");
        for (int i = 0; i < hd.length; i++) {
            System.out.print(hd[i].getPriority() + "  ");
        }
        System.out.println();

        System.out.println(MaxHeap.isMaxHeap(hd));

        heap.add(new HeapData(3, 8));

        System.out.println(MaxHeap.isMaxHeap(heap.toArray()));

        heap.pop();

        for (int i = 0; i < heap.toArray().length; i++) {
            System.out.print(heap.toArray()[i].getPriority() + "  ");
        }
        System.out.println();
        System.out.println(MaxHeap.isMaxHeap(heap.toArray()));

//        MaxHeap.isMaxHeap(heap.toArray());


    }
}

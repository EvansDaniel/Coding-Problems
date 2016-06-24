import edu.evansdaniel.collections.HeapData;
import edu.evansdaniel.collections.MaxHeap;

/**
 * Created by daniel on 6/20/16.
 */
public class Main {

    public static void main(String[] args) {

        HeapData[] hd = new HeapData[15];
        System.out.println("before max heap: ");
        for (int i = 0; i < hd.length; i++) {
            hd[i] = new HeapData(i, (int) Math.round(Math.random() * 100));
        }
        System.out.println();

        // interestingly when MaxHeap(hd,1) is called
        // we get a sorted array descending
        MaxHeap heap = new MaxHeap(hd, 4);

        hd = heap.toArray();

        System.out.println("Max heap: ");
        for (int i = 0; i < hd.length; i++) {
            System.out.print(hd[i].getPriority() + "  ");
        }
        heap.setHeapChildren(2);

        hd = heap.toArray();

        System.out.println("Max heap: ");
        for (int i = 0; i < hd.length; i++) {
            System.out.print(hd[i].getPriority() + "  ");
        }
    }
}

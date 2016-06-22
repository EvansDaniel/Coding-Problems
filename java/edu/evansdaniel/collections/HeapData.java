package edu.evansdaniel.collections;

public class HeapData {
    int data;
    int priority;

    public HeapData(int data, int priority) {
        this.data = data;
        this.priority = priority;
    }

    public int getPriority() {
        return priority;
    }
}

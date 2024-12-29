#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

class MinHeap {
public:
    int *harr;     // Pointer to array of elements in heap
    int capacity;  // Maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

    // Constructor
    MinHeap(int cap) {
        heap_size = 0;
        capacity = cap;
        harr = new int[cap];
    }

    // Destructor
    ~MinHeap() {
        delete[] harr;
    }

    // Utility function to swap two elements
    void swap(int *x, int *y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    // Function to get index of parent
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Function to get index of left child
    int left(int i) {
        return 2 * i + 1;
    }

    // Function to get index of right child
    int right(int i) {
        return 2 * i + 2;
    }

    // To heapify a subtree with the root at index i
    void MinHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        // Check if left child is smaller than root
        if (l < heap_size && harr[l] < harr[smallest]) {
            smallest = l;
        }

        // Check if right child is smaller than smallest so far
        if (r < heap_size && harr[r] < harr[smallest]) {
            smallest = r;
        }

        // If smallest is not root
        if (smallest != i) {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);  // Recursively heapify the affected subtree
        }
    }

    // Extract the minimum element (root)
    int extractMin() {
        if (heap_size == 0) {
            return INT_MAX; // Heap is empty
        }

        // Store the minimum value, and remove it from heap
        int root = harr[0];
        if (heap_size > 1) {
            harr[0] = harr[heap_size - 1]; // Move the last element to root
            MinHeapify(0); // Call minHeapify to restore the heap property
        }
        heap_size--;
        return root;
    }

    // Get the minimum element (root)
    int getMin() {
        if (heap_size == 0) {
            return INT_MAX; // Heap is empty
        }
        return harr[0];
    }

    // Delete a key at index i
    void deleteKey(int i) {
        // Replace the element at index i with a very small value
        // to move it to the root, then extract the minimum
        decreaseKey(i, INT_MIN);
        extractMin();
    }

    // Insert a new key
    void insertKey(int k) {
        if (heap_size == capacity) {
            cout << "Overflow: Could not insertKey\n";
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)] > harr[i]) {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    // Function to decrease the value of key at index i to new_val
    void decreaseKey(int i, int new_val) {
        harr[i] = new_val;
        while (i != 0 && harr[parent(i)] > harr[i]) {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
};

int main() {
    // Create a MinHeap with capacity of 11
    MinHeap h(11);

    // Insert some keys
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);  // Delete key at index 1
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);

    // Extract the minimum element (should be the root)
    cout << "Extracted Min: " << h.extractMin() << endl;

    // Get the current minimum (should be the new root)
    cout << "Current Min: " << h.getMin() << endl;

    // Delete the key at index 2 (value 15)
    h.deleteKey(2);

    // Print the current minimum element
    cout << "Current Min after delete: " << h.getMin() << endl;

    return 0;
}

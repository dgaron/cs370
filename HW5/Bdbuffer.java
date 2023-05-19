
public class Bdbuffer {

    // Constructor
    //
    // Accepts one int indicating the size of the buffer
    public Bdbuffer(int size) {
        buffer = new char[size];
        this.size = size;
        in = 0;
        out = 0;
    }

    // Synchronized method for inserting an item into the buffer
    public synchronized void insertItem(int id, char item) {
        // If buffer is full, suspend Producer thread
        while (this.isFull()) {
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        // Insert item into the buffer
        buffer[in] = item;
        System.out.printf("\033[0;4mProducer %3d inserted %c at index %3d at time\033[0;0m %s%n",
                          id, item, in, Invoker.getTime());
        // Increment in counter
        in = (in + 1) % size;
        // Wake all threads: possible condition change from empty to !empty
        notifyAll();
    }

    // Synchronized method for removing an item from the buffer
    public synchronized char getItem(int id) {
        // If buffer is empty, suspend Consumer thread
        while (this.isEmpty()) {
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        // Obtain item from the buffer
        char item = buffer[out];
        System.out.printf("Consumer %3d consumed %c at index %3d at time %s%n",
                          id, item, out, Invoker.getTime());
        // Increment out counter
        out = (out + 1) % size;
        // Wake all threads: possible condition change from full to !full
        notifyAll();
        return item;
    }

    public boolean isEmpty() {
        return in == out;
    }

    public boolean isFull() {
        return (in + 1) % size == out;
    }

    private char[] buffer;
    private int size;
    private int in;
    private int out;

}

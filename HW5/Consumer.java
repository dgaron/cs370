import java.util.Arrays;

public class Consumer implements Runnable {

    public Consumer(Bdbuffer buffer, int count, int id) {
        //Assign values to the variables
        this.buffer = buffer;
        this.count = count;
        this.id = id;
        characters = new StringBuilder();
    }

    @Override
    public void run() {
        for (int i = 0; i < count; ++i) {
            char letter = buffer.getItem(id);
            characters.append(letter);
        }
    }

    public String getConsumedStr() {
        return sortString();
    }

    private String sortString() {
        String str = characters.toString();
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }

    private Bdbuffer buffer;
    private int count;
    private int id;
    private StringBuilder characters;
}

import java.util.Random;
import java.util.Arrays;

public class Producer implements Runnable {

    public Producer(Bdbuffer buffer, int count, int id, int seed) {
        //Assign values to the variables
        this.buffer = buffer;
        this.count = count;
        this.id = id;
        rand = new Random(seed);
        characters = new StringBuilder();
    }

    @Override
    public void run() {
        for (int i = 0; i < count; ++i) {
            char letter = (char)(rand.nextInt(26) + 'a');
            buffer.insertItem(id, letter);
            characters.append(letter);
        }
    }

    public String getProducedStr() {
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
    private Random rand;
    private StringBuilder characters;

}

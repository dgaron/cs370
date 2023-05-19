import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Arrays;

class Invoker {
    public static void main(String[] args) throws InterruptedException {
        // Ensure the proper number of arguments have been passed
        if (args.length != 1) {
            // Print usage message if user enters wrong number of arguments
            System.out.println("Usage: java Invoker seed");
            return;
        }

        // Seed for random number generation
        int seed;
        // Convert string arg[0] to int
        try {
            seed = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invoker: error parsing seed argument. Please enter an integer.");
            return;
        }

        // Populate int array with random numbers
        // 0: Buffer size
        // 1: Number of items
        // 2: Number of Producers
        // 3: Number of Consumers
        int[] randomNumbers = newRandoms(seed);
        // Print content of randomNumbers to console
	    printRandoms(randomNumbers);

        // Create the buffer
        Bdbuffer buffer = new Bdbuffer(randomNumbers[0]);

        // Create Producers
        Producer[] producers = new Producer[randomNumbers[2]];
        Thread[] pThreads = new Thread[randomNumbers[2]];
        for (int i = 0; i < randomNumbers[2]; ++i) {
            // IDs start at 1
            int id = i + 1;
            // Divide number of items among Producers
            int numItems = randomNumbers[1] / randomNumbers[2];
            // Add remainder of items to last Producer
            if (id == randomNumbers[2]) {
                numItems += randomNumbers[1] % randomNumbers[2];
            }
            producers[i] = new Producer(buffer, numItems, id, seed);
            pThreads[i] = new Thread(producers[i]);
            pThreads[i].start();   
        }

        // Create Consumers
        Consumer[] consumers = new Consumer[randomNumbers[3]];
        Thread[] cThreads = new Thread[randomNumbers[3]];
        for (int i = 0; i < randomNumbers[3]; ++i) {
            // IDs start at 1
            int id = i + 1;
            // Divide number of items amont consumers
            int numItems = randomNumbers[1] / randomNumbers[3];
            // Add remainder of items to last Consumer
            if (id == randomNumbers[3]) {
                numItems += randomNumbers[1] % randomNumbers[3];
            }
            consumers[i] = new Consumer(buffer, numItems, id);
            cThreads[i] = new Thread(consumers[i]);
            cThreads[i].start();
        }

        // Wait for Producers to finish
        // Assemble string of characters produced
        StringBuilder produced = new StringBuilder();
        for (int i = 0; i < randomNumbers[2]; ++i) {
            pThreads[i].join();
            produced.append(producers[i].getProducedStr());
        }

        // Wait for Consumers to finish
        // Assemble string of characters consumed
        StringBuilder consumed = new StringBuilder();
        for (int i = 0; i < randomNumbers[3]; ++i) {
            cThreads[i].join();
            consumed.append(consumers[i].getConsumedStr());
        }     

        // Sort strings
        String pString = sortString(produced);
        String cString = sortString(consumed);

        // Verify that Producer and Consumer strings are the same
        if (pString.equals(cString)) {
            System.out.println("The sorted Produced and Consumed strings are the same " +
                               "as shown: " + pString);
        } else {
            System.out.println("Error: the strings do not match");
            System.out.printf("Producer string: %s%n", pString);
            System.out.printf("Consumer string: %s%n", cString);
        }
    }

    // Takes a StringBuilder and returns a sorted string of the contents
    private static String sortString(StringBuilder characters) {
        String str = characters.toString();
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }


    // Generates an array of random numbers conforming to the specified bounds
    private static int[] newRandoms(int seed) {
        Random rand = new Random(seed);
        int[] randomNumbers = new int[4];
        randomNumbers[0] = rand.nextInt(6) + 5;     // Buffer size [5,10]
        randomNumbers[1] = rand.nextInt(11) + 10;   // Number of items [10,20]
        randomNumbers[2] = rand.nextInt(4) + 2;     // Number of consumers [2,5]
        randomNumbers[3] = rand.nextInt(4) + 2;     // Number of producers [2,5]
        return randomNumbers;
    }

    // Prints the randomly generated ints
    private static void printRandoms(int[] randomNumbers) {
        System.out.println("[Invoker] Buffer Size: " + randomNumbers[0]);
        System.out.println("[Invoker] Total Items: " + randomNumbers[1]);
        System.out.println("[Invoker] No. of Producers: " + randomNumbers[2]);
        System.out.println("[Invoker] No. of Consumers: " + randomNumbers[3]);
    }

    //Call this function from your producer or your consumer to get the time stamp to be displayed
    public static String getTime() {
        Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
        Instant time = Instant.now(offsetClock);
        String timeString = time.toString();
        timeString = timeString.replace('T', ' ');
        timeString = timeString.replace('Z', ' ');
        return(timeString);
    }
}

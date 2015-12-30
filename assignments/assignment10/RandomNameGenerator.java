 package assignment10;

 import java.util.Random;
 import java.util.ArrayList;
 import java.util.Collections;

 public final class RandomNameGenerator {
     private final int ASCII_A = 65;
     private final int ASCII_a = 97;
     private final int ASCII_SPACE = 32;
     private final int ALPHABET_SIZE = 26;
     private final int MIN_NAME_LENGTH = 14; // arbitrary choice

     public String getRandomName() {
         Random random = new Random();
         byte[] bytes = new byte[24];
         String s;
         random.nextBytes(bytes);
         // convert the bytes to 97..126 to make lower case letters
         for (int j = 0; j < bytes.length; j++) {
             bytes[j] = (byte)(Math.abs(bytes[j])%ALPHABET_SIZE + ASCII_a);
         }
         // set string total length to range 14..24
         int length = MIN_NAME_LENGTH + random.nextInt(10);
         // put a space somewhere from 4 to length - 4
         int spaceLocation = 4 + random.nextInt(length-8);
         bytes[spaceLocation] = ASCII_SPACE; // insert a space
         bytes[0] -= (ASCII_a-ASCII_A); // make first letter upper case
         bytes[spaceLocation+1] -= (ASCII_a-ASCII_A); // letter after space uppercase
         s = new String(bytes);
         return s.substring(0,length);
     }

     public static void main(String[] args) {
         ABubbleSortUtility obj = new ABubbleSortUtility();
         obj.test();        
         runTimingTest();
     }
     
     public static void runTimingTest() {
         ArrayList<String> names = new ArrayList<String>();
         ArrayList<String> namesCopy = new ArrayList<String>();
         RandomNameGenerator helper = new RandomNameGenerator();
         ABubbleSortUtility obj = new ABubbleSortUtility();
         // in a for loop make 10000 Strings using 
         // helper.getRandomName, add each one to names and namesCopy
         for(int i = 0; i < 10000; i++) {
        	 names.add(helper.getRandomName());
        	 namesCopy.add(helper.getRandomName());
            } 
         System.out.println("\n------------\nTime Testing");
         long start = System.currentTimeMillis();
         obj.aBubbleSort(names);
         long end = System.currentTimeMillis();
         System.out.println("Bubble Sort took " + (end-start) + " milliseconds");

         start = System.currentTimeMillis();
         Collections.sort(namesCopy);
         end = System.currentTimeMillis();
         System.out.println("Merge Sort took " + (end-start) + " milliseconds");
         // this is Tim sort if you are using Java 8.
     }
 }
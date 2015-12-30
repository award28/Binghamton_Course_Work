You must show this lab to the TA at the end of class to receive a grade.

All classes must be in package lab08.

Write a class BankAccount with:

    A private String name
    A private int balance
    A constructor which accepts and sets both
    Getters for both fields

Write a class Bank with:

    A private List<BankAccount> accounts
    A constructor which instantiates accounts to an empty ArrayList (ArrayList a class that implements the List interface)

Write a class LookupMap with:

    a private Map<String, Integer> map, instantiated as a HashMap.
        a Map<String, Integer> is an interface describing a way to associate Strings with Integers. The TA will explain this
        feel free to lookup the javadocs for it

This lab will be about writing a computer that can do some simple tasks with storage (like a hard drive). Our hard drive will be similar to how programming languages work. We associate a named variable with an integer. For example we want our computer to be able to execute code like this

a = 0
for i=0 to 5
  a += i

Here we would need to create a variable a, a variable i, and a way to loop with a starting value and an ending point. We also want our computer to be able to work with different types of hard drives (different types of storage). If we had a Computer class with a field representing the hard drive, how could we let it be anything which could possibly operate as some type of storage? The answer is interfaces. We will create a Storage interface which any class can implement if it wants to act as a hard drive.

Copy this interface to your project:

package lab08;

public interface Storage {

  /**
   * Stores the value associated with ID
   * If ID is already associated to some value, that value is overwritten
   * If no ID exists in storage, new association is made
   * @param ID the name of the variable to store with
   * @param value the value of the ID variable
   */
    public void store(String ID, int value);

  /**
   * Loads the value associated with ID
   * @param ID the name of the variable to load
   * @return the value associated with ID if an association exists,
   *         otherwise -1
   */
  public int load(String ID);

  /**
   * Erases the association entry for ID
   * Does nothing if no association exists
   * @param ID the name of the variable to erase
   */
  public void erase(String ID);
}

Now alter your Bank and your LookupMap classes to implement Storage (add an implements Storage phrase after the class declaration). Like this: public class LookupMap implements Storage
{ ... }. This is straightforward for the LookupMap class but using a bank as a hard drive is a little more tricky and will require more code.

Now let's create a Computer class that can use storage.

Copy this class to your project:

package lab08;

import java.util.function.*;

public class Computer {
    public Storage storage;

    public Computer(Storage s) {
        this.storage = s;
    }

    public int for_loop(String i, int start, String v, IntBinaryOperator f, IntPredicate stop) {
        this.storage.store(i, start);
        while (true) {
            int tmp = this.storage.load(v);
            int ii = this.storage.load(i);
            tmp = f.applyAsInt(ii, tmp);
            this.storage.store(v, tmp);
            if (!stop.test(ii)) {
                break;
            }
            this.storage.store(i, ii + 1);
        }
        return this.storage.load(v);
    }

    public void setVariable(String s, int i) {
        this.storage.store(s, i);
    }

    public int getVariable(String s) {
        return this.storage.load(s);
    }
}

Note that the type of storage is Storage. By not hard-coding a certain class as the type of storage, we are freed from constraining our code to one implementation. Instead, we constrain any class that wants to act as a storage mechanism to implement the 3 methods in the Storage interface.

Now let's test your hard drives.

Copy this class to your project and run it

package lab08;

public class Driver {
    public static void compare(String expected, String actual) {
        String prefix = expected.equals(actual) ? "-" : "!";
        System.out.println(prefix + " Got: " + actual + " | Expected: " + expected);
    }
    public static void compare(int expected, int actual) {
        compare(expected+"", actual+"");
    }

    public static void testWith(Storage s) {
        Computer c = new Computer(s);

        System.out.println("* Trying simple variables");
        c.setVariable("a", 0);
        c.setVariable("b", 1);

        /**/
        compare(0, c.getVariable("a"));
        compare(1, c.getVariable("b"));
        /**/

        System.out.println("* Trying for loop");
        c.for_loop("i", 0, "a", (a, b) -> a + b, i -> i < 5);

        /**/
        compare(15, c.getVariable("a"));

    }

    public static void main(String[] args) {
        System.out.println("Trying Map Computer");
        testWith(new LookupMap());
        System.out.println("Trying Bank Computer");
        testWith(new Bank());
    }
}

Read the code and make sure you understand what is happening. Look how the for_loop function is working. Now, create a while_loop function, similar to the for_loop and test it within the testWith method inside Driver.

Show your code to the TA to receive a grade.

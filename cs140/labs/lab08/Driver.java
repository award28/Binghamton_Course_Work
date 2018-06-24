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

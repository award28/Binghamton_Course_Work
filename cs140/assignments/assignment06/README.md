Assignment 06
===

Due Wednesday October 14, 11:59 pm

This assignment will have code in the package `assignment06`.

Copy over your code from Asssignment 2, the classes Course, Offering, and MyClass.

Use this code for the QPointsCalculator:

```java
package assignment06;
import java.util.HashMap;
import java.util.Map;
public class QPointsCalculator {
	public static double points(String letterGrade, int credits) {
		Map<String, Double> map = new HashMap<>();
		map.put("A", 4.0);
		map.put("A-", 3.7);
		map.put("B+", 3.3);
		map.put("B", 3.0);
		map.put("B-", 2.7);
		map.put("C+", 2.3);
		map.put("C", 2.0);
		map.put("C-", 1.7);
		map.put("D", 1.0);
		map.put("P", 0.0);
		map.put("F", 0.0);
		if(map.containsKey(letterGrade.toUpperCase())) {
			return map.get(letterGrade.toUpperCase())*credits;
		} else {
			throw new IllegalArgumentException("Invalid Letter Grade");
		}
	}
}
```

Copy the class `Person` and the enum `Gender` from Assignment 1. 

Question 1. Make a class Student with fields Person `student` and an `ArrayList<MyClass> myClasses` instantiated as new
empty ArrayList. As before, provide a constructor with just a Person as a parameter. Rewrite the `addToMyClass` method 
that simply uses the `add` method to add a MyClass object to the end of `myClasses`.

Question 2. Now just work on the version 2 `GPA` method, this time the loops traverse the ArrayList. Note that the way
to sort an ArrayList of Comparable elements is to use Collections.sort(list).

Question 3. Write a JUnit test for `GPA` in Question 2 [JUnit was covered in Lab on October 8]

Question 4. Go back to Assignment 3 and copy over BankAccount. Rewrite the BankAccountGroup so that the field 
is an ArrayList<BankAccount>, instantiated as an empty ArrayList. The method `getBalance(int i)` returns 0 if there
is no `i-th` element in the list, otherwise the balance of the `i-th` account. 
The method `removeAccount(int i)` calls the `remove(i)` on the ArrayList field if `i` 
is an index in the ArrayList and returns the balance of the `i-th` account. 
If that `i` is not in range, simply return 0, without throwing an exception.
Create the method `public void addAccount(BankAccount acc)` that adds `acc` to the ArrayList if `acc` is not null and
does nothing if `acc` is null. Do NOT implement `insertAccount` and `countNonNull`. 
Provide the method `evenUpAccounts`. There is no need to worry about null BankAccounts since we are preventing their 
insertion. 

Question 5. Write a JUnit test for `evenUpAccounts`

Question 6. Write a javadoc comment for `evenUpAccounts`.
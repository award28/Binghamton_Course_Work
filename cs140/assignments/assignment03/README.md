**Due Friday the 25th**

Here is the textbook's first BankAccount version

```java
package assignment03;
/**
   A bank account has a balance that can be changed by 
   deposits and withdrawals.
*/
public class BankAccount
{  
   private double balance;

   /**
      Constructs a bank account with a zero balance.
   */
   public BankAccount()
   {   
      balance = 0;
   }

   /**
      Constructs a bank account with a given balance.
      @param initialBalance the initial balance
   */
   public BankAccount(double initialBalance)
   {   
      balance = initialBalance;
   }

   /**
      Deposits money into the bank account.
      @param amount the amount to deposit
   */
   public void deposit(double amount)
   {  
      balance = balance + amount;
   }

   /**
      Withdraws money from the bank account.
      @param amount the amount to withdraw
   */
   public void withdraw(double amount)
   {   
      balance = balance - amount;
   }

   /**
      Gets the current balance of the bank account.
      @return the current balance
   */
   public double getBalance()
   {   
      return balance;
   }
}
```

Make a class `BankAccountGroup`

Private field: array of BankAccount

Constructor: takes an array of BankAccounts as parameter that is used to set the value of the field. In test cases you are allowed to pass null, an empty array, an array of any number of accounts, some of which could be null

Methods: 

`public double getBalance(int i)` to get the i-th account balance (this method will throw NullPointerException if the array is null 
or that account is null).

`public double removeAccount(int i)` returns balance in i-th account if that account is not null and then 
sets that index to null in the array element at index `i` to null. 
If that element was already null, return 0 (this method will throw NullPointerException if the array is null). 

`public void insertAccount(int i, BankAccount ac)` if i-th index in the array is null, set it to ac, otherwise 
`throw new IllegalArgumentException("Trying to replace existing account")` (this method will throw NullPointerException if the array is null).

`public int countNonNull()` returns the number of non-null accounts in the array (this method will throw NullPointerException if the array is null).

`public void evenUpAccounts()` find the average of all the non-null accounts in the array and deposit or withdraw from each non-null account 
to give them all the average balance. Do nothing if all accounts are null or the array is null.

`public double depositLowest(double amount)` find the account with lowest balance (first one if there is a tie) 
and deposit the amount in that one, return 0. return `amount` if all the accounts are null (this method will throw NullPointerException 
if the array is null).

`public double withdrawHighest(double amount)` find the account with highest balance (first one if there is a tie) and withdraw 
the amount from that one, return 0. Throw `new IllegalArgumentException("No account with sufficient funds")` 
if amount is larger than any account balance or all accounts are null (this method will throw NullPointerException if the array is null).

`public void depositInParts(double amount)` if the number `N` of non-null accounts is 0, do nothing. Otherwise divide the `amount` into `N` equal parts 
and repeatedly deposit `amount/N` to the first acount that has the currently smallest balance UNTIL THE amount HAS BEEN 
USED UP, THAT MEANS YOU REPEAT `N` TIMES. NOTE: use methods already created above and observe 
that after each deposit into an account, the account with the smallest balance is likely to change (this method will throw NullPointerException 
if the array is null).

Add this code to BakAccountGroup to make it easier to see what is in the `group` array

```java
	public String toString() {
		StringBuilder bldr = new StringBuilder();
		if(group == null) bldr.append("null\n");
		else if(group.length == 0) bldr.append("empty\n");
		else for(int i = 0; i < group.length; i++)
			bldr.append("account " + i + ((group[i]==null?" is null\n":
				" has balance " + group[i].getBalance() + "\n")));
		return bldr.toString();
	}
```

Write a test class `Driver` with a main method that contains a series of test cases, which verify correct results for all the different behaviors 
that these methods can exhibit. I AM EXPECTING 40 to 50 tests in the main method (5 test arrays, 6 methods for each one and some methods 
need more that one test). Give each one a number in the test message. Here are some examples showing the 
numbering 1.1, 4.1 and 4.2.

```java
package assignment03;

public class Driver {

	public static void main(String[] args) {
		BankAccount[] arr1 = null;
		BankAccount[] arr2 = {};
		BankAccount[] arr3 = {null, null, null, null, null};
		BankAccount[] arr4 = {
				new BankAccount(200),
				new BankAccount(300),
				new BankAccount(250),
				new BankAccount(300),
				new BankAccount(200)
				};
		BankAccount[] arr5 = {
				null, null,
				new BankAccount(200),
				new BankAccount(300),
				null,
				new BankAccount(250),
				new BankAccount(300),
				null, null, 
				new BankAccount(200),
				null};

// test all of the following for all the groups above
//		public double removeAccount(int i)
//		public void insertAccount(int i, BankAccount ac)
//		public int countNonNull()
//		public void evenUpAccounts()
//		public double withdrawHighest(double amount)
//		public void depositInParts(double amount)

// For arr1 
		BankAccountGroup test1 = new BankAccountGroup(arr1);		
		try {
			test1.removeAccount(0);
		} catch (NullPointerException e) {
			System.out.println("1.1. As expected, null pointer exception");
		} 
		// similar test for the other 5 methods

// In the tests that follow, you can cheat about setting up the exceptions:
// Try it and see what happens first.
// If your test throws an exception, just go back and put in a try and
// catch around that line and then a println saying it was expected.
// It's like someone screwing up and then saying "I meant to do that!"
// Other exceptions are
// ArrayIndexOutOfBoundsException and IllegalArgumentException
		
// For arr4
		BankAccountGroup test4 = new BankAccountGroup(arr4);
		System.out.println("Before:");
		System.out.println(test4);
		test4.removeAccount(2);
		System.out.println("After:");
		System.out.println(test4);
		System.out.println("4.1. As expected the account[2] was set "
				+ "to null");

		try {
			test4.removeAccount(arr4.length);			
		} catch(ArrayIndexOutOfBoundsException e) {
			System.out.println("4.2. As expected there is no bounds "
					+ "check in the code of the method");			
		}

	}
}
```
# Lab 02

All classes in this lab must be in package lab02.

In this lab we will learn about arrays and ways to access and modify what they hold.

A data structure can be put into an array using the `type[]` syntax. For example

```java
int[] myArray = new int[3];
```

declares a variable named myArray as an array of `int`s and a length of 3 (there are 3 `int`s inside `myArray`).

To initialize an array when declaring it you can use the following syntax:

```java
int[] myArray = {1, 2, 3};
```

To set elements of an array use the `[]` syntax:

```java
myArray[0] = 2;
myArray[1] = 3;
myArray[2] = 4;
```

If you try to set an element that doesn't exist you will get an error:

```java
myArray[10] = 2;
Exception in thread "main" java.lang.ArrayIndexOutOfBoundsException: 10
```

You'll notice we declared myArray to be type `int []`. This means each element of myArray must be of type `int`.
What do you think will happen if we do something like:
```java
myArray[2] = true;
```
If you try and compile this with javac, you should see the error: `error: incompatible types: boolean cannot be converted to int`
This is telling us we cannot make an element of `myArray` to be `true` (a `boolean`) when we declared `myArray` with type `int []`.

To access elements of an array use the same `[]` syntax:

```java
int firstElement = myArray[0];
```

To access each element of an array and do something with it you can use a for-loop:

```java
for (int i = 0; i < myArray.length; ++i) {
	// do something with element myArray[i]
}
```

An example might be printing out every element.

Create a class ArrayTesting and make a main method that creates an
array of 10 `int`s and prints them out.

When that is done make another loop that finds the sum of the elements
in the array. After the loop print this sum out. For this you will
need an aggregation variable declared before the loop.

Create an Account class with the following code.

```java
package lab02;

public class Account {
	public int money;

	public Account(int money) {
		this.money = money;
	}

	public void deposit(int toDeposit) {
		this.money += toDeposit;
	}
}
```

Create a class AccountTester and in the main method create an array of
10 `Account`s. Set each element to a new `Account` with any money
amount.

There is another way to loop over an array:

```java
Account[] array = ...
for (Account a : array) {
	// do something with element a
}
```

To print out every element:

```java
Account[] array = ...
for (Account a : array) {
	System.out.println(a);
}
```

This is called an enhanced for-loop, sometimes called a for-each loop.

Write a static method that takes an `Account` array as an argument and finds the `Account` in that array with the most money in it. It should then return that `Account`.
Do
this twice (write two methods), once with a normal for-loop and once with an enhanced
for-loop. You should test this code in the main method of AccountTester.

Now do the same as above but each method should find the `Account`
with the minimum money in the array. Also test this in your main
method.

Arrays are useful containers to hold our objects that we can then pass to methods to be manipulated.
Write a static method that takes an `Account` array as its first argument and an `int amount` as its second argument. The method
should deposit `amount` into each `Account` in the array. Do this with whichever for-loop style you prefer.
Test this code in the main method of the AccountTester.

Copy and paste the following into AccountTester's main method and run it:

```java
Account[] arr = null;
for (int i = 0; i < arr.length; ++i) {
	System.out.println(arr[i]);
}
```

You should get an error. So what happened? `null` is a 'nothing
value'. If you have an array set to null then you cannot find its
length, you cannot index it, you cannot do anything with it. If you
try then you will get an error.

To fix this you should always check for `null`:

```java
if (arr != null) {
	for (int i = 0; i < arr.length; ++i) {
		System.out.println(arr[i]);
	}
}
```

Show the TA your work when you are done.
NOTICE: Friday will have a quiz on declaring arrays and accessing their elements.
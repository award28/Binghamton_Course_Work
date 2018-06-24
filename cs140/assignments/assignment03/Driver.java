package assignment03;

public class Driver {

    public static void main(String[] args) {
	int i;

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
//      public double removeAccount(int i)
//      public void insertAccount(int i, BankAccount ac)
//      public int countNonNull()
//      public void evenUpAccounts()
//      public double withdrawHighest(double amount)
//      public void depositInParts(double amount)



// For arr1
	System.out.println("\n***********arr1***********\n");
        BankAccountGroup test1 = new BankAccountGroup(arr1);

        try {
        	test1.removeAccount(0);
		System.out.println(test1);
        } catch (NullPointerException e) {
        	System.out.println("1.1. As expected, null pointer exception");
        }
 	
	try {
		test1.insertAccount(0, arr1[0]);
		System.out.println(test1);
	} catch (NullPointerException e) { 
		System.out.println("1.2. as expected, null pointer exception");
	}
	try {
		System.out.println("Number of non null accounts ---> " + test1.countNonNull());
		System.out.println(test1);
	} catch (NullPointerException e) { 
		System.out.println("1.3. as expected, null pointer exception");
	}
	try {
		test1.evenUpAccounts();
		System.out.println(test1);
	} catch (NullPointerException e) { 
		System.out.println("1.4. as expected, null pointer exception");
	}
	try {
		test1.withdrawHighest(100);
		System.out.println(test1);
	} catch (NullPointerException e) { 
		System.out.println("1.5. as expected, null pointer exception");
	}
	try {
		test1.depositLowest(100);
		System.out.println(test1);
	} catch (NullPointerException e) { 
		System.out.println("1.6. as expected, null pointer exception");
	}
	try {
		test1.depositInParts(100);
		System.out.println(test1);
	} catch (NullPointerException e) { 
		System.out.println("1.7. as expected, null pointer exception");
	}

// For arr2
	System.out.println("\n***********arr2***********\n");
	BankAccountGroup test2 = new BankAccountGroup(arr2);
    
        try {
		for(i=0; i < arr2.length; i++){
			test2.removeAccount(i);
		}
		System.out.println(test2);	
        } catch (NullPointerException e) {
        	System.out.println("2.1. As expected, null pointer exception");
        }
 	
	try {
		for(i=0; i < arr2.length; i++){
			test2.insertAccount(i, arr2[i]);
		}
	System.out.println(test2);
	} catch (NullPointerException e) { 
		System.out.println("2.2. as expected, null pointer exception");
	}
	try {
		System.out.println("Number of non null accounts ---> " + test2.countNonNull());
		System.out.println(test2);
	} catch (NullPointerException e) { 
		System.out.println("2.3. as expected, null pointer exception");
	}
	try {
		test2.evenUpAccounts();
		System.out.println(test2);
	} catch (NullPointerException e) { 
		System.out.println("2.4. as expected, null pointer exception");
	}
	try {
		//test2.withdrawHighest(100);
		System.out.println(test2);
	} catch (NullPointerException e) { 
		System.out.println("2.5. as expected, null pointer exception");
	}
	try {
		//test2.depositLowest(100);
		System.out.println(test2);
	} catch (NullPointerException e) { 
		System.out.println("2.6. as expected, null pointer exception");
	}
	try {
		//test2.depositInParts(100);
		System.out.println(test2);
	} catch (NullPointerException e) { 
		System.out.println("2.7. as expected, null pointer exception");
	}

// For arr3
	System.out.println("\n***********arr3***********\n");
	BankAccountGroup test3 = new BankAccountGroup(arr3);
	
	try {
		for(i=0; i < arr3.length; i++){
			test3.removeAccount(i);
		}
		System.out.println(test3);	
        } catch (NullPointerException e) {
        	System.out.println("3.1. As expected, null pointer exception");
        }
 	
	try {
		for(i=0; i < arr3.length; i++){
			test3.insertAccount(i, arr3[i]);
		}
	System.out.println(test3);
	} catch (NullPointerException e) { 
		System.out.println("3.2. as expected, null pointer exception");
	}
	try {
		System.out.println("Number of non null accounts ---> " + test3.countNonNull());
		System.out.println(test3);
	} catch (NullPointerException e) { 
		System.out.println("3.3. as expected, null pointer exception");
	}
	try {
		test3.evenUpAccounts();
		System.out.println(test3);
	} catch (NullPointerException e) { 
		System.out.println("3.4. as expected, null pointer exception");
	}
	try {
		test3.withdrawHighest(100);
		System.out.println(test3);
	} catch (NullPointerException e) { 
		System.out.println("3.5. as expected, null pointer exception");
	}
	try {
		test3.depositLowest(100);
		System.out.println(test3);
	} catch (NullPointerException e) { 
		System.out.println("3.6. as expected, null pointer exception");
	}
	try {
		test3.depositInParts(100);
		System.out.println(test3);
	} catch (NullPointerException e) { 
		System.out.println("3.7. as expected, null pointer exception");
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
	System.out.println("\n***********arr4***********\n");
        BankAccountGroup test4 = new BankAccountGroup(arr4);

	
	try {
			test4.removeAccount(2);
		System.out.println(test4);	
        } catch (NullPointerException e) {
        	System.out.println("4.1. As expected, null pointer exception");
        }
 	
	try {
			test4.insertAccount(2, arr4[2]);
		
	System.out.println(test4);
	} catch (NullPointerException e) { 
		System.out.println("4.2. as expected, null pointer exception");
	}
	try {
		System.out.println("Number of non null accounts ---> " + test4.countNonNull());
		System.out.println(test4);
	} catch (NullPointerException e) { 
		System.out.println("4.3. as expected, null pointer exception");
	}
	try {
		test4.evenUpAccounts();
		System.out.println(test4);
	} catch (NullPointerException e) { 
		System.out.println("4.4. as expected, null pointer exception");
	}
	try {
		test4.withdrawHighest(100);
		System.out.println(test4);
	} catch (NullPointerException e) { 
		System.out.println("4.5. as expected, null pointer exception");
	}
	try {
		test4.depositLowest(100);
		System.out.println(test4);
	} catch (NullPointerException e) { 
		System.out.println("4.6. as expected, null pointer exception");
	}
	try {
		test4.depositInParts(100);
		System.out.println(test4);
	} catch (NullPointerException e) { 
		System.out.println("4.7. as expected, null pointer exception");
	}



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


// For arr5
	System.out.println("\n***********arr5***********\n");
	BankAccountGroup test5 = new BankAccountGroup(arr5);

		
	try {
		test5.removeAccount(3);
		System.out.println(test5);	
        } catch (NullPointerException e) {
        	System.out.println("5.1. As expected, null pointer exception");
        }
 	
	try {
		test5.insertAccount(3, arr5[3]);
		System.out.println(test5);
	} catch (NullPointerException e) { 
		System.out.println("5.2. as expected, null pointer exception");
	}
	try {
		System.out.println("Number of non null accounts ---> " + test5.countNonNull());
		System.out.println(test5);
	} catch (NullPointerException e) { 
		System.out.println("5.3. as expected, null pointer exception");
	}
	try {
		test5.evenUpAccounts();
		System.out.println(test5);
	} catch (NullPointerException e) { 
		System.out.println("5.4. as expected, null pointer exception");
	}
	try {
		test5.withdrawHighest(100);
		System.out.println(test5);
	} catch (NullPointerException e) { 
		System.out.println("5.5. as expected, null pointer exception");
	}
	try {
		test5.depositLowest(100);
		System.out.println(test5);
	} catch (NullPointerException e) { 
		System.out.println("5.6. as expected, null pointer exception");
	}
	try {
		test5.depositInParts(100);
		System.out.println(test5);
	} catch (NullPointerException e) { 
		System.out.println("5.7. as expected, null pointer exception");
	}



    }
}

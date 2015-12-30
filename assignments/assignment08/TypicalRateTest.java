package assignment08;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;

public class TypicalRateTest {

	@Test
	public void test() {		
		ArrayList<BankAccount> accounts1 = new ArrayList<BankAccount>();
		ArrayList<BankAccount> accounts2 = new ArrayList<BankAccount>();
		ArrayList<BankAccount> accounts3 = new ArrayList<BankAccount>();
		ArrayList<BankAccount> accounts4 = null; //Null Account
		ArrayList<BankAccount> accounts5 = new ArrayList<BankAccount>(); //Empty Account
		
		accounts1.add(new SavingsAccount(5,1));
		accounts1.add(new SavingsAccount(10,2));
		accounts1.add(new SavingsAccount(15,3));
		accounts1.add(new SavingsAccount(20,4));
		accounts1.add(new SavingsAccount(25,5));
		
		accounts2.add(new CheckingAccount(5,1));
		accounts2.add(new CheckingAccount(10,2));
		accounts2.add(new SavingsAccount(15,3));
		accounts2.add(new SavingsAccount(20,4));
		accounts2.add(new SavingsAccount(25,5));
		
		accounts3.add(new CheckingAccount(5,1));
		accounts3.add(null);
		accounts3.add(new SavingsAccount(15,3));
		accounts3.add(null);
		accounts3.add(new SavingsAccount(25,5));
		
		accounts1.get(0).deposit(500);
		accounts1.get(1).deposit(600);
		accounts1.get(2).deposit(700);
		accounts1.get(3).deposit(800);
		accounts1.get(4).deposit(900);
		
		accounts2.get(0).deposit(500);
		accounts2.get(1).deposit(600);
		accounts2.get(2).deposit(700);
		accounts2.get(3).deposit(800);
		accounts2.get(4).deposit(900);
		
		accounts3.get(0).deposit(500);
		accounts3.get(2).deposit(700);
		accounts3.get(4).deposit(900);
		
		TypicalRate test1 = new TypicalRate(accounts1);
		TypicalRate test2 = new TypicalRate(accounts2);
		TypicalRate test3 = new TypicalRate(accounts3);
		TypicalRate test4 = new TypicalRate(accounts4);
		TypicalRate test5 = new TypicalRate(accounts5);
		
		assertEquals(3, test1.report().getId());
		assertEquals(4, test2.report().getId());
		assertEquals(3, test3.report().getId());
		assertEquals(null, test4.report());
		assertEquals(null, test5.report());
		
	}
}

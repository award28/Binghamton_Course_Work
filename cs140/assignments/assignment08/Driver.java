package assignment08;

import java.util.ArrayList;

public class Driver {
	
	public static void main(String[] args) {
		ArrayList<BankAccount> accounts = new ArrayList<BankAccount>();
		BankAccountGroup group = new BankAccountGroup();
		
		accounts.add(new SavingsAccount(5,1));
		accounts.add(new SavingsAccount(10,2));
		accounts.add(new SavingsAccount(15,3));
		accounts.add(new SavingsAccount(20,4));
		accounts.add(new SavingsAccount(25,5));
		accounts.add(new CheckingAccount(35,6));
		accounts.add(new CheckingAccount(30,7));
		accounts.add(new SavingsAccount(45,8));
		accounts.add(new SavingsAccount(50,9));
		accounts.add(new SavingsAccount(75,10));
		accounts.add(new CheckingAccount(60,11));
		accounts.add(null);
		accounts.add(new SavingsAccount(80,12));
		accounts.add(null);
		accounts.add(new SavingsAccount(85,3));
		
		accounts.get(0).deposit(500);
		accounts.get(1).deposit(600);
		accounts.get(2).deposit(700);
		accounts.get(3).deposit(800);
		accounts.get(4).deposit(900);	
		accounts.get(5).deposit(1500);
		accounts.get(6).deposit(1600);
		accounts.get(7).deposit(1700);
		accounts.get(8).deposit(1800);
		accounts.get(9).deposit(1900);
		accounts.get(10).deposit(2500);
		accounts.get(12).deposit(2700);
		accounts.get(14).deposit(2900);
		
		for(BankAccount b : accounts) {
			group.addAccount(b);
		}
		
		//Expected
		System.out.println("What is expected when calling doReport in BankAccountGroup:" +
				"\n" + new MinBalance(accounts).report().getId() +
				"\n" + new MaxBalance(accounts).report().getId() +
				"\n" + new ClosestToAverage(accounts).report().getId() +
				"\n" + new TypicalRate(accounts).report().getId() +
				"\nWhat the actual returned values are:");
		//Actual
		group.doReport();
		
		//Updating account information
		group.doUpdate();
		
		System.out.println("\nPrinting the updated account info:\n" + group);
	}
}

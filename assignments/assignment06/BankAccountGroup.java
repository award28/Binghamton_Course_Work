package assignment06;

import java.util.ArrayList;

public class BankAccountGroup {
	ArrayList<BankAccount> account = new ArrayList<BankAccount>();
	
	public double getBalance(int i) {
		double balance;
		if(account.size() != i) {
			balance = account.get(i).getBalance();
		}
		else {
			balance = 0;
		}
		return balance;
	}

	public double removeAccount(int i) {
		double balance;
		if( i < account.size()) {
			balance = account.get(i).getBalance();
			account.remove(i);
		}
		else {
			balance = 0;
		}
		return balance;
	}
	public void addAccount(BankAccount acc){
		if(acc != null) {
			account.add(acc);
		}
	}
	
	/** Description of evenUpAccounts()
	*
	* Adds all of the accounts balances for a total balance. This total is then
	* used to find the average. Depending on the accounts balance, money is 
	* either withdrawn or deposited to match the average.
	*
	*@author	Austin Ward
	*@version	1.0 Build 1 Oct 14, 2015.
	*/
	public void evenUpAccounts() {
		double totalBalance = 0;
		double average;
		double difference;

		for(int i = 0; i < account.size(); i++) {
			if(account.size() != 0) {
				totalBalance += account.get(i).getBalance();
			}
		}
		
		average = totalBalance / account.size();

		for(int i = 0;  i < account.size(); i++) {
			if(account.size() != 0) {
				if(account.get(i).getBalance() > average) {
					difference = account.get(i).getBalance() - average;
					account.get(i).withdraw(difference);
				}
				else if (account.get(i).getBalance() < average) {
					difference = average - account.get(i).getBalance();
					account.get(i).deposit(difference);
				}
			}
		}
	}
}

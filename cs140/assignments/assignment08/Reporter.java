package assignment08;

import java.util.ArrayList;

public abstract class Reporter {
	private ArrayList<BankAccount> accounts;
	
	public Reporter(ArrayList<BankAccount> accounts) {
		this.accounts = accounts;
	}

	protected ArrayList<BankAccount> getAccounts() {
		return accounts;
	}
	
	public BankAccount report(){ 
		return null;
	}
}
package assignment08;
/**
   A bank account has a balance that can be changed by 
   deposits and withdrawals.
 */
public abstract class BankAccount {  
	private double balance; 
	private int id; 

	/**
      Constructs a bank account with a zero balance.
      @param i the id of the account      
	 */
	public BankAccount(int i) {  
		balance = 0;
		id = i;
	}

	/**
      Constructs a bank account with a given balance.
      @param initialBalance the initial balance
      @param i the id of the account      
	 */
	public BankAccount(double initialBalance, int i) {  
		balance = initialBalance;
		id = i;
	}
	
	/**
      Deposits money into the bank account.
      @param amount the amount to deposit
	 */
	public void deposit(double amount) {  
		balance = balance + amount;
	}

	/**
      Withdraws money from the bank account.
      @param amount the amount to withdraw
	 */
	public void withdraw(double amount) {  
		balance = balance - amount;
	}

	/**
      Gets the current balance of the bank account.
      @return the current balance
	 */
	public double getBalance() {  
		return balance; 
	}

	/**
    Gets the id of the bank account.
    @return the id of the account
	 */
	public int getId() {  
		return id; 
	}
	
	/**
      Transfers money from the bank account to another account
      @param amount the amount to transfer
      @param other the other account
	 */
	public void transfer(double amount, BankAccount other) {  
		withdraw(amount);
		other.deposit(amount);
	}
}
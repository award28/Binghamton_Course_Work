package assignment08;
/**
   An account that earns interest at a fixed rate.
 */
public class SavingsAccount extends BankAccount {  
	private double interestRate;

	/**
      Constructs a bank account with a given interest rate.
      @param rate the interest rate
      @param id the id of the account
	 */
	public SavingsAccount(double rate, int id) {  
		super(id);
		interestRate = rate;
	}

	/**
      Adds the earned interest to the account balance.
	 */
	public void addInterest() {
		double interest = getBalance() * interestRate / 100;
		deposit(interest); 
	}
	
	public double getInterestRate() {
		return interestRate;
	}
}
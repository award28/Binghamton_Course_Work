package assignment08;

import java.util.ArrayList;

public class TypicalRate extends Reporter {

	public TypicalRate(ArrayList<BankAccount> accounts) {
		super(accounts);
	}
	
	public SavingsAccount report() {
		ArrayList<BankAccount> accounts = getAccounts();
		BankAccount retVal = null;
		double average = 0;
		int numOfSavings = 0;
		if(accounts != null && accounts.size() > 0) {	
			for(BankAccount b : accounts) {
				if(b != null && b instanceof SavingsAccount){
					average += ((SavingsAccount)b).getInterestRate();
					numOfSavings++;
				}
			}
			average = average / numOfSavings;
			
			for(BankAccount b : accounts) {
				if(b != null && b instanceof SavingsAccount) {
					if (retVal == null || 
						Math.abs(((SavingsAccount)retVal).getInterestRate() - average) > 
						Math.abs(((SavingsAccount)b).getInterestRate() - average)) {
						retVal = (SavingsAccount)b;
					}
				}
			}
		}
		return (SavingsAccount)retVal;
	}
}
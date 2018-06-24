package assignment08;

import java.util.ArrayList;

public class ClosestToAverage extends Reporter {

	public ClosestToAverage(ArrayList<BankAccount> accounts) {
		super(accounts);
	}
	
	public BankAccount report(){
		ArrayList<BankAccount> accounts = getAccounts();
		BankAccount retVal = null;
		double average = 0;
		int numNonNull = 0;
		if(accounts != null && accounts.size() > 0) {	
			for(BankAccount b : accounts) {
				if(b != null){
					average += b.getBalance();
					numNonNull++;
				}
			}
			average = average / numNonNull;
			
			for(BankAccount b : accounts) {
				if(b != null) {
					if (retVal == null || Math.abs(retVal.getBalance() - average) > Math.abs(b.getBalance() - average)) 
						retVal = b;
				}
			}
		}
		return retVal;
	}
}

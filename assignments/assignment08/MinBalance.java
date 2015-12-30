package assignment08;

import java.util.ArrayList;

public class MinBalance extends Reporter {

	public MinBalance(ArrayList<BankAccount> accounts) {
		super(accounts);
	}

	public BankAccount report(){
		ArrayList<BankAccount> accounts = getAccounts();
		BankAccount retVal = null;
		if(accounts != null && accounts.size() > 0) {
			for(BankAccount b : accounts) {
				if(b != null) {
					if (retVal == null || retVal.getBalance() > b.getBalance()) 
						retVal = b;
				}
			}
		}
		return retVal;
	}
}
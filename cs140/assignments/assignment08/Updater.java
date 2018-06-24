package assignment08;

import java.util.ArrayList;

public class Updater {
	public static void update(ArrayList<BankAccount> accounts) {
		for(BankAccount b : accounts) {
			if(b != null && b instanceof SavingsAccount) {
				((SavingsAccount)b).addInterest();
			}
			if(b != null && b instanceof CheckingAccount) {
				((CheckingAccount)b).deductFees();
			}
		}
	}
}
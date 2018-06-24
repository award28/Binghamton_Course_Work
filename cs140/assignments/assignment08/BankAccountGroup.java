package assignment08;

import java.util.ArrayList;

public class BankAccountGroup {
	private ArrayList<BankAccount> accounts = new ArrayList<>();
	public void addAccount(BankAccount acc) {
		accounts.add(acc);
	}

	public void doReport() {
		Reporter[] reports = new Reporter[4];
		reports[0] = new MinBalance(accounts);
		reports[1] = new MaxBalance(accounts);
		reports[2] = new ClosestToAverage(accounts);
		reports[3] = new TypicalRate(accounts);
		for(Reporter r : reports) {
			BankAccount acc = r.report();
			if(acc != null) {
				System.out.println(acc.getId());
			} else {
				System.out.println("null");
			}
		}
	}
	
	public void doUpdate() {
		Updater.update(accounts);
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for(BankAccount b : accounts) {
			sb.append((b==null)?"null\n":
				b.getId() + ": " + b.getBalance() + "\n");
		}
		return sb.toString();
	}
}
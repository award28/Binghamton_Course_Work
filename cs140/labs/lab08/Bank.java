package lab08;

import java.util.List;
import java.util.ArrayList;

public class Bank implements Storage {
	private List<BankAccount> accounts;
	
	public Bank() {
		accounts = new ArrayList<BankAccount>();
	}

	
}

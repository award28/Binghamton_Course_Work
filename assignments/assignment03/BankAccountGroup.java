package assignment03;

public class BankAccountGroup {
	private BankAccount[] account;

	public BankAccountGroup(BankAccount[] account) {
		this.account = account;
	}
	
	public double getBalance(int i) {
		double balance;
		balance = account[i].getBalance();
		return balance;
	}

	public double removeAccount(int i) {
		double balance;
		if( account[i] != null && account.length != 0) {
			balance = account[i].getBalance();
			account[i] = null;
		}
		else {
			balance = 0;
		}
		return balance;
	}

	public void insertAccount(int i, BankAccount ac) {
		if(account[i] ==  null && account.length != 0) {
			account[i] = ac;
		}
		else {
			throw new IllegalArgumentException("Trying to replace existing account");
		}
	}

	public int countNonNull() {
		int nonNullCount = 0;

		for(int i = 0; i < account.length; i++) {
			if(account[i] != null && account.length != 0) {
				nonNullCount++;
			}
		}
		
		return nonNullCount;
	}

	public void evenUpAccounts() {
		double totalBalance = 0;
		double average;
		double difference;

		for(int i = 0; i < account.length; i++) {
			if(account[i] != null && account.length != 0) {
				totalBalance += account[i].getBalance();
			}
		}
		
		average = totalBalance / countNonNull();

		for(int i = 0;  i < account.length; i++) {
			if(account[i] != null && account.length != 0) {
				if(account[i].getBalance() > average) {
					difference = account[i].getBalance() - average;
					account[i].withdraw(difference);
				}
				else if (account[i].getBalance() < average) {
					difference = average - account[i].getBalance();
					account[i].deposit(difference);
				}
			}
		}
	}

	public double depositLowest(double amount) {
		double lowestAccount = account[0].getBalance();
		int lowestAccountIndex = 0;
		if(account.length != 0){
			for(int i = 0;  i < account.length; i++) {
				if(account[i].getBalance() < lowestAccount){
					lowestAccount = account[i].getBalance();
					lowestAccountIndex = i;
				}
			}
				account[lowestAccountIndex].deposit(amount);
		}
		return 0;
	}

	public double withdrawHighest(double amount){
		double highestAccount = account[0].getBalance();
		int highestAccountIndex = 0;
		if(account.length != 0){
			for(int i = 0;  i < account.length; i++) {
				if(account[i].getBalance() > highestAccount){
					highestAccount = account[i].getBalance();
					highestAccountIndex = i;
				}
			}
			if(amount < account[highestAccountIndex].getBalance()) {
				account[highestAccountIndex].withdraw(amount);
			}
			else {
				throw new IllegalArgumentException("No account with sufficient funds");
			}
		}
		return 0;
	}

	public void depositInParts(double amount) {
		int N = countNonNull();
		if(account.length != 0){
			if(N != 0){
				for(int i = 0; i < N; i++){
					depositLowest(amount/N);
				}
			}
		}
	}

	public String toString() {
        StringBuilder bldr = new StringBuilder();
        if(account == null) bldr.append("null\n");
        else if(account.length == 0) bldr.append("empty\n");
        else for(int i = 0; i < account.length; i++)
            bldr.append("account " + i + ((account[i]==null?" is null\n":
                " has balance " + account[i].getBalance() + "\n")));
        return bldr.toString();
    }
}

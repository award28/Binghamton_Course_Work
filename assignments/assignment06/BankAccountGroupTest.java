package assignment06;

import static org.junit.Assert.*;

import org.junit.Test;

public class BankAccountGroupTest {

	@Test
	public void test() {
		BankAccount acc1 = new BankAccount(400);
		BankAccount acc2 = new BankAccount(300);
		BankAccount acc3 = new BankAccount(200);
		BankAccount acc4 = new BankAccount(500);
		BankAccount acc5 = new BankAccount(600);
		

        BankAccountGroup test1 = new BankAccountGroup();
        
        test1.addAccount(acc1);
        test1.addAccount(acc2);
        test1.addAccount(acc3);
        test1.addAccount(acc4);
        test1.addAccount(acc5);
        
        test1.evenUpAccounts();
        
        assertEquals(400, test1.getBalance(0), 0.1);
        assertEquals(400, test1.getBalance(1), 0.1);
        assertEquals(400, test1.getBalance(2), 0.1);
        assertEquals(400, test1.getBalance(3), 0.1);
        assertEquals(400, test1.getBalance(4), 0.1);
	}

}

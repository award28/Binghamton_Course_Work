package lab01;

/**
 * A simulation class that tests some loanees
 */
public class Simulation {
	public static void main(String[] args) {
		Loanee l1 = new Loanee(100);
		boolean l1cp = l1.canPayLoan(100, 0, 10);
		System.out.println(l1cp);
		Loanee l2 = new Loanee(100);
		boolean l2cp = l2.canPayLoan(100, 0.1, 1);
		System.out.println(l2cp);
		Loanee l3 = new Loanee(110);
		boolean l3cp = l3.canPayLoan(100, 0.1, 1);
		System.out.println(l3cp);
	}
}

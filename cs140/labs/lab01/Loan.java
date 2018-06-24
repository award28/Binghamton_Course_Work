package lab01;

/**
 * A class representing a loan
 */
public class Loan {
	private double amount;
	private double interestRate;

	/**
	 * Construct a loan object given a loan amount
	 * and an interest rate
	 *
	 * @param amt the amount of the loan
	 * @param ir the interest rate
	 */
	public Loan(double amt, double ir) {
		this.amount = amt;
		this.interestRate = ir;
	}

	/**
	 * Return the amount to be paid back on the loan
	 * given a number of years that have passed
	 *
	 * @param years the amount of years that have passed
	 *
	 * @return the amount due after `years`
	 */
	public double getAmountDue(int years) {
		double amt = this.amount;
		for (int i = 0; i < years; ++i) {
			amt += amt * this.interestRate;
		}
		return amt;
	}
}

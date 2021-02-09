//package lab1.comp6231.org;

public abstract class BankAccount {

	protected static int accNum;
	protected double balance;
	protected static int serialNum = 0;
	
	/** Default constructor 
	 * 
	 */
	public BankAccount()
	{
        // TODO
		this.balance = getBalance();
		accNum = getAccNum()+1;
		
		if(this.balance >= 0.0 && accNum > 0) {
			System.out.println("Balance for Account "+accNum+" is "+this.balance);
		}
		else {
			System.out.println("Invalid balance and Account Number");
		}
		
	    // check the balance
        // check the account Number
	}
	
	/** Overloaded constructor
	 */
	public BankAccount( double startBalance) throws Exception
	{
        // TODO
		this.balance = startBalance;
	    //deposit the balance
        //check the account number
	}
	
	/** accessor for balance
	 * 
	 */
	public double getBalance()
	{
		return balance;
        // TODO
        // get the balance
    }
	
	/* accessor for account number
	 * 
	 */
	public int getAccNum()
	{
		return accNum;
	}
	
	/** Deposit amount to account
	 * 
	 */
	public void deposit( double amount ) throws Exception
	{
        // TODO
		if(amount >= 0.0) {
			balance += amount;
		}
		else
			throw new Exception("Invalid Amount");
        // deposit amount of money, if it is legal/valid amount
	}
	
	/** withdraw amount from account
	 * 
	 */
	public void withdraw( double amount ) throws Exception
	{
		if(amount >= 0.0 && amount <= balance)
			balance -= amount;
		else
			throw new Exception("Insufficient Balance");
	}

	/**Override toString()
	 *
	 */
	public String toString()
	{
		return "The balance is of the "+accType()+" "+accNum+" is "+balance;
		// TODO: print the balance amount for specific account type displaying the account number.
	}
	
	public abstract void applyComputation();
	public abstract String accType();
}

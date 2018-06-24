package assignment09;

import java.util.ArrayList;

/**
   This program demonstrates the measurable BankAccount and Country classes.
*/
public class Measurable09Tester
{
   public static void main(String[] args)
   {
	  ArrayList<Measurable09> accounts = new ArrayList<Measurable09>();
	  accounts.add(new BankAccount09(0));
      accounts.add(new BankAccount09(10000));
      accounts.add(new BankAccount09(2000));

      double averageBalance = Measurable09.average(accounts);
      System.out.println("Average balance: " + averageBalance);
      System.out.println("Expected: 4000");

      ArrayList<Measurable09> countries = new ArrayList<Measurable09>();
      countries.add(new Country09("Uruguay", 176220));
      countries.add(new Country09("Thailand", 513120));
      countries.add(new Country09("Belgium", 30510));

      double averageArea = Measurable09.average(countries);
      System.out.println("Average area: " + averageArea);
      System.out.println("Expected: 239950");
      
      BankAccount09 maximumBalance = (BankAccount09) Measurable09.maximum(accounts);
      Country09 maximumArea = (Country09) Measurable09.maximum(countries);
      
      System.out.println("Maximum balance: " + maximumBalance.getBalance());
      System.out.println("Expected: 10000");
      
      System.out.println("Maximum area: " + maximumArea.getArea());
      System.out.println("Expected: 513120");
      
      BankAccount09[] accountUniform ={ new BankAccount09(25), 
						    		  	new BankAccount09(50), 
						    		  	new BankAccount09(75)
						    		  };
      
      Country09[] countriesUniform ={ new Country09("Australia", 29700), 
						    		  new Country09("China", 37055), 
						    		  new Country09("Russia", 66066)
									 };
      
      boolean checkAccounts;
      boolean checkCountries;
      
      for(int i = 0; i < accounts.size() || i < countries.size(); i++) {
	      checkAccounts = Measurable09.uniform(accountUniform, accounts.get(i).getClass());
	      checkCountries = Measurable09.uniform(countriesUniform, countries.get(i).getClass());
      
	      System.out.println("Accounts boolean:" + checkAccounts);
	      System.out.println("Expected: true");
	      System.out.println("Countries boolean:" + checkCountries);
	      System.out.println("Expected: true");
      }
      
      ArrayList<Measurable09> bothObjectType = new ArrayList<Measurable09>();
      
      bothObjectType.add(new BankAccount09(25));
      bothObjectType.add(new BankAccount09(75));
      bothObjectType.add(new Country09("Australia", 29700));
      bothObjectType.add(new Country09("Russia", 66066));

      double averageBoth = Measurable09.average(bothObjectType);
      Measurable09 maximumBoth = Measurable09.maximum(bothObjectType);
      
      System.out.println("Average test for ArrayList with both Objects: " + averageBoth);
      System.out.println("Maximum test for ArrayList with both Objects: " + ((Country09) maximumBoth).getArea());
      
      boolean checkbothObjectType;
      
      System.out.println("-Checking ArrayList with both Object Type against an accounts array-");
      
      for(int i = 0; i < bothObjectType.size(); i++) {
    	  checkbothObjectType = Measurable09.uniform(accountUniform, bothObjectType.get(i).getClass().getClass());
	      
	      if(i < 2) {
		      System.out.println("Accounts boolean:" + checkbothObjectType);
		      System.out.println("Expected: true");
	      }
	      else {
	    	  System.out.println("Countries boolean:" + checkbothObjectType);
		      System.out.println("Expected: false");
	      }
      }     
   }
}

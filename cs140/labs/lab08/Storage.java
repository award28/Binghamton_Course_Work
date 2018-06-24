package lab08;

public interface Storage {

  /**
   * Stores the value associated with ID
   * If ID is already associated to some value, that value is overwritten
   * If no ID exists in storage, new association is made
   * @param ID the name of the variable to store with
   * @param value the value of the ID variable
   */
    public void store(String ID, int value);

  /**
   * Loads the value associated with ID
   * @param ID the name of the variable to load
   * @return the value associated with ID if an association exists,
   *         otherwise -1
   */
  public int load(String ID);

  /**
   * Erases the association entry for ID
   * Does nothing if no association exists
   * @param ID the name of the variable to erase
   */
  public void erase(String ID);
}

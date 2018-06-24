package cs572;

/** For checking type compatibility, we can check for equals or isSubType()
 *  as necessary.
 */
interface TypeI {

   /** Return true iff this is a sub-type of other; i.e., this may be assigned
   *  to other.
   */
  boolean isSubType(TypeI other);
}

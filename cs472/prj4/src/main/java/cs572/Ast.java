package cs572;

import org.antlr.v4.runtime.Token;
import static org.antlr.v4.runtime.IntStream.UNKNOWN_SOURCE_NAME;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/** Abstract class representing all Asts.  All Asts will have a
 *  line number and column number giving the approximate source position
 *  of the root of the Ast.  All concrete AST's will have a rubric
 *  specifying the category of the AST.
 *
 *  All AST's can be pretty-printed in a simple-minded way to a string.
 */
abstract class Ast implements TypedI {
  private final String _rubric;
  private final Position _position;
  private List<Ast> _kids;
  private TypeI _type;

  /** Constructor which uses token t to approximate source position. */
  Ast(String rubric, Token t) {
    this(rubric, new Position(t));
  }

  /** Constructor which uses some sub-Ast t to approximate source position. */
  Ast(String rubric, Ast t) {
    this(rubric, t.getPosition());
  }

  /** Constructor which uses specific line number lineN and column number
   *  colN as position.
   */
  Ast(String rubric, Position position) {
    _rubric = rubric; _position = position;
    _kids = new ArrayList<>();
    _type = BasicType.NIL;
  }

  /* Return approx. line number:col number of Ast in source. */
  public Position getPosition() { return _position; }

  /** Return category which identifies the kind of this Ast. */
  public String getRubric() { return _rubric; }

  public TypeI getType() { return _type; }
  void setType(TypeI type) { _type = type; }

  /** Add kid as child of this AST. */
  protected void addKid(Ast kid) { _kids.add(kid); }

  /** Return kid at index i (starting with 0) of this AST. */
  protected Ast getKid(int i) { return _kids.get(i); }

  /** Return total # of kids in this AST. */
  public int getNKids() { return _kids.size(); }

  protected List<Ast> getKids() { return Collections.unmodifiableList(_kids); }

  /** Surgery routine: replace i'th kid (assume i in [0, getNKids()]). */
  public void setKid(int i, Ast t) { _kids.set(i, t); }

  /** Surgery routine: replace all kids */
  public void setKids(List<Ast> kids) { _kids = new ArrayList<>(kids); }

  /** Output error message specified by format and args to stderr.
   *  Precede error message by the position of this AST and
   *  follow it by a newline.
   */
  protected void error(String format, Object...args) {
    CountingErrorListener.INSTANCE.error(_position.toString() + ": " +  format,
                                         args);
  }

  public abstract void accept(AstVisitorI visitor);

  /** Represent source position. */
  public static class Position {
    /** Name of source file (will always default non-null) */
    final String sourceName;

    /** Source line number (1-origin)*/
    final int lineNumber;

    /** Source column number (0-origin) */
    final int colNumber;

    static final Position UNKNOWN = new Position(UNKNOWN_SOURCE_NAME, 1, 0);

    public Position(Token t) {
      this(t.getTokenSource().getSourceName(),
           t.getLine(), t.getCharPositionInLine());
    }
    public Position(String srcName, int lineN, int colN) {
      sourceName = srcName;
      lineNumber = lineN; colNumber = colN;
    }

    public String toString() {
      return String.format("%s:%d:%d", sourceName, lineNumber, colNumber);
    }
  }

}

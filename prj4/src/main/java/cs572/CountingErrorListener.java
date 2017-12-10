package cs572;

import org.antlr.v4.runtime.ANTLRErrorListener;
import org.antlr.v4.runtime.ConsoleErrorListener;
import org.antlr.v4.runtime.Parser;
import org.antlr.v4.runtime.Recognizer;
import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.atn.ATNConfigSet;
import org.antlr.v4.runtime.dfa.DFA;

/** ANTLR error listener which is just like ANTLR's ConsoleErrorListener
 *  except that it counts the number of syntax errors (via syntaxError())
 *  and semantic errors (via error()).
 */
public class CountingErrorListener extends ConsoleErrorListener {
  private int _nErrors;

  /** Publically available instance of counting error listener */
  public static CountingErrorListener INSTANCE = new CountingErrorListener();

  private CountingErrorListener() { _nErrors = 0; }

  /** Upon syntax error, notify any interested parties. */
  @Override
  public void
    syntaxError(Recognizer<?,?> recognizer, java.lang.Object offendingSymbol,
                int line, int charPositionInLine, java.lang.String msg,
                RecognitionException e)
  {
    _nErrors++;
    super.syntaxError(recognizer, offendingSymbol, line, charPositionInLine,
                      msg, e);
  }


  /** Return total number of syntax (syntaxError()) and semantic (error())
   *  calls.
   */
  int getNErrors() { return _nErrors; }

  /** Print error specified by printf-style format with args on stderr
   *  followed by a newline.
   */
  public void error(String format, Object...args) {
    System.err.format(format, args);
    System.err.format("\n");
    _nErrors++;
  }

}

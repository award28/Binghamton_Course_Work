import org.antlr.v4.runtime.ANTLRErrorListener;
import org.antlr.v4.runtime.ConsoleErrorListener;
import org.antlr.v4.runtime.Parser;
import org.antlr.v4.runtime.Recognizer;
import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.atn.ATNConfigSet;
import org.antlr.v4.runtime.dfa.DFA;

public class CountingErrorListener extends ConsoleErrorListener {
  private int _nErrors;

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

  int getNErrors() { return _nErrors; }

}

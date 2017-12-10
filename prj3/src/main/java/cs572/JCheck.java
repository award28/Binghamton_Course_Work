package cs572;

import org.antlr.v4.runtime.ANTLRFileStream;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

/** Top-level program. */
public class JCheck {

  private static final String HELP_OPT = "-h";
  private static final String LONG_HELP_OPT = "--help";
  private static final String PP_OPT = "--pp";
  private static final String XML_OPT = "--xml";

  private static final String STDIN_FILE_NAME = "-";

  private static void usage() {
    System.err.format("usage: java %s [%s|%s] [%s] [%s] SRC_FILE|%s\n",
                      JCheck.class.getName(), HELP_OPT, LONG_HELP_OPT,
                      PP_OPT, XML_OPT, STDIN_FILE_NAME);
    System.exit(1);
  }

  /** Invokes ast builder on source file specified by last
   *  command-line argument ("-" specifies standard-input).
   *  If there are no errors, will pretty-print AST on stdout
   *  if --pp option specified; will print XML version of AST
   *  on stdout if --xml option specified.
   */
  public static void main(String[] args) throws Exception {
    boolean doXml = false;
    boolean doPp = false;
    int argIndex;
    for (argIndex = 0; argIndex < args.length; argIndex++) {
      String arg = args[argIndex];
      if (!arg.startsWith("-") || arg.length() == 1) break;
      if (PP_OPT.equals(arg)) {
        doPp = true;
      }
      else if (XML_OPT.equals(arg)) {
        doXml = true;
      }
      else if (HELP_OPT.equals(arg) || LONG_HELP_OPT.equals(arg)) {
        usage();
      }
      else {
        System.err.format("unknown option %s\n", arg);
        usage();
      }
    }
    if (argIndex != args.length - 1) {
      usage();
    }
    else {
      doCheckFile(args[argIndex], doPp, doXml);
    }
  }

  private static void doCheckFile(String fileName,
                                  boolean doPp, boolean doXml)
  {
    try {
      ANTLRInputStream input =
        (STDIN_FILE_NAME.equals(fileName))
        ? new ANTLRInputStream(System.in)
        : new ANTLRFileStream(fileName);
      DecafLexer lexer = new DecafLexer(input);
      lexer.removeErrorListeners();
      CountingErrorListener errors = CountingErrorListener.INSTANCE;
      lexer.addErrorListener(errors);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      DecafParser parser = new DecafParser(tokens);
      parser.removeErrorListeners();
      parser.addErrorListener(errors);
      parser.setBuildParseTree(false);
      ProgramAst ast = parser.start().ast;
      if (errors.getNErrors() == 0) {
        JCheckVisitor jcheck = new JCheckVisitor();
        ast.accept(jcheck);
        if (errors.getNErrors() == 0) {
          if (doPp) {
            PrettyPrintVisitor pp = new PrettyPrintVisitor();
            ast.accept(pp);
            System.out.print(pp.getPrettyPrint());
          }
          if (doXml) {
            XmlPrintVisitor xml = new XmlPrintVisitor();
            ast.accept(xml);
            System.out.print(xml.getXmlPrint());
          }
        }
      }
    }
    catch (Exception e) {
      throw new RuntimeException(e);
    }
  }

}

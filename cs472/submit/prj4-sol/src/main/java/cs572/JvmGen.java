package cs572;

/**

Stores JVM instructions and Jasmin pseudo-ops and emits to a file
ClassName.j when instructed via emit().  Format of instructions
and pseudo-ops are as documented by Jasmin, except for labels,
which have a pseudo-op of ".label".

It is possible to extend this class to reorganize/optimize the
stored instructions before emitting.

*/

import java.util.ArrayList;
import java.util.List;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;

public class JvmGen {

  private final List<JvmOp> _ops;
  private final String _destDir;
  private final String _className;
  private final String _superName;

  /** Construct a generator for class className.
    * The generator will automatically generate a ".class className" and
    * ".super java/lang/Object" pseudo-ops.
    */
  public JvmGen(String destDir, String className) {
    this(destDir, className, null);
  }

  /** Construct a generator for class className with superclass superName.
    * The generator will automatically generate a ".class className" and
    * ".super superName" pseudo-ops.
    */
  public JvmGen(String destDir, String className, String superName) {
    _destDir = destDir;
    _className = className;
    _superName = (superName == null) ? "java/lang/Object" : superName;
    _ops = new ArrayList<JvmOp>();
  }

  /** Add operator op with operands rands to the instruction stream.
    * Automatically produces efficient forms of ldc (iconst_<n>, iconst_m1,
    * bipush, sipush) and [ai]load/store ([ai]load/store_<n>) instructions.
    * Returns index at which instruction was added (each instruction
    * increments the index by 1, irrespective of the number of operands).
    * The instruction is merely added to an internal datastructure.  It
    * will not be added to the .j file until emit() is called.
    */
  public int add(String op, Object... rands) {
    JvmOp jvmOp = new JvmOp(op, rands);
    _ops.add(jvmOp);
    return _ops.size() - 1;
  }

  int add(String op) {
    return add(op, new Object[] { });
  }

  /** Creates a label from a Integer */
  public static String makeLabel(Integer i) {
    return "L" + i;
  }

  /** Add operator op with operands rands to the instruction stream at
    * specified index.  Used for backpatching a previous instruction
    * at a previous index when more information becomes available.
    * Automatically produces efficient forms of ldc (iconst_<n>, iconst_m1,
    * bipush, sipush) and [ai]load/store ([ai]load/store_<n>) instructions.
    * Returns index at which instruction was added (each instruction
    * increments the index by 1, irrespective of the number of operands).
    * The instruction is merely added to an internal datastructure.  It
    * will not be added to the .j file until emit() is called.
    */
  public int backpatch(String op, int index, Object ...rands) {
    JvmOp jvmOp = new JvmOp(op, rands);
    _ops.set(index, jvmOp);
    return index;
  }

  /** Emits all stored ops/pseudo-ops into file className.j.  Returns
    * count of # of instructions emitted.
    */
  public int emit() {
    String jPath = String.format("%s/%s.j", _destDir, _className);
    try {
      PrintWriter out = new PrintWriter(new FileWriter(jPath));
      out.println("\t.class" + " " + _className);
      out.println("\t.super" + " " + _superName);
      out.println("");
      for (int i = 0; i < _ops.size(); i++) {
        JvmOp op = _ops.get(i);
        if (op.op.equals(".method")) out.println();
        out.println(op.toString());
        if (op.op.equals(".end")) out.println();
      }
      out.close();
    }
    catch (IOException e) {
      System.err.println("i/o error while writing " + jPath + ": " + e);
      System.exit(1);
    }
    return _ops.size();
  }

  /** Return # of Jvm ops currently stored. */
  public int nJvmOps() {
    return _ops.size();
  }

  /** Return the JvmOp at the specified index. */
  public JvmOp getJvmOpAtIndex(int index) {
    return _ops.get(index);
  }

  /** Models a Jvm operator or Jasmin pseudo-op. */
  public class JvmOp {
    /** The operator or pseudo-op. */
    public final String op;

    /** The operands.  null if none. */
    public final Object rands[];

    /** Smart constructor for op (or pseudo-op) with operands rands[].
      * Automatically, constructs more efficient forms of ldc, [ai]load
      * and [ai]store ops, depending on operands.
      */
    public JvmOp(String op, Object... rands) {
      String opx = op;
      Object randsx[]= rands;
      if (opx.equals("ldc") && rands.length == 1 &&
          rands[0] instanceof Integer) {
        int rand0 = ((Integer)randsx[0]).intValue();
        if (rand0 == -1) {
          opx = "iconst_m1"; randsx= null;
        }
        else if (0 <= rand0 && rand0 <= 5) {
          opx = "iconst_" + rand0; randsx= null;
        }
        else if (-128 <= rand0 && rand0 <= 127) {
          opx = "bipush";
        }
        else if (-(1<<15) <= rand0 && rand0 <= (1<<15) - 1) {
          opx = "sipush";
        }
      } //if (opx.equals("ldc") && ...)
      else if (opx.equals("iload") || opx.equals("istore") ||
               opx.equals("aload") || opx.equals("astore")) {
        int rand0= ((Integer)randsx[0]).intValue();
        if (0 <= rand0 && rand0 <= 3) {
          opx += "_" + rand0; randsx = null;
        }
      }
      this.op = opx; this.rands = randsx;
    } //public JvmOp(String op, Object rands[])

    /** Converts JvmOp to a string.  Adds suitable indentation for
      * printing in a stream.  If indentation not needed, then left-trim
      * whitespace.
      */
    public String toString() {
      if (op.equals(".label")) {
        return rands[0].toString() + ":";
      }
      else {
        StringBuffer b = new StringBuffer();
        String indent = (op.equals(".method") || op.equals(".end")) ? "" : "\t";
        b.append(indent); b.append(op);
        int n = (rands == null) ? 0 : rands.length;
        for (int i = 0; i < n; i++) {
          b.append(" "); b.append(rands[i].toString());
        }
        return b.toString();
      }
    } //toString()
  } //public class JvmOp

  /** Non-interactive test program. */
  static public void main(String args[]) {
    JvmGen gen= new JvmGen(".", "Test1");
    gen.add(".method", "test");
    gen.add("ldc", 1);
    gen.add("ldc", -1);
    int i = gen.add(".limit");
    gen.add("ldc", -2);
    gen.add("ldc", 100);
    gen.add("ldc", 1000);
    gen.add("ldc", 100000);
    gen.add("iload", 1);
    gen.add("iload", 4);
    gen.add("istore", 0);
    gen.add("iadd");
    gen.add(".label", "Label");
    gen.add(".end", "test");
    gen.backpatch(".limit", i, "locals", 10);
    gen.emit();
  }

}

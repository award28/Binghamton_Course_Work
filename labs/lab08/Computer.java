package lab08;

import java.util.function.*;

public class Computer {
    public Storage storage;

    public Computer(Storage s) {
        this.storage = s;
    }

    public int for_loop(String i, int start, String v, IntBinaryOperator f, IntPredicate stop) {
        this.storage.store(i, start);
        while (true) {
            int tmp = this.storage.load(v);
            int ii = this.storage.load(i);
            tmp = f.applyAsInt(ii, tmp);
            this.storage.store(v, tmp);
            if (!stop.test(ii)) {
                break;
            }
            this.storage.store(i, ii + 1);
        }
        return this.storage.load(v);
    }

    public void setVariable(String s, int i) {
        this.storage.store(s, i);
    }

    public int getVariable(String s) {
        return this.storage.load(s);
    }
}



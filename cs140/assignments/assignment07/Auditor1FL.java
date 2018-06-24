package assignment07;

import java.util.ArrayList;

public class Auditor1FL extends Auditor {
	
    public Auditor1FL(ArrayList<GenEd> sList, boolean b) {
        super(sList, b);
        this.removeGenedReq(GenEd.FL2);
        this.removeGenedReq(GenEd.FL3);
    }
}

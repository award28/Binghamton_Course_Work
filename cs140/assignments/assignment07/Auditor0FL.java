package assignment07;

import java.util.ArrayList;

public class Auditor0FL extends Auditor {
	
    public Auditor0FL(ArrayList<GenEd> sList, boolean b) {
        super(sList, b);
        this.removeGenedReq(GenEd.FL1);
        this.removeGenedReq(GenEd.FL2);
        this.removeGenedReq(GenEd.FL3);
    }
}
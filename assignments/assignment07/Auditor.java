package assignment07;

import java.util.ArrayList;

public class Auditor {
	private ArrayList<GenEd> genedReqs = new ArrayList<>();
	private ArrayList<GenEd> studentList;
	
	{
		genedReqs.add(GenEd.A);
		genedReqs.add(GenEd.C);
		genedReqs.add(GenEd.FL1);
		genedReqs.add(GenEd.FL2);
		genedReqs.add(GenEd.FL3);
		genedReqs.add(GenEd.G);
		genedReqs.add(GenEd.H);
		genedReqs.add(GenEd.L);
		genedReqs.add(GenEd.M);
		genedReqs.add(GenEd.N);
		genedReqs.add(GenEd.O);
		genedReqs.add(GenEd.S);
		genedReqs.add(GenEd.Y);	
	}
	
	public Auditor(ArrayList<GenEd> sList, boolean b) {
		if(b){
			genedReqs.add(GenEd.P);
		}
		else {
			genedReqs.add(GenEd.PH);
		}
		
		studentList = (ArrayList<GenEd>) sList.clone();
		
		if(studentList.contains(GenEd.J)){
			studentList.add(GenEd.C);
			studentList.add(GenEd.O);
		}
		
		if(studentList.contains(GenEd.B)){
			studentList.add(GenEd.S);
			studentList.add(GenEd.Y);
		}
	}
	public void removeGenedReq(GenEd g) {
		genedReqs.remove(g);
	}
	
	public ArrayList<GenEd> missingGeneds() {
		for(int i = 0; i < studentList.size(); i++){
			genedReqs.remove(studentList.get(i));
		}
		
		return genedReqs;
	}
}

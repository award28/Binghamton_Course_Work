package lab06;

import java.util.ArrayList;

public class Document {
	private ArrayList<TextTag> textTags;

	public Document() {
		textTags = new ArrayList<TextTag>();
	}
	
	public void addTextTag(TextTag added) {
		textTags.add(added);
	}

	public ArrayList<TextTag> sortInLineOrder() {
		ArrayList<TextTag> returnTextTags = new ArrayList<TextTag>();
		
		
	}
}

package lab06;

public class TextTag {
	private int line;
	private int column;
	private String text;

	public TextTag() {
		this.line = line;
		this.column = column;
		this.text = text;
	}

	public int getLine() {
		return line;
	}

	public int getColumn() {
		return column;
	}
	
	ps = new ArrayList<TextTag>()ublic String getText() {
		return text;
	}

	public String toString() {
 		StringBuilder bldr = new StringBuilder();		
		bldr.append(line + "-" column + " " + text);
		return bldr.toString();
	}
}

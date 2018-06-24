package lab07;

import java.util.List;
import java.lang.UnsupportedOperationException;

public class Buffer {   
    protected List<String> lines;


    public int getNumlines() {     
        return lines.size();
    }

    public String getText() {
        return String.join("\n", this.lines);
    }

    public void draw() {
    System.out.println(this.getText());
    }

    public void save() {
       throw new UnsupportedOperationException();
    }

   public void type(String toType) {
        for(int i = 0; i < toType.length(); i++) {
            if(toType.charAt(i) == '\n') {
                lines.add("");
            }
            else {
              lines.add(toType.charAt(i)); 
            }
        }
   }
}

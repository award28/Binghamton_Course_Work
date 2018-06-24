package pippin;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class Assembler {
	public static Set<String> noArgument = new TreeSet<String>();

	static {
		noArgument.add("HALT");
		noArgument.add("NOP");
		noArgument.add("NOT");
	}

	/**
	 * Method to assemble a file to its executable representation. If the input
	 * has errors one of the errors will be reported the StringBulder. The error
	 * may not be the first error in the code and will depend on the order in
	 * which instructions are checked. The line number of the error that is
	 * reported is returned as the value of the method. A return value of 0
	 * indicates that the code had no errors and an output file was produced and
	 * saved. If the input or output cannot be opened, the return value is -1.
	 * The unchecked exception IllegalArgumentException is thrown if the error
	 * parameter is null, since it would not be possible to provide error
	 * information about the source code.
	 * 
	 * @param input		the source assembly language file
	 * @param output	the executable version of the program if the source program is
	 *          		correctly formatted
	 * @param error		the StringBuilder to store the description of the error that
	 *            		is reported. It will be empty if no error is found
	 * @return 0 		if the source code is correct and the executable is saved, -1
	 *         			if the input or output files cannot be opened, otherwise the line
	 *         			number of the reported error
	 */
	public static int assemble(File input, File output, StringBuilder error) {
		if (error == null)
			throw new IllegalArgumentException("Coding error: the error buffer is null");

		ArrayList<String> inputText = new ArrayList<String>();
		int retVal = 0;

		try (Scanner inp = new Scanner(input)) {
			int lineNum = 1;
			int firstBlank = 0;

			while (inp.hasNextLine() && retVal == 0) {
				String line = inp.nextLine();

				if (line.trim().length() == 0) {
					if (firstBlank == 0) {
						firstBlank = lineNum;
					} 
					else {
						error.append("Illegal blank line in the source file");
						retVal = firstBlank;
					}
				} 
				else if (line.charAt(0) == ' ' || line.charAt(0) == '\t') {
					error.append("Line starts with illegal white space");
					retVal = lineNum;
				} 
				else
					inputText.add(line.trim());

				lineNum++;
			}
		} catch (FileNotFoundException e) {
			error.append("Unable to open the assembled file");
			retVal = -1;
		}

		ArrayList<String> inputCode = new ArrayList<>();
		ArrayList<String> inputData = new ArrayList<>();
		ArrayList<String> outputCode = new ArrayList<>();
		ArrayList<String> outputData = new ArrayList<>();

		if (retVal == 0) {
			boolean codeRead = false;

			for (int i = 0; i < inputText.size() && retVal == 0; i++) {
				if (!(inputText.get(i).trim().equalsIgnoreCase("ENDCODE")) && !inputText.get(i).contains("ENDCODE")
						&& !codeRead) {
					inputCode.add(inputText.get(i).trim());
				} 
				else if (inputText.get(i).trim().equalsIgnoreCase("ENDCODE")) {
					if (!(inputText.get(i).trim().equals("ENDCODE"))) {
						error.append("Error on line " + (i + 1) + ": \"ENDCODE\" must be upper case");
						retVal = i + 1;
					}
					codeRead = true;
				} 
				else {
					inputData.add(inputText.get(i).trim());

				}
			}
			for (int i = 0; i < inputCode.size() && retVal == 0; i++) {
				String[] parts = inputCode.get(i).split("\\s+");
				if (!InstructionMap.opcode.containsKey(parts[0].toUpperCase())) {
					error.append("Error on line " + (i + 1) + ": illegal mnemonic");
					retVal = i + 1;
				} 
				else if (parts[0].toUpperCase() != parts[0]) {
					error.append("Error on line " + (i + 1) + ": mnemonic must be upper case");
					retVal = i + 1;
				} 
				else if (parts.length > 1 && noArgument.contains(parts[0])) {
					if (noArgument.contains(parts[0])) {
						error.append("Error on line " + (i + 1) + ": this mnemonic cannot take arguments");
						retVal = i + 1;
					} 
					else {
						outputCode.add(Integer.toString(InstructionMap.opcode.get(parts[0]), 16) + " 0");
					}
				} 
				else {
					if (parts.length > 2) {
						error.append("Error on line " + (i + 1) + ": this mnemonic has too many arguments");
						retVal = i + 1;
					} 
					else if (parts.length == 1 && !noArgument.contains(parts[0])) {
						error.append("Error on line " + (i + 1) + ": this mnemonic a missing arguments");
						retVal = i + 1;
					} 
					else if (noArgument.contains(parts[0])) {
						outputCode.add(Integer.toString(InstructionMap.opcode.get(parts[0]), 16) + " 0");
					} 
					else {
						try {
							int arg = Integer.parseInt(parts[1], 16);
							outputCode.add(Integer.toString(InstructionMap.opcode.get(parts[0]), 16) + " "
									+ Integer.toString(arg, 16));
						} catch (NumberFormatException e) {
							error.append("Error on line " + (i + 1) + ": argument is not a hex number");
							retVal = i + 1;
						}
					}
				}
			}
			for (int i = 0; i < inputData.size() && retVal == 0; i++) {
				String[] parts = inputData.get(i).split("\\s+");
				int[] values = new int[2];

				if (parts.length == 2) {
					try {
						values[0] = Integer.parseInt(parts[0], 16);
						values[1] = Integer.parseInt(parts[0], 16);

						outputData.add(inputData.get(i));
					} catch (NumberFormatException e) {
						error.append("Error on line " + (i + 1) + ": argument is not a hex number");
						retVal = i + 1;
					}
				} 
				else if (parts.length < 2) {
					error.append("Error on line " + (i + 1) + ": this data is missing arguments");
					retVal = i + 1;
				} 
				else if (parts.length > 2) {
					error.append("Error on line " + (i + 1) + ": this data has too many arguments");
					retVal = i + 1;
				}
			}
		}
		if (retVal == 0) {
			try (PrintWriter outp = new PrintWriter(output)) {
				for (String str : outputCode) {
					outp.println(str);
				}
				outp.println(-1);
				for (String str : outputData) {
					outp.println(str);
				}
				outp.close();
			} catch (FileNotFoundException e) {
				error.append("Error: Unable to write the assembled program to the output file");
				retVal = -1;
			}
		}
		return retVal;
	}
}

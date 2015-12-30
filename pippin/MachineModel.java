package pippin;

import java.util.Map;
import java.util.Observable;
import java.util.TreeMap;

public class MachineModel extends Observable {

	public final Map<Integer, Instruction> INSTRUCTIONS = new TreeMap<>();
	private Registers cpu = new Registers();
	private Memory memory = new Memory();
	private Code code = new Code();
	private boolean withGUI = false;
	private boolean running = false;

	public MachineModel() {
		this(false);
	}

	public MachineModel(boolean withGUI) {
		this.withGUI = withGUI;

		// INSTRUCTIONS entry for "NOP"
		INSTRUCTIONS.put(0x0, arg -> {
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "LODI"
		INSTRUCTIONS.put(0x1, arg -> {
			cpu.accumulator = arg;
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "LOD"
		INSTRUCTIONS.put(0x2, arg -> {
			INSTRUCTIONS.get(0x1).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "LODN"
		INSTRUCTIONS.put(0x3, arg -> {
			INSTRUCTIONS.get(0x2).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "STO"
		INSTRUCTIONS.put(0x4, arg -> {
			memory.setData(arg, cpu.accumulator);
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "STON"
		INSTRUCTIONS.put(0x5, arg -> {
			INSTRUCTIONS.get(0x4).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "JMPI"
		INSTRUCTIONS.put(0x6, arg -> {
			cpu.programCounter = arg;
		});

		// INSTRUCTIONS entry for "JUMP"
		INSTRUCTIONS.put(0x7, arg -> {
			INSTRUCTIONS.get(0x6).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "JMZI"
		INSTRUCTIONS.put(0x8, arg -> {
			if (cpu.accumulator == 0) {
				cpu.programCounter = arg;
			} else {
				cpu.programCounter++;
			}
		});

		// INSTRUCTIONS entry for "JMPZ"
		INSTRUCTIONS.put(0x9, arg -> {
			INSTRUCTIONS.get(0x8).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "ADDI"
		INSTRUCTIONS.put(0xA, arg -> {
			cpu.accumulator += arg;
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "ADD"
		INSTRUCTIONS.put(0xB, arg -> {
			INSTRUCTIONS.get(0xA).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "ADDN"
		INSTRUCTIONS.put(0xC, arg -> {
			INSTRUCTIONS.get(0xB).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "SUBI"
		INSTRUCTIONS.put(0xD, arg -> {
			cpu.accumulator -= arg;
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "SUB"
		INSTRUCTIONS.put(0xE, arg -> {
			INSTRUCTIONS.get(0xD).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "SUBN"
		INSTRUCTIONS.put(0xF, arg -> {
			INSTRUCTIONS.get(0xE).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "MULI"
		INSTRUCTIONS.put(0x10, arg -> {
			cpu.accumulator *= arg;
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "MUL"
		INSTRUCTIONS.put(0x11, arg -> {
			INSTRUCTIONS.get(0x10).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "MULN"
		INSTRUCTIONS.put(0x12, arg -> {
			INSTRUCTIONS.get(0x11).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "DIVI"
		INSTRUCTIONS.put(0x13, arg -> {
			if (arg != 0) {
				cpu.accumulator /= arg;
				cpu.programCounter++;
			} else {
				throw new DivideByZeroException();
			}
		});

		// INSTRUCTIONS entry for "DIV"
		INSTRUCTIONS.put(0x14, arg -> {
			INSTRUCTIONS.get(0x13).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "DIVN"
		INSTRUCTIONS.put(0x15, arg -> {
			INSTRUCTIONS.get(0x14).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "ANDI"
		INSTRUCTIONS.put(0x16, arg -> {
			if (arg != 0 && cpu.accumulator != 0) {
				cpu.accumulator = 1;
			} else {
				cpu.accumulator = 0;
			}
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "AND"
		INSTRUCTIONS.put(0x17, arg -> {
			INSTRUCTIONS.get(0x16).execute(memory.getData(arg));
		});

		// INSTRUCTIONS entry for "NOT"
		INSTRUCTIONS.put(0x18, arg -> {
			if (cpu.accumulator == 0) {
				cpu.accumulator = 1;
			} else {
				cpu.accumulator = 0;
			}
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "CMPL"
		INSTRUCTIONS.put(0x19, arg -> {
			if (memory.getData(arg) < 0) {
				cpu.accumulator = 1;
			} else {
				cpu.accumulator = 0;
			}
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "CMPZ"
		INSTRUCTIONS.put(0x1A, arg -> {
			if (memory.getData(arg) == 0) {
				cpu.accumulator = 1;
			} else {
				cpu.accumulator = 0;
			}
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "HALT"
		INSTRUCTIONS.put(0x1F, arg -> {
			halt();
		});

		// INSTRUCTIONS entry for "COPY"
		INSTRUCTIONS.put(0x1D, (arg) -> {
			copy(arg);
			cpu.programCounter++;
		});

		// INSTRUCTIONS entry for "CPYN"
		INSTRUCTIONS.put(0x1E, (arg) -> {
			INSTRUCTIONS.get(0x1D).execute(memory.getData(arg));
		});
	}

	public int getData(int index) {
		return memory.getData(index);
	}

	public void setData(int index, int value) {
		memory.setData(index, value);
	}

	public Instruction get(Object key) {
		return INSTRUCTIONS.get(key);
	}

	int[] getData() {
		return memory.getDataArray();
	}

	int getProgramCounter() {
		return cpu.programCounter;
	}

	int getAccumulator() {
		return cpu.accumulator;
	}

	void setAccumulator(int i) {
		cpu.accumulator = i;
	}

	void setProgramCounter(int i) {
		cpu.programCounter = i;
	}

	void halt() {
		if (withGUI) {
			running = false;
		} else {
			System.exit(0);
		}
	}

	public int getChangedIndex() {
		return memory.getChangedIndex();
	}

	public void clearMemory() {
		memory.clear();
	}

	Code getCode() {
		return code;
	}

	public void setCode(int op, int arg) {
		code.setCode(op, arg);
	}

	public void step() {
		try {
			int pc = cpu.programCounter;
			int opcode = code.getOp(pc);
			int arg = code.getArg(pc);
			get(opcode).execute(arg);
		} catch (Exception e) {
			halt();
			throw e;
		}
	}

	public void clear() {
		memory.clear();
		code.clear();
		cpu.accumulator = 0;
		cpu.programCounter = 0;
	}

	public void setRunning(boolean running) {
		this.running = running;
	}

	public boolean getRunning() {
		return running;
	}

	/**
	 * Loads in source location, target location, and length of data to be
	 * copied from parameter. Copies data from source to target location.
	 * 
	 * @param arg
	 *            memory location of data used by copy
	 */
	public void copy(int arg) {
		int source = memory.getData(arg);
		int target = memory.getData(arg + 1);
		int length = memory.getData(arg + 2);
		if (source < 0 || source > memory.DATA_SIZE - 1 || target < 0 || target > memory.DATA_SIZE - 1) {
			throw new IllegalArgumentException();
		}
		if (source < target) {
			for (int i = target + length - 1, j = source + length - 1; i > target - 1 && j > source - 1; i--, j--) {
				memory.setData(i, memory.getData(j));
			}
		} else {
			for (int i = target, j = source; i < target + length && j < source + length; i++, j++) {
				memory.setData(i, memory.getData(j));
			}
		}
	}

	public class Registers {
		private int accumulator;
		private int programCounter;
	}
}

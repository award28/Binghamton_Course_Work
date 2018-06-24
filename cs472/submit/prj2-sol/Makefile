COURSE = cs572

JAVA_SRC_DIR = src/main/java
ANTLR_SRC_DIR = src/main/antlr

JAR = build/libs/prj2-sol.jar


.PHONY:		 clean



$(JAR):		$(wildcard $(JAVA_SRC_DIR)/*.java $(ANTLR_SRC_DIR)/*.g4)
		ant -emacs $(VERBOSE) </dev/null



run:		$(JAR)
		java -cp '$(HOME)/$(COURSE)/lib/*:build/libs/*' Jpp

clean:
		ant clean


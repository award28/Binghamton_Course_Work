COURSE = cs572

JAVA_SRC_DIR = src/main/java
ANTLR_SRC_DIR = src/main/antlr
SRCS = $(wildcard $(JAVA_SRC_DIR)/$(COURSE)/*.java $(ANTLR_SRC_DIR)/*.g4)

JAR = build/libs/prj3-sol.jar


.PHONY:		 clean



$(JAR):		$(SRCS)
		ant -emacs $(VERBOSE) </dev/null

api:
		ant api

clean:
		ant clean

$(TARGET):
		ant $(TARGET)

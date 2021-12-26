JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

# @SuppressWarnings("unchecked");
CLASSES = \
	GameScreenGUI.java \
	MainMenuGUI.java \
	HexGUI.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
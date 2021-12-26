JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

# @SuppressWarnings("unchecked");
CLASSES = \
	Collection.java \
	Set.java \
	Queue.java \
	List.java \
	HashSet.java \
	LinkedList.java \
	ArrayList.java \
	hierarchyTest.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
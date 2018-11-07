all: test clean

test:
	cl /EHsc /c LinkedList.cpp
	cl /EHsc test.cpp LinkedList.cpp
	
clean:
	del *.obj
	del *.exe	
#
#
#

LDFLAGS = -lopencv_objdetect -lopencv_core -lopencv_imgproc -lopencv_highgui

all:	sample1

sample1:	sample1.cpp
	c++ $^ -o $@ $(LDFLAGS)

clean:
	$(RM) -f sample1

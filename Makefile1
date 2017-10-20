#
#
#

LDFLAGS = -lopencv_objdetect -lopencv_core -lopencv_imgproc -lopencv_highgui

all:	get_rect

get_rect:	get_rect.cpp
	c++ $^ -o $@ $(LDFLAGS)

clean:
	$(RM) -f get_rect

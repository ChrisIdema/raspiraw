CROSS_COMPILE ?=

CC	?= g++
CC	:= $(CROSS_COMPILE)$(CC)
CFLAGS	?= -I/opt/vc/include -pipe -W -Wall -Wextra -O4 -MD -Wl,--no-as-needed
CFLAGs += -I/usr/local/include/opencv4
LDFLAGS	?=
LIBS	:= -L/opt/vc/lib -lrt -lbcm_host -lvcos -lmmal_core -lmmal_util -lmmal_vc_client -lvcsm -lpthread
LIBS +=  `pkg-config --libs --cflags opencv4`
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio
LIBS += -Lstdc++ -lbcm_host -lrt


%.o : %.c %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: raspiraw

OBJS := raspiraw.o RaspiCLI.o opencv_raw.o
raspiraw: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	-rm -f *.o *.d
	-rm -f raspiraw

-include $(OBJS:.o=.d)

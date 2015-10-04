# Paths
OPENCV_PATH=/Users/yzl5709/software/opencv3
#change the path with your opencv path

# Programs
CC=
CXX=g++

# Flags
ARCH_FLAGS=
CFLAGS=-Wextra -Wall  $(ARCH_FLAGS) -O3 -Wno-long-long
LDFLAGS=$(ARCH_FLAGS)
DEFINES=
INCLUDES=-I$(OPENCV_PATH)/include -Iinclude/
LIBRARIES=-L$(OPENCV_PATH)/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_videoio -lopencv_imgcodecs


# Source files which contain a int main(..) function
SOURCE_FILES_WITH_MAIN=bs.cc


ALL_OBJECTS=\
	$(patsubst %.cc,%.o,$(SOURCE_FILES_WITH_MAIN))

DEPENDENCY_FILES=\
	$(patsubst %.o,%.d,$(ALL_OBJECTS)) 

all: bs

%.o: %.cc Makefile
	@# Make dependecy file
	$(CXX) -MM -MT $@ -MF $(patsubst %.cc,%.d,$<) $(CFLAGS) $(DEFINES) $(INCLUDES) $<
	@# Compile
	$(CXX) $(CFLAGS) $(DEFINES) -c -o $@ $< $(INCLUDES)

-include $(DEPENDENCY_FILES)

bs: $(ALL_OBJECTS)
	$(CXX) $(LDFLAGS)  -o $@ $(ALL_OBJECTS) $(LIBRARIES)

.PHONY: clean
clean:
	@echo "Cleaning"
	@for pattern in '*~' '*.o' '*.d' ; do \
		find . -name "$$pattern" | xargs rm ; \
	done

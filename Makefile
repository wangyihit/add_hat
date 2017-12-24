INCLUDE_OPENCV =-I/home/wangyi/proj/cpp/libs/include/opencv \
              -I/home/wangyi/proj/cpp/libs/include

LIBS_OPENCV = -L/home/wangyi/proj/cpp/libs/lib -L/home/wangyi/proj/cpp/libs/share/OpenCV/3rdparty/lib -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core -llibwebp -llibtiff -llibjasper -lIlmImf -ljpeg -lpng -lz -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lfontconfig -lfreetype -lgthread-2.0 -lgstbase-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lstdc++ -ldl -lm -lpthread -lrt

CXX = g++
CFLAG += -g
CXXFLAG += -std=c++11

INCLUDES := $(INCLUDE_OPENCV)

LIBS = -lgflags ${LIBS_OPENCV}

HEADER = $(wildcard *.h)
SOURCE = $(wildcard *.cpp)
BIN  = add_hat
OBJ = $(patsubst %.cpp,%.o,$(SOURCE))

all: $(BIN)
	echo "build $(BIN)"

run : $(BIN)
	./$(BIN) --large_image ./large.jpg --small_image ./small.jpg

%.o: %.cpp
	$(CXX)  -o $@ $(INCLUDES) $(CFLAG) $(CXXFLAG) -c $<

$(BIN) : $(OBJ) $(HEADER)
	$(CXX) -o $(BIN) $(INCLUDES) $(OBJ) $(LIBS)

clean :
	rm -f *.o $(BIN)

rb:
	echo "rebulid ..."
	make clean
	make $(BIN)

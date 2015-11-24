CC     = g++
CFLAGS = -pedantic -Wall -Wextra -O2
UNAME   := $(shell uname)
ifeq ($(UNAME), Linux)
OPENCV = -I/usr/include/opencv  /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_contrib.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_core.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_features2d.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_flann.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_gpu.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_highgui.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_legacy.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_ml.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_ocl.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_photo.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_stitching.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_superres.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_ts.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_video.so \
		 /usr/lib/x86_64-linux-gnu/libopencv_videostab.so -lopencv_calib3d \
		 -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu \
		 -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml \
		 -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching \
		 -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
else ifeq ($(UNAME), Darwin)
OPENCV = -I/usr/local/Cellar/opencv/2.4.12/include/opencv \
		 -I/usr/local/Cellar/opencv/2.4.12/include -L/usr/local/Cellar/opencv/2.4.12/lib \
		 -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d \
		 -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy \
		 -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo \
		 -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video \
		 -lopencv_videostab
endif

all: carve

carve: src/carve.cpp bin/seamcarver.o
	@echo CC $<
	@$(CC) $(CFLAGS) -o $@ $^ $(OPENCV)

bin/seamcarver.o: src/seamcarver.cpp src/seamcarver.h
	@echo CC $<
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo RM "carve bin/seamcarver.o"
	@rm -f carve bin/seamcarver.o

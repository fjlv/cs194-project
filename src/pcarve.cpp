#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <sys/time.h>
#include <getopt.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "clhelp.h"

using namespace cv;
using namespace std;

double get_time() 
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char *argv[])
{
    // OpenCL boilerplate
    std::string ..._kernel_str;

    std::string ..._name_str = std::string("...");
    std::string ..._kernel_file = std::string("...");

    cl_vars_t cv; 
    cl_kernel ...;

    readFile(..._kernel_file, ..._kernel_str);

    initialize_ocl(cv);

    compile_ocl_program(..., cv, ..._kernel_str.c_str(), ..._name_str.c_str());

    // Parse arguments
    char c;
    char *filepath;
    int cut_horizontal;
    int cut_vertical;
    int timed = 0;
    int show = 0;

    while ((c = getopt(argc, argv, "f:h:v:ts")) != -1) {
        switch (c) {
        case 'f': filepath = optarg; break;
        case 'h': cut_horizontal = (int)strtol(optarg, NULL, 10); break;
        case 'v': cut_vertical = (int)strtol(optarg, NULL, 10); break;
        case 't': timed = 1; break;
        case 's': show = 1; break;
        default: exit(1); 
        }
    }

    // Read image
    Mat_<Vec3b> image = imread(filepath);

    if (!image.data) {
        printf("%s\n", "Invalid input");
        image.release();
        return -1;
    }

    if (show) {
        imshow("Original Image", image);
    }

    // Carving happens here
    double start = get_time();
    ...;
    double elapsed = get_time() - start;
    // --------------------

    if (timed) {
        printf("Elapsed time: %.3lf seconds\n", elapsed);
    }

    Mat_<Vec3b> output = ...;
    imwrite("scarved.jpg", output);

    if (show) {
        imshow("Carved Image", output);
        while (waitKey(20) != 27);
    }

    image.release();

    uninitialize_ocl(cv);

    ...;

    clReleaseMemObject(...); 

    return 0;
}

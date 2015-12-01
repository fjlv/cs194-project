#include <sys/time.h>
#include <getopt.h>
#include <cstdio>

#include "sseamcarver.h"

double get_time() 
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char **argv) 
{
    char c;
    char *filepath;
    int cut_horizontal = 0;
    int cut_vertical = 0;
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

    Mat_<Vec3b> image = imread(filepath);

    if (!image.data) {
        cout << "Invalid input";
        image.release();
        return -1;
    }

    if (show) {
        imshow("Original Image", image);
    }

    SeamCarver s(image);

    // imshow("Gradient", s.energy);
    // Mat tmp = s.energy/195075.0*255.0;
    // s.energy.convertTo(tmp,CV_8U,-1);
    // imwrite("bench_gradient.jpg", tmp);
    // vector<uint> sm = s.findVerticalSeam();
    // s.showVerticalSeam(sm);

    double start = get_time();
    for (int i = 0; i < cut_horizontal; ++i) {
        vector<uint> seam = s.findHorizontalSeam();
        // s.showHorizontalSeam(seam);
        s.removeHorizontalSeam(seam);
    }
    for (int i = 0; i < cut_vertical; ++i) {
        vector<uint> seam = s.findVerticalSeam();
        // s.showVerticalSeam(seam);
        s.removeVerticalSeam(seam);
    }
    double elapsed = get_time() - start;

    if (timed) {
        printf("Elapsed time: %.3lf seconds\n", elapsed);
    }

    Mat_<Vec3b> output = s.getImage();
    imwrite("scarved.jpg", output);

    if (show) {
        imshow("Carved Image", output);
        while (waitKey(20) != 27);
    }

    // cout << "Seam Length: " << seam.size() << endl;
    // s.showImage();
    // s.showEnergy();

    // imwrite("bench_carved.jpg", s.getImage());

    // for (int i = 0; i < 5; ++i) {
    //     for (int j = 0; j < 5; ++j) {
    //         cout << s.energy.at<uint32_t>(i,j) << " ";
    //     }
    //     cout << endl;
    // }
    image.release();
    return 0;
}

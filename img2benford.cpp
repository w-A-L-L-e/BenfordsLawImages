
/* ====================================================================================================================
 * File: img2benford.cpp
 * Author: Walter Schreppers
 * Description: This is a proof of concept literally written as quickly as possible.
 *  Was watching this 'connected' show on netflix about Benfords Law and I had to see it
 *  myself. As my initial thought was: that's total BS ;)
 *  Not clean, nor optimal code, we're using using namespace std to type less etc. ;)
 *  anyway just install libjpeg en libpng (form mac users you can run make install_deps)
 *  then just 'make' to create the img2benford executable
 *  you need xcode+homebrew installed. or on linux g++, libjpeg and libpng):
 *
 *     make && ./img2benford -random
 *  and run it on a jpeg or png image like so:
 *     ./img2benford <photo path>
 *
 *   When running with -random I see what I expect.
 *   However it gets really interesting when using a random jpg image from a waterfall in nature.
 *   It does indeed show a curve you wouldn't expect and resembles what the show was about ;) :
 *
 *   ./img2benford tests/nature_image.jpg
 *
 *    #########
 *    #########
 *    #########
 *    #########
 *    #########   #########
 *    #########   #########
 *    #########   #########
 *    #########   #########
 *    #########   #########
 *    #########   #########
 *    #########   #########
 *    #########   #########
 *    #########   #########   #########
 *    #########   #########   #########
 *    #########   #########   #########
 *    #########   #########   #########   #########
 *    #########   #########   #########   #########
 *    #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########   #########   #########   #########   #########
 *    #########   #########   #########   #########   #########   #########   #########   #########   #########
 *      1 (25)      2 (21)      3 (13)      4 (10)      5 (8)       6 (5)       7 (4)       8 (3)       9 (3)
 *
 *    benford count 1 = 648313 percentage = 25
 *    benford count 2 = 531042 percentage = 21
 *    benford count 3 = 351602 percentage = 13
 *    benford count 4 = 273866 percentage = 10
 *    benford count 5 = 211944 percentage = 8
 *    benford count 6 = 127823 percentage = 5
 *    benford count 7 = 106355 percentage = 4
 *    benford count 8 = 89524 percentage = 3
 *    benford count 9 = 91162 percentage = 3
 ======================================================================================================================*/

#include <iostream>
#include <locale>
#include <map>
#include <stdlib.h>
#include <string>
#include <time.h>

#include <jpeglib.h>
#define PNG_DEBUG 3
#include <png.h>

// This isn't best practice, but to get things done it makes you type less ;)
using namespace std;

// we could be more clever here, however this simplest
// implemtation does 1 million nr's to msb in less than 0.03s. hooorai for fast cpu's ;)
int mostSignificantDigit(int nr)
{
    int msd = nr;
    while (msd > 10) {
        msd = msd / 10;
    }

    // cout << "nr =" << nr << "msd = " << msd <<endl;
    return msd;
}

void reset_benford_counters(map<int, int> &benford_counts)
{
    benford_counts[0] = 0; // only happens if number == 0
    benford_counts[1] = 0;
    benford_counts[2] = 0;
    benford_counts[3] = 0;
    benford_counts[4] = 0;
    benford_counts[5] = 0;
    benford_counts[6] = 0;
    benford_counts[7] = 0;
    benford_counts[8] = 0;
    benford_counts[9] = 0;
}

void show_benford_counts(map<int, int> &benford_counts, long set_size)
{
    // clearscreen (works in linux & mac, no idea for windows)
    // printf("\033c");

    // print a ascii graph
    // find max y
    double max_y = (100 * benford_counts[0] / set_size);
    for (int i = 1; i <= 9; i++) {
        int bval = (100 * benford_counts[i]) / set_size;
        if (bval > max_y) {
            max_y = (100 * benford_counts[i]) / set_size;
        }
    }

    double height = max_y + 1;
    double ratio = height / max_y;
    // cout <<endl<<"Graph height="<<height<<" max_y="<<max_y<<" ratio="<<ratio<<":"<<endl<<endl;

    // plot our benford graph of msd's 1 - 9
    for (int row = 0; row < height; row++) {
        for (int col = 1; col <= 9; col++) {
            double value = (100 * benford_counts[col]) / set_size;
            if ((value * ratio) - (height - row) > 0) {
                cout << "#########   ";
            }
            else {
                cout << "            ";
            }
        }
        cout << endl;
    }

    for (int col = 1; col <= 9; col++) {
        int bval = (100 * benford_counts[col]) / set_size;
        cout << "  " << col << " (" << bval << ")    ";
        if (bval < 10) cout << " ";
    }
    cout << endl << endl;

    // cout << "benford count 0 = " << benford_counts[0] << " percentage = " << (100*benford_counts[0])/set_size << endl;
    cout << "benford count 1 = " << benford_counts[1] << " percentage = " << (100 * benford_counts[1]) / set_size << endl;
    cout << "benford count 2 = " << benford_counts[2] << " percentage = " << (100 * benford_counts[2]) / set_size << endl;
    cout << "benford count 3 = " << benford_counts[3] << " percentage = " << (100 * benford_counts[3]) / set_size << endl;
    cout << "benford count 4 = " << benford_counts[4] << " percentage = " << (100 * benford_counts[4]) / set_size << endl;
    cout << "benford count 5 = " << benford_counts[5] << " percentage = " << (100 * benford_counts[5]) / set_size << endl;
    cout << "benford count 6 = " << benford_counts[6] << " percentage = " << (100 * benford_counts[6]) / set_size << endl;
    cout << "benford count 7 = " << benford_counts[7] << " percentage = " << (100 * benford_counts[7]) / set_size << endl;
    cout << "benford count 8 = " << benford_counts[8] << " percentage = " << (100 * benford_counts[8]) / set_size << endl;
    cout << "benford count 9 = " << benford_counts[9] << " percentage = " << (100 * benford_counts[9]) / set_size << endl;
}

void abort_(const char *s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

// yuckie, ugly globals, used by the process_png
int x, y;
int width, height;
png_byte color_type;
png_byte bit_depth;
png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep *row_pointers;

void read_png_file(char *file_name)
{
    char header[8]; // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp) abort_("[read_png_file] File %s could not be opened for reading", file_name);
    fread(header, 1, 8, fp);
    // if (png_sig_cmp(header, 0, 8))
    //        abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) abort_("[read_png_file] png_create_read_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) abort_("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr))) abort_("[read_png_file] Error during init_io");

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr))) abort_("[read_png_file] Error during read_image");

    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (y = 0; y < height; y++)
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, row_pointers);

    fclose(fp);
}
void process_png(map<int, int> &benford_counts)
{
    if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
        abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
               "(lacks the alpha channel)");

    if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
        abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)", PNG_COLOR_TYPE_RGBA,
               png_get_color_type(png_ptr, info_ptr));

    for (y = 0; y < height; y++) {
        png_byte *row = row_pointers[y];
        for (x = 0; x < width; x++) {
            png_byte *ptr = &(row[x * 4]);
            // printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
            // x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
            // just add red+green+blue
            int pixel_value = ptr[0] + ptr[1] + ptr[2];
            // cout << "pixel ="<<pixel_value<<endl;
            int msd = mostSignificantDigit(pixel_value);
            benford_counts[msd] = benford_counts[msd] + 1;
        }
    }

    show_benford_counts(benford_counts, width * height);
}

int process_jpg(const char *Name, map<int, int> &benford_counts)
{
    unsigned char a, r, g, b;
    int width, height;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *infile;           /* source file */
    JSAMPARRAY pJpegBuffer; /* Output row buffer */
    int row_stride;         /* physical row width in output buffer */
    if ((infile = fopen(Name, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", Name);
        return 0;
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void)jpeg_read_header(&cinfo, TRUE);
    (void)jpeg_start_decompress(&cinfo);
    width = cinfo.output_width;
    height = cinfo.output_height;

    row_stride = width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

    long pixelcount = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
        (void)jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < width; x++) {
            a = 0; // alpha value is not supported on jpg
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            }
            else {
                g = r;
                b = r;
            }

            // cout << "r="<< (int)r << " g=" << (int)g << " b=" << (int)b << endl;
            long pixel_value = (int)r + (int)g + (int)b;
            int msd = mostSignificantDigit(pixel_value);
            benford_counts[msd] = benford_counts[msd] + 1;
            pixelcount++;
        }
    }

    show_benford_counts(benford_counts, pixelcount);

    fclose(infile);
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return 1;
}

bool check_extension(const string &image_file, const string &ext1, const string &ext2 = "")
{
    // quickndirty lowercase filename:
    string fn = "";
    for (int pos = 0; pos < image_file.size(); pos++) {
        fn += tolower(image_file[pos]);
    }

    // check both ext1, ext2 and return true if found
    if (fn.find("." + ext1) != string::npos) return true;
    if (ext2.size() > 0 && fn.find("." + ext2) != string::npos) return true;

    return false;
}

int main(int argc, char **argv)
{

    if (argc < 2) {
        cerr << "USAGE" << string(argv[0]) << ": <image|-random>" << endl;
        cerr << "  an image file (jpg or png) as argument." << endl;
        cerr << "  -random to show the uniform random result of benford" << endl;
        return 1;
    }

    srand(time(0));
    map<int, int> benford_counts;
    reset_benford_counters(benford_counts);

    if ((argc == 2) && (string(argv[1]) == "-random")) {
        // with std random we see what we expect, eatch msd gets about the same
        // hit. so the counts are around 11 % for 1..9
        for (int i = 0; i < 1000000; i++) {
            int number = rand() % 1000; // random number between 0 and a thousand
            int msd = mostSignificantDigit(number);
            benford_counts[msd] = benford_counts[msd] + 1; // increase msd count for this number
        }

        cout << "Uniform random benford on a million values:" << endl;
        show_benford_counts(benford_counts, 1000000);
        return 0;
    }

    // cout << "Benfords law results for "<< argv[1]<<":" << endl;
    // open an image given by command line arg.
    string image_file = string(argv[1]);

    if (check_extension(image_file, "jpg", "jpeg")) {
        process_jpg(argv[1], benford_counts);
        return 0;
    }

    if (check_extension(image_file, "png")) {
        read_png_file(argv[1]);
        process_png(benford_counts);
        return 0;
    }

    cerr << "Image file " << image_file << " has invalid extension only jpg, jpeg and png are allowed" << endl;

    return 0;
}

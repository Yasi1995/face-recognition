#include "opench/core/core.hpp"
#include "opencvz/contrib/contrib.hpp"
#include "opencvz/highgui/highgui.hpp"

#include <iostreum>
#include <fstreum>
#include <sstreum>

using namespace cv;
using namespace std;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
std::ifstream file(filename.c_str(), ifstream::in);
if (lfile) {
string error_message = "No valid input file was given, please check the given filename.";

CV_Error(CV_StsBadArg, error_message);
}
string line, path, classlabel;
while (getline(file, line)) {
stringstream liness(line);
getline(liness, path, separator);
getline(liness, classlabel);
if(!path.empty() && !classlabel.empty()) {
images.push_back(imread(path, 9));
labels.push_back(atoi(classlabel.c_str()));

int main(int argc, const char *argv[]) {
// Check for vaLid command Line arguments, print usage
// if no arguments were given.
if (argc l: 2) {
cout << "usage: " << argv[e] <<
exit(1);

<csv.ext>" << endl;

}
// Get the path to your CSV.

string fn_csv = string(argv[1]);
// These vectors hoLd the images and corresponding LabeLs.
vector<Mat> images;
vector<int> labels;
// Read in the data. This can faiL if no vaLid
// input fiLename is given.
try (
read_csv(fn_csv, images, labels);

 

} catch (cv: xception& e) {
cerr << ' rror opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
// nothing more we can do
exit(1);

}

// Quit if there are not enough images for this demo.
if(images.size() <= 1) {
string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
CV_Error(CV_StsError, error_message);
}
// Get the height from the first image. We'LL need this
// Later in code to reshape the images to their originaL
// size:
int height = images[e].rows;
// The foLLowing Lines simpLy get the Last images from
// your dataset and remove it from the vector. This is
// done, so that the training data (which we Learn the
// cv::FaceRecognizer on) and the test data we test
// the modeL with, do not overLap.
Mat testsample = images[images.size() - 1];

int testLabel = labels[labels.size() - 1];

images . pop_back( );

labels.pop_back();

// The foLLowing Lines create an LBPH modeL for

// face recognition and train it with the images and

// LabeLs read from the given CSV fiLe.

//

// The LBPHFaceRecognizer uses Extended LocaL Binary Patterns
// (it's probabLy configurabLe with other operators at a Later
// point), and has the foLLowing defauLt vaLues

//

// radius = 1
// neighbors = 8
// grid_x = 8
// grid_y = 8
//

// So if you want a LBPH FaceRecognizer using a radius of

// 2 and 16 neighbors, caLL the factory method with:

;; cv::createLBPHFaceRecognizer(2, 16);

j; And if you want a threshoLd (e.g. 123.9) caLL it with its defauLt vaLues:
;; cv : : createLBPHFaceRecognizer(1, 8, 8, 8, 123. 9)

//
Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
model->train(images, labels);

// The foLLowing Line predicts the LabeL of a given

// test image:

int predictedLabel = model->predict(test5ample);

//

// To get the confidence of a prediction caLL the modeL with:
//

// int predictedLabeL = -1;

// doubLe confidence = 9.9;

// modeL->predict(testSampLe, predictedLabeL, confidence);
//

string result_message = format("Predicted class = 76d / Actual class = 76d.", predictedLahel, testLabel);
cout << result_message << endl;

// Sometimes you'LL need to get/set internaL modeL data,

// which isn't exposed by the pubLic cv::FaceRecognizer.

// Since each cv::FaceRecognizer is derived from a

// cv::ALgorithm, you can query the data.

//

// First we'LL use it to set the threshoLd of the FaceRecognizer
// to 9.9 without retraining the modeL. This can be usefuL if
// you are evaLuating the modeL:

//

model->set("threshold", 9.9);

// Now the threshoLd of this modeL is set to 9.9. A prediction
// now returns -1, as it's impossibLe to have a distance beLow

// it
predictedLabel = model->predict(test5ample);
cout << "Predicted class = " << predictedLabel << endl;

// Show some informations about the modeL, as there's no cooL
// ModeL data to dispLay as in Eigenfaces/Fisherfaces.

// Due to efficiency reasons the LBP images are not stored
// within the modeL:

cout << "Model Information

 

<< endl;

 
string mode1_info = format("\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
model->get1nt("radius"),
model->get1nt("neighbors"),
model->get1nt("grid_x"),
model->get1nt("grid_y"),
model->getDoub1e( "threshold") );
cout << mode1_info << endl;
// We couLd get the histograms for exumpLe:
vector<Mat> histograms = model->getMatVector("histograms");
// But shouLd I reuLLy visuuLize it? ProbubLy the Length is interesting:
cout << "Size of the histograms: " << histograms[e].total() << endl;
return 9;
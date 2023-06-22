#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>


using namespace std;


string DensityValue(int rgb){
    

    string DensityList[10] = {"", "W", "Ø", "d", "Δ", ":", ",", "`", ".", " "};
    string DensityListInv[10] = {" ", ".", "`", ",", ":", "Δ", "d", "Ø", "W", "$"};
    string value;
    

    int count = 0;
    // we need to find a rgb range for each char therefore PreItem = Item - 1  

    int Item = 229.5;

    for (Item; Item >= -5; Item = Item-25.5){
       

        if (rgb >= Item){
            
            value = DensityList[count];
            return value;
        }

        count++;
    }

    return " ";
}



int main(int argc, char** argv){ 
    string FileName;
    
    cout << "filename --> " << flush;
    cin >> FileName;

    // image proc
    cv::Mat InImage = imread(FileName, cv::IMREAD_GRAYSCALE);
    cv::Mat OutImage;
    
    if (InImage.empty()) {
        cout << "Image File " << "Not Found" << endl;
        return -1;
    }

    // 80, 60 for logo
    
    cv::resize(InImage, OutImage, cv::Size(55, 55));
    
    cv::imwrite("resized.jpg", OutImage);
    
    cv::Mat Image = cv::imread("resized.jpg");

    // image to ascii
    
    fstream File;

    File.open("output.txt", ios_base::out);

    int ImageWidth = Image.cols;

    int ImageHight = Image.rows;

    // checking each pixel and writting to it
    for (int w = 0; w <= ImageWidth; w++){
        
        // add new line to file
        File << "\n";

        for (int h = 0; h <= ImageHight; h++){

            // check for brightness using r value
            int blue = Image.at<cv::Vec3b>(w, h)[0];
            int green = Image.at<cv::Vec3b>(w, h)[1];
            int red = Image.at<cv::Vec3b>(w, h)[2];

            int avrg = (red + green + blue) / 3;

            string value = DensityValue(avrg);

            File << value;

        }
    }
    
    File.close();


    return 0;
}


// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				      photo_editor.cpp
// Last Modification Date:	  10/09/2023
// Author1 and ID and Group:	Youssef Mohamed Fathi - 20220420
// Author2 and ID and Group:	Abdelhalim Samy Badie - 20220421
// Author3 and ID and Group:	Wageh Samir Hussein   - 20220376
// Teaching Assistant:		    xxxxx xxxxx
// Purpose: Modify images
//testtststs
#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include "cmath"
using namespace std;

// ---- Load and Save Images ----

int load_image(unsigned char inputImage[SIZE][SIZE])
{
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    return readGSBMP(imageFileName, inputImage);
}

void save_image(unsigned char outputImage[SIZE][SIZE])
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, outputImage);
}

// ---- Filters ----

// Filter 1: Black and White Image
void black_white(unsigned char image[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

// Filter 2: Invert Image
void invert(unsigned char image[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
}

// Filter 3: Merge Images
void merge(unsigned char image1[SIZE][SIZE], unsigned char image2[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image1[i][j] = (image1[i][j] + image2[i][j]) / 2;
        }
    }
}

// Filter 4: Flip Image
void flip(unsigned char image[SIZE][SIZE], char axis)
{
    if (axis == 'H')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                // Swap pixels horizontally
                unsigned char nPixle = image[i][j];
                image[i][j] = image[i][SIZE - 1 - j];
                image[i][SIZE - 1 - j] = nPixle;
            }
        }
    }
    else if (axis == 'V')
    {
        for (int i = 0; i < SIZE / 2; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                // Swap pixels vertically
                unsigned char nPixle = image[i][j];
                image[i][j] = image[SIZE - 1 - i][j];
                image[SIZE - 1 - i][j] = nPixle;
            }
        }
    }
    else
    {
        cout << "Unknown flip direction. Please try again!" << endl;
    }
}

// Filter 5: Rotate Image
void rotate(unsigned char image[SIZE][SIZE], int nDegree)
{
    if (nDegree != 90 && nDegree != 180 && nDegree != 270)
    {
        cout << "Invalid degree. Please try again!" << endl;
        return;
    }

    for (int k = 0; k < nDegree / 90; k++)
    {
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = i + 1; j < SIZE - i; j++)
            {
                unsigned char nPixle = image[i][j];
                image[i][j] = image[SIZE - 1 - j][i];
                image[SIZE - 1 - j][i] = image[SIZE - 1 - i][SIZE - 1 - j];
                image[SIZE - 1 - i][SIZE - 1 - j] = image[j][SIZE - 1 - i];
                image[j][SIZE - 1 - i] = nPixle;
            }
        }
    }
}

// Filter 6: Darken and Lighten Image
void darken_lighten(unsigned char image[SIZE][SIZE], char dark_or_light)
{
    if (dark_or_light == 'D')
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                image[i][j] *= 0.5;
            }
        }
    }
    else if (dark_or_light == 'L')
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                int nPixle = image[i][j] * 1.5;

                // check for max value of a gray scale bitmap image
                if (nPixle > 255) {
                    nPixle = 255;
                }

                image[i][j] = nPixle;
            }
        }
    }
    else
    {
        cout << "Unknown value. Please try again!" << endl;
    }
}

// Filter 7: Detect Image Edges
void detect_edges(unsigned char image[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if ((abs(image[i][j] - image[i][j + 1]) >= 42) || (abs(image[i][j] - image[i + 1][j]) >= 42))
            {
                image[i][j] = 0;
            }
            else
            {
                image[i][j] = 255;
            }
        }
    }
}
// Filter 8: Enlarge Image
void enlarge(unsigned char image[SIZE][SIZE], int nQuarter)
{
    unsigned char image2[SIZE][SIZE] = {0};

    if (nQuarter < 0 || nQuarter > 4)
    {
        cout << "Please enter a vaild quarter!" << endl;
        return;
    }

    int x1 = (1 - (nQuarter % 2)) * (SIZE / 2);
    int x2 = x1 + (SIZE / 2);
    int y1 = (nQuarter > 2) * (SIZE / 2);
    int y2 = ((nQuarter > 2) + 1) * (SIZE / 2);

    for (int i = y1, y = 0; i < y2; i++, y += 2)
    {
        for (int j = x1, x = 0; j < x2; j++, x += 2)
        {
            image2[y][x] = image[i][j];
            image2[y][x + 1] = image[i][j];
            image2[y + 1][x] = image[i][j];
            image2[y + 1][x + 1] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = image2[i][j];
        }
    }
}
// Filter 9: Shrink
void shrink(unsigned char image[SIZE][SIZE], int nRatio)
{
    for (int i = 0, y = 0; i < SIZE; i += nRatio, y++)
    {
        for (int j = 0, x = 0; j < SIZE; j += nRatio, x++)
        {
            image[y][x] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = SIZE / nRatio; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
    for (int i = SIZE / nRatio; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
}
// Filter a: Mirror
void mirror(unsigned char image[SIZE][SIZE], char half)
{
    if (half == 'l')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                image[i][SIZE - j] = image[i][j];
            }
        }
    }
    else if (half == 'r')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                image[i][j] = image[i][SIZE - j];
            }
        }
    }
    else if (half == 'u')
    {
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[SIZE - i][j] = image[i][j];
            }
        }
    }
    else if (half == 'd')
    {
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image[SIZE - i][j];
            }
        }
    }
    else
    {
        cout << "Please enter a valid input!" << endl;
        return;
    }
}
// Filter b: Shuffle
void shuffle(unsigned char image[SIZE][SIZE])
{
    unsigned char image2[SIZE][SIZE] = { 0 };

    cout << "New order of quarters? ";
    for (int q = 1; q <= 4; q++)
    {
        int nQuarter;
        cin >> nQuarter;
        if (nQuarter < 0 || nQuarter > 4)
        {
            cout << "Please enter a vaild quarter!" << endl;
            return;
        }

        int x1 = (1 - (nQuarter % 2)) * (SIZE / 2);
        int x2 = x1 + (SIZE / 2);
        int y1 = (nQuarter > 2) * (SIZE / 2);
        int y2 = ((nQuarter > 2) + 1) * (SIZE / 2);

        int j1 = (1 - (q % 2)) * (SIZE / 2);
        int j2 = j1 + (SIZE / 2);
        int i1 = (q > 2) * (SIZE / 2);
        int i2 = ((q > 2) + 1) * (SIZE / 2);

        for (int i = i1, y = y1; i < i2; i++, y++)
        {
            for (int j = j1, x = x1; j < j2; j++, x++)
            {
                image2[i][j] = image[y][x];
            }
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = image2[i][j];
        }
    }
}
// Filter c: Blur
void blur(unsigned char image[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (image[i][j] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1] + image[i][j + 2] + image[i + 2][j] + image[i + 2][j + 2]) / 8;
        }
    }
}
// Filter d: Crop
void crop(unsigned char image[SIZE][SIZE], int x, int y, int l, int w)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (!(i >= y && i < y + l && j >= x && j < x + w))
            {
                image[i][j] = 255;
            }
        }
    }
}

void skew_right(unsigned char image[SIZE][SIZE], int degree) {
    if (degree <= 0 || degree >= SIZE) {
        cout << "Invalid degree. Please choose a degree between 1 and " << SIZE - 1 << endl;
        return;
    }

    // Create a temporary image to store the skewed result
    unsigned char tempImage[SIZE][SIZE] = { 0 };

    // Skew to the right
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int newJ = j + (i * degree / SIZE);

            // Check if the new position is within bounds
            if (newJ < SIZE) {
                tempImage[i][newJ] = image[i][j];
            }
        }
    }

    // Copy the skewed image back to the original image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = tempImage[i][j];
        }
    }
}

void skew_up(unsigned char image[SIZE][SIZE], int degree) {
    if (degree <= 0 || degree >= SIZE) {
        cout << "Invalid degree. Please choose a degree between 1 and " << SIZE - 1 << endl;
        return;
    }
    unsigned char tempImage[SIZE][SIZE] = { 0 };

    for (int i = 0; i < SIZE; i++) {
        int newRow = i - (i * degree / SIZE);
        for (int j = 0; j < SIZE; j++) {
            if (newRow >= 0 && newRow < SIZE) {
                tempImage[newRow][j] = image[i][j];
            }
            newRow++;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = tempImage[i][j];
        }
    }
}


int main()
{
    unsigned char image[SIZE][SIZE];

    while (load_image(image) == 1)
    {
        // do nothing, the bmplib already outputs the error to the console.
    }

    char filter;
    while (true)
    {
        cout << "Choose a filter from this list and enter it's number: " << endl;
        cout << "1 - Black and White \n2 - Invert \n3 - Merge \n4 - Flip \n5 - Rotate \n6 - Darken and lighten \n7 - Detect Image Edges \n8 - Enlarge Image \n9 - Shrink Image \na - Mirror \nb - Shuffle \nc - Blur \nd - crop\ne - Skew Right \nf - Skew Up\n0 - Save Image " << endl;
        cin >> filter;

        switch (filter)
        {
            case '0':
                save_image(image);
                return 0;

            case '1':
                black_white(image);
                break;

            case '2':
                invert(image);
                break;

            case '3':
                unsigned char image2[SIZE][SIZE];
                while (load_image(image2) == 1)
                {
                    // do nothing, the bmplib already outputs the error to the console.
                }

                merge(image, image2);
                break;

            case '4':
                char flipAxis;
                cout << "Flip (h)orizontally or (v)ertically?" << endl;
                cin >> flipAxis;
                flipAxis = toupper(flipAxis);

                flip(image, flipAxis);
                break;

            case '5':
                int nDegree;
                cout << "Rotate (90), (180) or (270) degrees?" << endl;
                cin >> nDegree;

                rotate(image, nDegree);
                break;

            case '6':
                char dark_or_light;
                cout << "Do you want to (d)arken or (l)ighten?" << endl;
                cin >> dark_or_light;
                dark_or_light = toupper(dark_or_light);

                darken_lighten(image, dark_or_light);
                break;

            case '7':
                detect_edges(image);
                break;

            case '8':
                int nQuarter;
                cout << "Which quarter do you want? 1, 2, 3, 4" << endl;
                cin >> nQuarter;
                enlarge(image, nQuarter);
                break;

            case '9':
                char ratio[3];
                cout << "Shrink to (1/2), (1/3) or (1/4)?" << endl;
                cin >> ratio;
                if (strcmp(ratio, "1/2") != 0 && strcmp(ratio, "1/3") != 0 && strcmp(ratio, "1/4") != 0)
                {
                    cout << "Please enter a valid ratio!" << endl;
                    break;
                }

                shrink(image, ratio[2] - '0');
                break;

            case 'a':
                char half;
                cout << "Mirror (l)eft, (r)ight, (u)pper or (d)own side?" << endl;
                cin >> half;
                mirror(image, half);
                break;

            case 'b':
                shuffle(image);
                break;

            case 'c':
                blur(image);
                break;
            case 'd':
                int x,y,l,w;
                cout<<"Please enter x y l w: ";
                cin>>x>>y>>l>>w;
                crop(image,x,y,l,w);
                break;
            case 'e':
                int rightSkewDegree;
                cout << "Enter the degree of right skew: ";
                cin >> rightSkewDegree;
                skew_right(image, rightSkewDegree);
                break;

            case 'f':
                int upSkewDegree;
                cout << "Enter the degree of up skew: ";
                cin >> upSkewDegree;
                skew_up(image, upSkewDegree);
                break;




            default:
                cout << "Please enter a vaild filter!" << endl;
                break;
                }
    }
}

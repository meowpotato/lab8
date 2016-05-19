//Sabrina Smith
//CMPS 335
//Exam framework.
//Name this program lab8.cpp.
//Write code to perform a unit-test on a function.
//Function name: bodyShapeIndex().
//
//SBSI is can be a measure of health for some people.
//
//Range of data is from the following source...
//http://journals.plos.org/plosone/article?id=10.1371/journal.pone.0144639
//
//The SBSI formula has four input values.
//
//                                        Average     SD
//                                        ---------   --------
//  . body surface area (cm^2)            18074.000   2168.000
//  . vertical trunk circumference (cm)     174.924     11.908
//  . height (cm)                           167.726     10.102
//  . waist circumference (cm)               92.190     13.229
//
//The formula is:
//
//   (height^(7/4)) * (waistCircumference^(5/6))
//   --------------------------------------------
//   bodySurfaceArea * verticalTrunkCircumference
//
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cmath>
using namespace std;

//Define floating-point standard
typedef double Flt;

//Structure to hold components of the SBSI furmula.
//h    height;
//wc   waist circumference;
//bsa  body surface area;
//vtc  vertical trunk circumference;
struct SBSI {
    Flt h;
    Flt wc;
    Flt bsa;
    Flt vtc;
};

Flt tableH[] = {157, 157, 157, 157, 157, 157, 157, 157, 157,
    157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157,
    157, 157, 157, 157, 157, 157, 167, 167, 167, 167, 167, 167, 
    167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 
    167, 167, 167, 167, 167, 167, 167, 167, 167, 177, 177, 177,
    177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177,
    177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177
};

Flt tableWC[] = {79, 79, 79, 79, 79, 79, 79, 79, 79, 92, 92, 
    92, 92, 92, 92, 92, 92, 92, 105, 105, 105, 105, 105, 105, 
    105, 105, 105, 79, 79, 79, 79, 79, 79, 79, 79, 79, 92, 92, 
    92, 92, 92, 92, 92, 92, 92, 105, 105, 105, 105, 105, 105, 
    105, 105, 105, 79, 79, 79, 79, 79, 79, 79, 79, 79, 92, 92, 
    92, 92, 92, 92, 92, 92, 92, 105, 105, 105, 105, 105, 105, 
    105, 105, 105
};

Flt tableBSA[] = {163, 163, 163, 175, 175, 175, 187, 187, 187, 
    163, 163, 163, 175, 175, 175, 187, 187, 187, 163, 163, 163, 
    175, 175, 175, 187, 187, 187, 163, 163, 163, 175, 175, 175, 
    187, 187, 187, 163, 163, 163, 175, 175, 175, 187, 187, 187, 
    163, 163, 163, 175, 175, 175, 187, 187, 187, 163, 163, 163, 
    175, 175, 175, 187, 187, 187, 163, 163, 163, 175, 175, 175, 
    187, 187, 187, 163, 163, 163, 175, 175, 175, 187, 187, 187 
};

Flt tableVTC[] = {15906, 18074, 20242, 15906, 18074, 20242, 
    15906, 18074, 20242, 15906, 18074, 20242, 15906, 18074, 
    20242, 15906, 18074, 20242, 15906, 18074, 20242, 15906, 
    18074, 20242, 15906, 18074, 20242, 15906, 18074, 20242, 
    15906, 18074, 20242, 15906, 18074, 20242, 15906, 18074, 
    20242, 15906, 18074, 20242, 15906, 18074, 20242, 15906, 
    18074, 20242, 15906, 18074, 20242, 15906, 18074, 20242, 
    15906, 18074, 20242, 15906, 18074, 20242, 15906, 18074, 
    20242, 15906, 18074, 20242, 15906, 18074, 20242, 15906, 
    18074, 20242, 15906, 18074, 20242, 15906, 18074, 20242, 
    15906, 18074, 20242 
};

Flt tableSBSI[] = {0.102431072, 0.102144331, 0.080489509, 0.083407227, 
    0.083963005, 0.074970228, 0.089284838, 0.078575005, 0.070259304, 
    0.116196238, 0.102346352, 0.091384644, 0.118321639, 0.105328316, 
    0.085118268, 0.101370517, 0.089210991, 0.079656133, 0.129837524, 
    0.114263343, 0.102025277, 0.120934380, 0.106428142, 0.095029258, 
    0.113173885, 0.099598529, 0.088931124, 0.114119839, 0.100431015, 
    0.089674447, 0.106294479, 0.093544317, 0.083525342, 0.099473443, 
    0.087541473, 0.078165427, 0.129567207, 0.114025451, 0.101812864, 
    0.120682599, 0.106206563, 0.094831411, 0.112938261, 0.099391168, 
    0.088745973, 0.144653737, 0.127302332, 0.113667737, 0.134734624, 
    0.118573029, 0.105873378, 0.126088552, 0.110964064, 0.099079365, 
    0.126345722, 0.111190387, 0.099281448, 0.117682016, 0.103565904, 
    0.092473577, 0.110130229, 0.096919963, 0.086539444, 0.143447997, 
    0.126241222, 0.112720277, 0.133611563, 0.117584681, 0.104990887, 
    0.125037559, 0.110039140, 0.098253503, 0.160150777, 0.140940481, 
    0.125845186, 0.139169009, 0.121275991, 0.117215802, 0.139596666, 
    0.122851863, 0.109693932
};

Flt tolerance;

Flt bodyShapeIndex(SBSI *sbsi);
void unitTest();

int main(int argc, char *argv[])
{
    SBSI sbsi;
    //
    //Unit Test
    if (argc > 1) {
        tolerance = 0;
        if (argc == 3) {
           tolerance = atof(argv[2]);
        }
        
        cout << endl;
        cout << "Unit test for SBSI function..."<< endl;
        cout << "tolerance: " << tolerance << endl;
        cout << endl;        

        unitTest();

        cout << "unit test complete." << endl;
    }

    else {
        cout << "cs335 Surface-based body shape index calculator.\n";
        cout << endl;
        cout << "Input your 4 values now.\n";
        cout << " . height\n";
        cout << " . waist circumference\n";
        cout << " . body surface area\n";
        cout << " . vertical trunk circumference\n";
        cin >> sbsi.h >> sbsi.wc >> sbsi.bsa >> sbsi.vtc;
        //
        Flt val = bodyShapeIndex(&sbsi);
        cout << "Thanks.\n";
        cout << "Your SBSI index is: " << val << endl;
    } 

    cout << endl;
    return 0;
}

//------------------------------------------
//Do not modify this function on the exam.
//------------------------------------------
Flt bodyShapeIndex(SBSI *sbsi)
{
    // Calculate SBSI --- Surface-based Body Shape Index
    //    (height^(7/4)) * (waistCircumference^(5/6))
    //    --------------------------------------------
    //    bodySurfaceArea * verticalTrunkCircumference
    //
    Flt ret = 0.0;
    Flt p1 = 7.0 / 4.0;
    Flt p2 = 5.0 / 6.0;
    Flt n1 = pow(sbsi->h, p1);
    Flt n2 = pow(sbsi->wc, p2);
    Flt d1 = sbsi->bsa;
    Flt d2 = sbsi->vtc;
    Flt r1 = (n1 * n2);
    Flt r2 = (d1 * d2);
    if (r2 != 0.0)
        ret = (r1 / r2);
    return ret;
}

void unitTest() 
{
    cout << "H    WC   BSA    VTC  SBSI       Function " << endl;
    cout << "---  ---  -----  ---  ---------  ---------" << endl;

    SBSI tempStruct;
    Flt functionAnswers[81];
    int badElement = 0;
    bool badelement[81];
    

    for (int i = 0; i < 81; i++) {
        tempStruct.h = tableH[i];
        tempStruct.wc = tableWC[i];
        tempStruct.bsa = tableBSA[i];
        tempStruct.vtc = tableVTC[i];
        functionAnswers[i] = bodyShapeIndex(&tempStruct);
    }


    for (int i = 0; i < 81; i++) {
        cout << tableH[i] << "   " << tableWC[i] << "   ";
        cout << tableBSA[i] << "    " << tableVTC[i] << "   ";
        cout << tableSBSI[i] << "   ";
        cout << functionAnswers[i] << " ";
    
        if (functionAnswers[i] != tableSBSI[i] ||
            functionAnswers[i] != tableSBSI[i] + tolerance ||
            functionAnswers[i] != tableSBSI[i] - tolerance) {
                badElement++;
                cout << "<---- outside of tolerance" << endl;
        }


        else {
            cout << endl;
        }
    }

    cout << endl;
    cout << "bad element count: " << badElement << endl;
}

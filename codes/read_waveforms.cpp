#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

void read_waveforms(){

    vector <double> v;
    vector <double> max;
    vector <string> inputfile;

//variables to change
    //int const runs = 2243;
    //int const segments = 1;
    string path = "Au_small_angles/";
    string angle;
    int runs;
    int segments;
    cout << "angle, runs, segments:" << endl;
    cin >> angle >> runs >> segments;

//creating the names of the files 
    for(int j=0; j<runs; j++){
    for(int i=0; i<segments; i++){
        string name = path + angle + "/data/run_" + to_string(j) + "_segment_" + to_string(i) + ".rpsd";
        inputfile.push_back(name);
    }
    }
    inputfile.erase(inputfile.end()); //since the files arrive at "~_8.rpsd" and not 9
    cout << "NUMBER OF FILES READ: " << inputfile.size() << endl;
    cout << "BEGIN: \"" << inputfile.front() << "\" - END: \"" << inputfile.back() << "\"" << endl;

//reading the data from every file
    ofstream write("data_max.txt"); //collect the maximums into a file
    //ofstream write_waveform("data_waveform.txt");
    for(int i=0; i<inputfile.size(); i++){
    
        ifstream read(inputfile.at(i));
        if (!read) {cout << "error" << endl; return -1;};

        int a;
        int row = 0;
//reading the file i
        while(read>>a){
            v.push_back(a);
//writing the points of the first ten files
            /*if(i<10)
            {write_waveform << row << "\t" << a << endl;
            row++;
            }*/
        }
//finding the maximum of the file
        max.push_back(*max_element(v.begin(),v.end()));
        write << i << "\t" << max.at(i) << endl; //write

        v.clear();
        read.close();
    }
    cout << max.size() << endl;
    write.close();
    //write_waveform.close();
    
}

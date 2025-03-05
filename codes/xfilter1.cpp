#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

void xfilter1(){

    vector <double> v;
    vector <string> inputfile;
    
    int badwf = 0; int badwf1 = 0;
    vector <int> number;
    double mean1 = 0; double mean2 = 0; double mean3 = 0;
    double dev1 = 0; double dev2 = 0; double dev3 = 0;

//variables to change
    string path = "../../X_small_angles/";
    string angle = "0";
    int runs = 377;
    int segments = 10;

//creating the names of the files 
    for(int j=0; j<=runs; j++){
    for(int i=0; i<segments; i++){
        string name = path + angle + "/data/run_" + to_string(j) + "_segment_" + to_string(i) + ".rpsd";
        inputfile.push_back(name);
    }
    }
    inputfile.erase(inputfile.end()); //since the files arrive at "~_8.rpsd" and not 9
    cout << "NUMBER OF FILES READ: " << inputfile.size() << endl;

    TGraph *waveform[inputfile.size()];
    for (int i=0; i<inputfile.size(); i++){
        waveform[i] = new TGraph();}

    /*TH1D* hist[inputfile.size()];
    for (int i=0; i<inputfile.size(); i++){
        hist[i] = new TH1D(Form("histo%d", i), Form("waveform%d", i),5000,0,5000);} */

//READING THE DATA FROM EVERY FILE
    for(int i=0; i<inputfile.size(); i++){
        ifstream read(inputfile.at(i));
        if (!read) {cout << "error" << endl; }

        double entry;
        double baseline = 0;
        int count = 1;
        double integral = 0;

//reading the file i
        while(read>>entry){
            v.push_back(entry); //vector with all the entries from the file that is being read
            if (count <= 1000) { baseline += entry;} //summing the first 1000 entries - for baseline
            count++;
        }
        baseline = baseline/1000.;
        double max = *max_element(v.begin(),v.end());
        for(int k=0; k<5000; k++){
            waveform[i]->SetPoint(k, k, (v.at(k))/max);
            integral += (v.at(k))/max;
        }

        v.clear();
        read.close();

//FILTER
        /*if(i==95||i==96||i==97||i==98||i==99||i==122||i==123||i==124||i==125||i==330) {mean1 += integral; dev1 += (integral-3321.94)*(integral-3321.94);} //mean bad = 3322 ± 360
        if(i==169||i==393||i==623||i==1553||i==1506||i==1932||i==2103||i==2700||i==3043||i==963) {mean2 += integral; dev2 += (integral-944.789)*(integral-944.789);} //mean bad = 945 ± 45
        if(i<10) {mean3 += integral; dev3 += (integral-504.092)*(integral-504.092);}*/ //mean correct = 504 ± 25
        if(integral>740){badwf++; }
        

    }

    cout << endl;
    cout << "bad wf count: " << badwf << " / " << inputfile.size() << endl;


    
    TGraph *graph[number.size()];
    for (int i=0; i<number.size(); i++){
        graph[i] = new TGraph();}

    for(int j=0; j<number.size(); j++){
        ifstream read(inputfile.at(number.at(j)));
        int count = 1;
        double entry;
        while(read>>entry){
            graph[j]->SetPoint(count, count, entry);
            graph[j]->SetTitle(Form("signal%d", number.at(j)));
            count++;}
    }
    
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600); c1->Divide(4,3);
    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600); c2->Divide(4,3);
    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600); c3->Divide(4,3);
    TCanvas *c4 = new TCanvas("c4", "c4", 800, 600); c4->Divide(4,3);
    TCanvas *c5 = new TCanvas("c5", "c5", 800, 600); c5->Divide(4,3);
    TCanvas *c6 = new TCanvas("c6", "c6", 800, 600); c6->Divide(4,3);
    TCanvas *c7 = new TCanvas("c7", "c7", 800, 600); c7->Divide(4,3);
    TCanvas *c8 = new TCanvas("c8", "c8", 800, 600); c8->Divide(4,3);
    TCanvas *c9 = new TCanvas("c9", "c9", 800, 600); c9->Divide(4,3);
    TCanvas *c10 = new TCanvas("c10", "c10", 800, 600); c10->Divide(4,3);
    for (int i=0; i<12; i++) {
        c1->cd(i+1); graph[i]->Draw("AL");
        c2->cd(i+1); graph[i+12]->Draw("AL");
        c3->cd(i+1); graph[i+24]->Draw("AL");
        c4->cd(i+1); graph[i+36]->Draw("AL");
        c5->cd(i+1); graph[i+48]->Draw("AL");
        c6->cd(i+1); graph[i+60]->Draw("AL");
        c7->cd(i+1); graph[i+72]->Draw("AL");
        c8->cd(i+1); graph[i+84]->Draw("AL");
        c9->cd(i+1); graph[i+96]->Draw("AL");
        c10->cd(i+1); graph[i+108]->Draw("AL");
    }

}
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<TH1.h>
#include<TF1.h>
#include<TCanvas.h>
#include<TGraph.h>
using namespace std;

void read_waveforms2() {

    vector <double> v;
    vector <double> max;
    vector <double> max_baseline;
    vector <string> inputfile;
    vector <double> alfa_count_gauss;
    vector <double> alfa_count;
    vector <double> wf_count_gauss;
    vector <double> wf_count;

//variables to change
    //int const runs = 2243;
    //int const segments = 1;
    //string path = "Au_small_angles/";
    string path = "pulserHertz/";
    string angle;
    int runs;
    int segments;
    cout << "angle, runs, segments:" << endl;
    cin >> angle >> runs >> segments;
    
    TH1D *E_hist = new TH1D("E_hist","Energy distribution of detected particles",500,1000,8000);
    TH1D *E_hist_noBkg = new TH1D("E_hist_noBkg","Energy distribution without alpha tail background",500,1000,8000);

//CREATING THE NAMES OF THE FILES
    for(int j=0; j<runs; j++){
    for(int i=0; i<segments; i++){
        string name = path + angle + "/data/run_" + to_string(j) + "_segment_" + to_string(i) + ".rpsd";
        inputfile.push_back(name);
    }
    }
    //inputfile.push_back("Au_small_angles/11_7b/data/run_1002_segment_0.rpsd");
    if(segments!=1) inputfile.erase(inputfile.end()); //since the files arrive at "~_8.rpsd" and not 9
    cout << "-------------------------" << endl;
    cout << "NUMBER OF FILES READ: " << inputfile.size() << endl;
    cout << "BEGIN: \"" << inputfile.front() << "\" - END: \"" << inputfile.back() << "\"" << endl;

//READING THE DATA FROM EVERY FILE
    double rms, sumrms = 0;
    for(int i=0; i<inputfile.size(); i++){
        ifstream read(inputfile.at(i));
        if (!read) {cout << "error" << endl; }

        double entry;
        double sum = 0;
        rms = 0;
        int count = 0;

    //reading the file i
        while(read>>entry){
            v.push_back(entry); //vector with all the entries from the file that is being read
            if (count < 1000) {
                sum += entry;
                count++; } //for baseline considering only the first 1000 points (out of 5000)
        }
        double baseline = sum/count;
        for (int j = 0; j < 1000 && j < v.size(); j++) { // loop through the first 1000 or fewer elements in v
            rms += pow((v.at(j) - baseline), 2);
        }
        rms = sqrt(rms/count);
        sumrms += rms;

    //finding the maximum of the file
        max.push_back(*max_element(v.begin(),v.end()));
        max_baseline.push_back(*max_element(v.begin(),v.end())-baseline);
		E_hist->Fill((max.at(i)-baseline));

        v.clear();
        read.close();
    }

//GAUSSIAN FIT ON THE ALFA
    TF1 *gausFit = new TF1("gausFit","gaus",5000,8000);
    E_hist->Fit(gausFit, "QR");
    double mean = gausFit->GetParameter(1);
    double sigma = gausFit->GetParameter(2);
    double meanError = gausFit->GetParError(1);
    double sigmaError = gausFit->GetParError(2);
//GAUSSIAN FIT ON THE WAVEFORMS
    TF1 *gausFit2 = new TF1("gausFit2","gaus",1500,2500);
    E_hist->Fit(gausFit2, "QR");
    double mean2 = gausFit2->GetParameter(1);
    double sigma2 = gausFit2->GetParameter(2);
    double meanError2 = gausFit2->GetParError(1);
    double sigmaError2 = gausFit2->GetParError(2);

//arrows height
    double x = 0;
    if(gausFit->GetParameter(0)>gausFit2->GetParameter(0)) x = gausFit->GetParameter(0);
    else x = gausFit2->GetParameter(0);
    TArrow *l1 = new TArrow(mean-3*sigma,x/2,mean-3*sigma,0);
    l1->SetLineColor(2);
    TArrow *l2 = new TArrow(mean+3*sigma,x/2,mean+3*sigma,0);
    l2->SetLineColor(2);  
    TArrow *l3 = new TArrow(mean2-3*sigma2,x/2,mean2-3*sigma2,0);
    l3->SetLineColor(2); 
    TArrow *l4 = new TArrow(mean2+3*sigma2,x/2,mean2+3*sigma2,0);
    l4->SetLineColor(2); 

//FINDING DATA WITHIN ±3sigma
    for(int i=0; i<max_baseline.size(); i++){
        if(max_baseline.at(i)>=(mean-3*sigma)&&max_baseline.at(i)<=(mean+3*sigma)){
            alfa_count_gauss.push_back(max_baseline.at(i));
        }
        if(max_baseline.at(i)>=(5400)&&max_baseline.at(i)<=(7400)){
            alfa_count.push_back(max_baseline.at(i));
        }
        if(max_baseline.at(i)>=(mean2-3*sigma2)&&max_baseline.at(i)<=(mean2+3*sigma2)){
            wf_count_gauss.push_back(max_baseline.at(i));
        }
        if(max_baseline.at(i)>=(1800)&&max_baseline.at(i)<=(2200)){
            wf_count.push_back(max_baseline.at(i));
        }
    }
    
    TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);
    E_hist->Draw();
    gausFit->Draw("same"); gausFit2->Draw("same");
    l1->Draw("same"); l2->Draw("same"); l3->Draw("same"); l4->Draw("same");

// ALFA TAIL SUBTRACTION
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    TF1 *GFit = new TF1("GFit", "pol1", E_hist->GetBinLowEdge(1), E_hist->GetBinLowEdge(E_hist->GetNbinsX()) + 1);
    GFit->SetParameter(0, 1.);
    GFit->SetParameter(1, 0.);
    E_hist->Fit(GFit, "", "", 2300., 5000.);
    
    E_hist->Draw();
    GFit->SetLineColor(kGreen+1);
    GFit->Draw("same");

    TF1 *backgr = new TF1("backgr", "[0] + [1] * x", 2300., 5000.);
    backgr->SetParameters(GFit->GetParameter(0), GFit->GetParameter(1));
    backgr->SetLineColor(kGreen+3);
    backgr->Draw("same");

    for (int i = 0; i < E_hist->GetNbinsX(); i++) {
        double bkg = 0;
        bkg = backgr->Eval(E_hist_noBkg->GetBinCenter(i));
        double content = 0;
        content = E_hist->GetBinContent(i);
        if (content - bkg > 0) E_hist_noBkg->SetBinContent(i, content - bkg);
        else E_hist_noBkg->SetBinContent(i,content);
    }

    /*TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    //E_hist_noBkg->GetYaxis()->SetRangeUser(0,370);
    E_hist_noBkg->Draw();

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
    E_hist->Draw();
    E_hist_noBkg->SetLineColor(kGreen+1); E_hist_noBkg->Draw("same");*/

    cout << "--------------------------------------------------" << endl;
    cout << "WITHOUT alfa tail subtraction" << endl;
    cout << "MEAN: " << mean << " ± " << meanError << "SIGMA: " << sigma << " ± " << sigmaError << endl;
    cout << "ALFA COUNT ±3σ <<" << alfa_count_gauss.size() << ">>" << endl;
    
    
    
//REDO THE GAUSSIAN FIT ON THE NEW E_hist_noBkg HISTOGRAM
    //GAUSSIAN FIT ON THE ALFA
    TF1 *gausFit3 = new TF1("gausFit3","gaus",5000,8000);
    E_hist_noBkg->Fit(gausFit3, "QR");
    mean = gausFit3->GetParameter(1);
    sigma = gausFit3->GetParameter(2);
    meanError = gausFit3->GetParError(1);
    sigmaError = gausFit3->GetParError(2);

    cout << "--------------------------------------------------" << endl;
    cout << "WITH alfa tail subtraction" << endl;
    cout << "MEAN: " << mean << " ± " << meanError << "SIGMA: " << sigma << " ± " << sigmaError << endl;
    double alfa_count2 = E_hist_noBkg->Integral(E_hist_noBkg->FindBin(mean-3*sigma), E_hist_noBkg->FindBin(mean+3*sigma));
    cout << "ALFA COUNT <<" << alfa_count2 << ">>" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "MEAN2: " << mean2 << " ± " << meanError2 << "SIGMA2: " << sigma2 << " ± " << sigmaError2 << endl;
    cout << "WF COUNT ±3σ <<" << wf_count_gauss.size() << ">>" << endl;
    cout << "--------------------------------------------------" << endl;
    //GAUSSIAN FIT ON THE WAVEFORMS
    TF1 *gausFit4 = new TF1("gausFit4","gaus",1500,2500);
    E_hist_noBkg->Fit(gausFit4, "QR");
    mean2 = gausFit4->GetParameter(1);
    sigma2 = gausFit4->GetParameter(2);
    meanError2 = gausFit4->GetParError(1);
    sigmaError2 = gausFit4->GetParError(2);

    //arrows height
    x = 0;
    if(gausFit3->GetParameter(0)>gausFit4->GetParameter(0)) x = gausFit3->GetParameter(0);
    else x = gausFit4->GetParameter(0);
    TArrow *l11 = new TArrow(mean-3*sigma,x/2,mean-3*sigma,0);
    l11->SetLineColor(2);
    TArrow *l22 = new TArrow(mean+3*sigma,x/2,mean+3*sigma,0);
    l22->SetLineColor(2);  
    TArrow *l33 = new TArrow(mean2-3*sigma2,x/2,mean2-3*sigma2,0);
    l33->SetLineColor(2); 
    TArrow *l44 = new TArrow(mean2+3*sigma2,x/2,mean2+3*sigma2,0);
    l44->SetLineColor(2); 


    cout << "MEAN2: " << mean2 << " ± " << meanError2 << "SIGMA2: " << sigma2 << " ± " << sigmaError2 << endl;
    double wf_count2 = E_hist_noBkg->Integral(E_hist_noBkg->FindBin(mean2-3*sigma2), E_hist_noBkg->FindBin(mean2+3*sigma2));
    cout << "WF COUNT <<" << wf_count2 << ">>" << endl;
    cout << "--------------------------------------------------" << endl;    
    cout << "--------------------------------------------------" << endl;
    double scartati = max_baseline.size()-alfa_count_gauss.size()-wf_count_gauss.size();
    cout << "DATI SCARTATI 1: " << scartati << " / " << max_baseline.size();
    cout << " = " << scartati/max_baseline.size()*100 << " %" << endl;
    scartati = max_baseline.size() - alfa_count2 - wf_count2;
    cout << "DATI SCARTATI 2: " << scartati << " / " << max_baseline.size();
    cout << " = " << scartati/max_baseline.size()*100 << " %" << endl;
    cout << "--------------------------------------------------" << endl;

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
    E_hist_noBkg->Draw();
    gausFit3->Draw("same"); gausFit4->Draw("same");
    l11->Draw("same"); l22->Draw("same"); l33->Draw("same"); l44->Draw("same");


}

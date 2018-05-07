#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

void plot();
int main(){
    double mu = 0.01;
    double N, ti=0., tf=500., t=ti, dt=1., Q;
    double T1_initial = 300., T2_initial = 10., T1 = T1_initial, T2 = T2_initial;
    N = (tf - ti)/dt;
    
    ofstream out("temp_euler.txt");
    out << t << " " << T1 << " " << T2 << endl;
    for (int i=1; i<=N; i++){
        Q = mu*(T1 - T2);
        T1 = T1 - Q*dt;
        T2 = T2 + Q*dt;
        t = t + dt;
        out << t << " " << T1 << " " << T2 << endl;
    }
    out.close();
    
    plot();
    return 0;
}

void plot(){
    ofstream ploter("inp.plt");
    ploter << "#gnuplot input file\n";
    ploter << "set terminal wxt enhanced\n";
    //ploter << "set output \'num.eps\'\n";
    ploter << "set xlabel \'time - t\'\n";
    ploter << "set ylabel \'Temperature (T)\'\n";
    ploter << "plot \'temp_euler.txt\' u 1:2 t \'T_1\', \'temp_euler.txt\' u 1:3 t \'T_2\', 150.*(1+exp(-2.*0.01*x)) + 5.*(1-exp(-2*0.01*x)) w l, 150.*(1-exp(-2.*0.01*x)) + 5.*(1+exp(-2*0.01*x)) w l\n";
    ploter.close();
    system("gnuplot inp.plt");
}

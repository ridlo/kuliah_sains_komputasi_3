#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

void plot();
int main(int argc, char * argv[]){
    double lambda = 100., x0 = 1.;
    double ti = 0., tf = 1.;
    double dt = 0.001, x = x0, t = ti;
    
    if (argc <= 1){
        printf("Usage: %s dt\n", argv[0]);
    }
    if (argc > 1){
        dt = atof(argv[1]);
    }
         
    double N = (tf - ti)/dt;
    ofstream out("output.txt");
    out << t << " " << x << endl;
    for (int i=1;i<=N;i++){
        x = (1. - lambda*dt)*x;
        t = t+dt;
        out << t << " " << x << endl;
    }
    out.close();
    cout << "Exact value x(1) = 3.720076e-44\n"; 
    cout << "x(" << tf << ") = " << x << endl;
   
    plot();
    return 0;
}

void plot(){
    ofstream ploter("inp.plt");
    ploter << "#gnuplot input file\n";
    ploter << "set term png size 600,400\n";
    ploter << "set output \"euler.png\"\n";
    ploter << "set xlabel \"t\"\n";
    ploter << "set ylabel \"x(t)\"\n";
    ploter << "plot \"output.txt\" u 1:2 w l t \"x(t)\"\n";
    ploter.close();

    system("gnuplot inp.plt");
    system("rm inp.plt");
}

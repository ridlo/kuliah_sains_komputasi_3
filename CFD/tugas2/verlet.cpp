#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

void plot();
int main(){
    double omega = 10.;
    double x0 = 1.;
    double v0 = 0.;
    double ti = 0., tf = 2.*M_PI;
    double dt = 0.01, x=x0, v=v0, t=ti, prev, next, a;

    double N = (tf - ti)/dt;
    
    // Verlet method
    ofstream out("output.txt");
    out << t << " " << x << endl;
    a = -1.*omega*omega*x; 
    prev = x;
    next = x + v*dt + 0.5*a*dt*dt; 
    t = t+dt;
    out << t << " " << next << endl;
    for (int i=1; i<=N; i++){
        a = -1*omega*omega*next;
        x = 2*next - prev + a*dt*dt;
        prev = next; 
        next = x; 
        t = t+dt;
        out << t << " " << x << endl;
    }
    out.close();
    
    // Euler method
    ofstream out2("output2.txt");
    x=x0; v=v0; t=ti;
    out2 << t << " " << x << endl;
    for (int i=0;i<=N;i++){
        a = -1.*omega*omega*x;
        x = x + v*dt;
        v = v + a*dt;
        t = t + dt;
        out2 << t << " " << x << endl;
    }
    out2.close();

    plot();
    return 0;
}

void plot(){
    ofstream ploter("inp.plt");
    ploter << "#gnuplot input file\n";
    ploter << "set term png size 800,400\n";
    ploter << "set output \"verlet.png\"\n";
    ploter << "set xlabel \"t\"\n";
    ploter << "set ylabel \"x(t)\"\n";
    ploter << "plot \"output.txt\" u 1:2 w l t \"Verlet\", \"output2.txt\" u 1:2 w l t \"Euler\"\n";
    ploter.close();

    system("gnuplot inp.plt");
}


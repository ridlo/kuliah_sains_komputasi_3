#gnuplot input file
set terminal wxt enhanced
set xlabel 'time - t'
set ylabel 'Temperature (T)'
plot 'temp_euler.txt' u 1:2 t 'T_1', 'temp_euler.txt' u 1:3 t 'T_2', 150.*(1+exp(-2.*0.01*x)) + 5.*(1-exp(-2*0.01*x)) w l, 150.*(1-exp(-2.*0.01*x)) + 5.*(1+exp(-2*0.01*x)) w l

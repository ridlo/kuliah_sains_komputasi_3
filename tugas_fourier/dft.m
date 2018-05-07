%Fourier Transform of Sound File

%Load File
file = 'D:\Sains Komputasi\visains\fourier\looperman_piano_hemorrhage';
wfile = 'D:\Sains Komputasi\visains\fourier\Piano';
[y,Fs,bits] = wavread(file);

Nsamps = length(y);
t = (1/Fs)*(1:Nsamps)          %Prepare time data for plot

%Do Fourier Transform
y_fft_asli = fft(y);
y_fft = abs(y_fft_asli);            %Retain Magnitude
y_fft = y_fft(1:Nsamps/2);      %Discard Half of Points
f = Fs*(0:Nsamps/2-1)/Nsamps;   %Prepare freq data for plot

%Plot Sound File in Time Domain
figure
plot(t, y)
xlabel('Time (s)')
ylabel('Amplitude')
title('Piano in Time Domain')

%Plot Sound File in Frequency Domain
figure
plot(f, y_fft)
xlim([0 20000])
xlabel('Frequency (Hz)')
ylabel('Amplitude')
title('Frequency Response of Piano')

y_ifft = ifft(y_fft);
y_ifft = real(y_ifft);
wavwrite(y_ifft, Fs, bits, wfile)

[y_inv,fs,nbits] = wavread(wfile);

N = length(y_inv);
t = (1/(fs))*(1:N);          %Prepare time data for plot

%nyobain buat plot terhadap frekuensi
y_fft_lagi = fft(y_inv);
y_fft_coba = abs(y_fft_lagi);            %Retain Magnitude
y_fft_coba = y_fft_coba(1:N/2);      %Discard Half of Points
f_coba = fs*(0:N/2-1)/N;   %Prepare freq data for plot

figure
plot(t, y_inv)
xlabel('Time (s)')
ylabel('Amplitude')
title('Piano in Time Domain (After Operation)')

figure
plot(f_coba, y_fft_coba)
xlim([0 20000])
xlabel('Frequency (Hz)')
ylabel('Amplitude')
title('Frequency Response of Piano (After Operation)')

%synthesize(wfile,f,10,y_fft)

%y_inv = y_fft_asli;                % normalize.  Coefficent controls volume.
%wavwrite( y_inv, Fs, bits, wfile)
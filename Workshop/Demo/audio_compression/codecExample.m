%notes:
%can not save file to wav, because MATLAB not support INT8 format as needed for
%linear and mu-law encoding.
%from the graph we can see that the wave quantization are smaller in linEnc and muEnc signal.
%in order to compare performance between linear and mu compression, we calculate the avg error of decoded and wave input.

%codec example
close all;

%mu-law codec algorithm
mu = inline('sign(x) * floor(128*(log(1+255*abs(x/32768))/log(256)))','x');
muInv = inline('ceil(32768*sign(y)*(1/255)*(256^abs(y/128)-1))', 'y');

%lin codec algorithm
lin = inline('floor(x/256)','x');
linInv = inline('y * 256', 'y');

%read audio file
srcFile = 'hts1a.wav';
%srcFile = 'lvb-sym-5-1.wav';
%srcFile = 'beethoven.wav';
[wave, fs, nbits] = wavread(srcFile,'native'); %native means 16-bit format
t = 0:1/fs:(length(wave)-1)/fs;

%convert wave from 16-bit format to double precision
wave = double(wave);

%linear encoding
linEnc = lin(wave);
linEnc;

%linear decoding
linDec = linInv(linEnc);
linDec;

%mu-law encoding
muEnc = [];
for idx = 1:numel(wave)
    el = wave(idx);
    enc = mu(el);
    muEnc(end+1) = enc;
end
muEnc;

%mu-law decoding
muDec = [];
for idx = 1:numel(muEnc)
    el = muEnc(idx);
    dec = muInv(el);
    muDec(end+1) = dec;
end
muDec;

figure('name','WaveInp Double');
plot(t,wave);
figure('name','linEnc Double');
plot(linEnc);
figure('name','linDec Double');
plot(linDec);
figure('name','muEnc Double');
plot(t,muEnc);
figure('name','muDec Double');
plot(t,muDec);

linErr = wave-linDec;
muErr = wave-transpose(muDec);
txt = sprintf('Linear encoding avg. error: %f',mean(abs(linErr)));
disp(txt)
txt1 = sprintf('Mu encoding avg.error: %f',mean(abs(muErr)));
disp(txt1)

%sound(linDec/32768); %audio data must be double precision
%sound(muDec/32768);
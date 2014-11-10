%notes:
%can not save file to wav, because MATLAB not support INT8 format as needed for
%linear and mu-law encoding.

%codec example
close all;
f = inline('sign(x)*((log(1+255*abs(x)))/log(256))', 'x');
%fplot(f,[-1,1]);

%mu-law codec algorithm
mu = inline('sign(x) * floor(128*((log(1+255*abs(x/32768))/log(256))))','x');
muInv = inline('ceil(32768*sign(y)*(1/255)*(256^abs(y/128)-1))', 'y');

%lin codec algorithm
lin = inline('floor(x/256)','x');
linInv = inline('y * 256', 'y');

%read audio file
srcFile = 'hts1a.wav';
%srcFile = 'lvb-sym-5-1.wav';
%srcFile = 'beethoven.wav';
[wave, fs, nbits] = wavread(srcFile);
t = 0:1/fs:(length(wave)-1)/fs;

%convert wave to 16-bit audio
wave = wave*32768;

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

figure('name','Wave Double');
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
txt = sprintf('Linear encoding avg. error: %f',mean(linErr));
disp(txt)
txt1 = sprintf('Mu encoding avg.error: %f',mean(muErr));
disp(txt1)

%sound(linDec/32768);
%sound(muDec/32768);
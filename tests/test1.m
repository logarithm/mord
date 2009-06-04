% тест 1. —читывание 16 отсчетов из файла test.wav
clear
clc
tic
[x0,Fs,bits]=wavread('D:\Projects\mord\matlab\test.wav',[1 16]);
save('file.txt','-ascii','x0','-double');
toc
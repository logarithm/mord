% ���� 1. ���������� 16 �������� �� ����� test.wav
clear
clc
tic
[x0,Fs,bits]=wavread('D:\Projects\mord\matlab\test.wav',[1 16]);
save('file.txt','-ascii','x0','-double');
toc
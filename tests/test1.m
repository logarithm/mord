% ���� 1. ���������� 16 �������� �� ����� test.wav
clear
clc
tic
[x0,Fs,bits]=wavread('D:\Projects\mord\trunk\dll\matlab\test.wav',[1 16]);
save('test1.txt','-ascii','x0','-double');
toc
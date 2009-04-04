set(0,'DefaultFigureColor','w')
% 26.01.09
% расчет распределени€ энергий по матрицам ј
clear
clc
tic
%% ввод исходных данных
load a_64x64_8
%%
[x0,Fs,bits]=wavread('fraza3.wav');
N_x=length(x0); %длина исходного сигнала
x0=x0-mean(x0);
N_otr=floor(N_x/N); % кол анализируемых отрезков
%% цикл анализа отрезков
P_a=zeros(R,N_otr);
for otr=1:N_otr
    n1=(otr-1)*N+1;
    n2=n1+N-1;
X=x0(n1:n2);
clear n1 n2
%% спектр по ј
for r=1:R
    A=a(:,:,r);
    P_a(r,otr)=X'*A*X;
end;
clear r A
end
clear otr
%% график спектра и сигнала
n=4; % номер участка сигнала
t=[0.0001:(N/Fs)/N:N/Fs];
figure(1), plot(t,x0((n-1)*N+1:n*N),'k');
f=[0.0001+(1/R)/2:1/R:1];
figure(2), stem(f,P_a(:,n),'ks','MarkerEdgeColor','k','MarkerFaceColor','k','MarkerSize',3)
toc
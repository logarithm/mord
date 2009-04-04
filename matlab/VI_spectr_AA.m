set(0,'DefaultFigureColor','w')
% 26.01.09
% расчет распределения энергий по матрицам АA
clear
clc
tic
%% ввод исходных данных
load ..\matrix\aaeig_768x512_64_lam AA nnn N NN
R=NN; J=nnn; clear NN sigma nnn
%%
[x0,Fs,bits]=wavread('aproks0201.wav');
N_x=length(x0); %длина исходного сигнала
x0=x0-mean(x0);
N_otr=floor(N_x/N); % кол анализируемых отрезков

%% цикл анализа отрезков
P_aa=zeros(R,N_otr);
for otr=1:N_otr
    n1=(otr-1)*N+1;
    n2=n1+N-1;
X=x0(n1:n2);
clear n1 n2
%% спектр АА
    yy=AA*X;
    for r=1:R
        P_aa(r,otr)=0;
        for p=1:J
            kk=(r-1)*J+p;
            P_aa(r,otr)=P_aa(r,otr)+yy(kk)^2;
        end;
    end;
end;
    clear r p kk yy otr
%% график спектра и сигнала
n=6; % номер участка сигнала
t=[0.0001:(N/Fs)/N:N/Fs];
figure(1), plot(t,x0((n-1)*N+1:n*N),'k');
f=[0.0001+(1/R)/2:1/R:1];
figure(2), stem(f,P_aa(:,n),'ks','MarkerEdgeColor','k','MarkerFaceColor','k','MarkerSize',3)
toc
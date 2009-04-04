% дискретное преобразование Фурье
clear 
clc
tic
%% ввод исходных данных
N=16; nf=N; my_n=10; R=0;
[x0,Fs,bits]=wavread('D:\Projects\mord\trunk\dll\matlab\test.wav',[1 16]);
N_x=length(x0); %длина исходного сигнала
x0=x0-mean(x0);
N_otr=floor(N_x/N); % кол анализируемых отрезков

%% цикл анализа отрезков
P_f=zeros(R,N_otr); P_dpf=zeros(nf,N_otr);
for otr=1:N_otr
    n1=(otr-1)*N+1;
    n2=n1+N-1;
X=x0(n1:n2);
clear n1 n2
%% ДПФ

V1=0; V2=pi;
dV=(V2-V1)/nf;
    for i=1:nf
        s1=0; s2=0;
        for k=1:N
            s1=s1+X(k)*cos((i-1)*dV*(k-1));
            s2=s2+X(k)*sin((i-1)*dV*(k-1));
        end;
        P_dpf(i,otr)=(s1^2+s2^2)/nf;
    end;
    clear i s1 s2 k S
kk=0;

end
clear r k kk
save('test3.txt','-ascii','P_dpf','-double');
toc
load AM_32_512_a11
%% КОДЕР

[x0,Fs,bits]=wavread('California.wav',[3500000 4000000]);
x=x0'; 
wavwrite(x0,Fs,bits,'wav0');
%% ===== СУБПОЛОСНОЕ ПРЕОБРАЗОВАНИЕ И КОДИРОВАНИЕ исходные данные

% R количество частотных интервалов
% N длина окна анализа
% nnn количество ненулевых стобственных чисел
% -------------------------------------------
% сигнал
N_x1=length(x)-1; %длина исходного сигнала
N_Int=floor(N_x1/(N)); % кол отрезков
sdvig=N; % сдвиг окна анализа
NR=16; % количество разрядов квантования
if NR~=0
    Nyr=2^NR-1;
    d=1/Nyr;
end;
%% ===== объявление массивов
XvWA=zeros(1,N_Int*N);
WWA=zeros(N_Int,N); 
WWA_kvant=zeros(N_Int,N);
WWA_kv=zeros(N_Int,N); 
Znak=zeros(N_Int,N);
Max=zeros(N_Int,R);

% -----------------------------------------
%% ===== цикл анализа отрезков
sch=1; %счетчик отрезков

for Int=1:sdvig:(N_x1-N+sdvig)
    if (N_x1-Int)<N
        x1=x(N_x1-N+1:N_x1);% последний отрезок сигнала
    else
        x1=x(Int:Int+N-1);% текущий отрезок сигнала
    end;

    % ----- субполосное кодирование
    % ----- вычисление уу по А_M
    wwA=A_M*x1';
    WWA(sch,:)=wwA;
    % ----- преобразование
    wwA1=wwA;
    % ----- квантование wwA1
    Znak_wwA=sign(wwA1);
    
    MaxA(1:R)=-1;
    for j=1:R
        for p=1:nnn
            kk=(j-1)*nnn+p;
            if MaxA(j)<abs(wwA1(kk))
                MaxA(j)=abs(wwA1(kk));
            end;
        end;
        if NR~=0
        for i=1:nnn
            kk=(j-1)*nnn+i;
            K3=abs(wwA1(kk))/MaxA(j);
            wwA_kvant(kk)=floor(K3/d+0.5);
        end;
        end;
    end;
  if NR~=0
       Max(sch,:)=d.*MaxA;
       WWA_kvant(sch,:)=wwA_kvant;
   else
       WWA_kvant(sch,:)=0.5;
       Max(sch,:)=MaxA;
   end;
    Znak(sch,:)=Znak_wwA;
    sch=sch+1;
end;

% Преобразование двумерного массива yy в одномерный wav1
WWA_kvant=WWA_kvant';
wav1(1:N,1)=WWA_kvant(1:N,1);
j2=2;
for i=1:N_Int
wav1(i*N+1:i*N+N,1)=WWA_kvant(1:N,j2);
j2=j2+1;
end;
save wav1 wav1
wavwrite(wav1,Fs,bits,'wav1');
clear i
WWA_kvant=WWA_kvant';
%% ДЕКОДЕР
%% ===== воосстановление сигнала 
% инверсия A_М
A_Minv=inv(A_M);
% --------------------------------------------

N_k=size(WWA_kvant,1);

for INT=1:N_k
    Znak_wwA=Znak(INT,:);
    wwA_kvant=WWA_kvant(INT,:);
    MaxA=Max(INT,:);
    % ----- восстановление квантованного сигнала wwA1
    for i=1:R
        for j=1:nnn
            kk=(i-1)*nnn+j;
            wwA2(kk)=Znak_wwA(kk)*wwA_kvant(kk)*MaxA(i);
        end;
    end;
    wwA1=wwA2;
    WWA_kv(INT,:)=wwA2;
    % ----- востановлеие сигнала по A_М
    xxA1=A_Minv*wwA1';
    for i=1:N
        k=(INT-1)*N+i;
        XvWA(k)=xxA1(i);
    end;
end;
N_v=length(XvWA);
XvWA(N_x1+1:N_v)=[];


wavwrite(XvWA,Fs,bits,'god');

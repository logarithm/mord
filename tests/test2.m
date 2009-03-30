% ���� 2. ������������ ������� N=32 R=2
clear
clc
tic
% ���������� ������� �
N=32; % ���������� �������� � ������
R=2;% ���������� ��������� ���������� �����
%%
sigma=pi/R;
a=zeros(N,N,R);
matri=zeros(N,N);
bufer=0;
    for r=1:R
        % ������� � ��� ������� r
        for i=1:N
            for k=1:N
                if i==k
                    a(i,k,r)=sigma/pi;
                    bufer=sigma/pi;
                else
                    a(i,k,r)=(sin(r*sigma*(i-k))-sin((r-1)*sigma*(i-k)))/(i-k)/pi;                   
                    bufer=(sin(r*sigma*(i-k))-sin((r-1)*sigma*(i-k)))/(i-k)/pi;                   
                end;
                if r==2 
                    matri(i,k)=bufer;
                end;
            end;
        end;
    end;
clear i k r
A_B=a;


nnn=N/R; % ��� ��������� ����������� �����
A_M=zeros(N,N);
%% �� � ���������� nnn ����� ��� ������� ���������� ��������� - �(nnn_N_NN)
for r=1:R
    a11=a(1,1,r);
    for i=1:nnn
        k=(i-1)*R+1;
        for j=1:N
            A_M((r-1)*nnn+i,j)=a(k,j,r)/a11;
        end;
    end;
end;

clear i j k r
save('test2_A.txt','-ascii','matri','-double');
save('test2_AM.txt','-ascii','A_M','-double');
%save AM_32_512_a11 A_M N R nnn
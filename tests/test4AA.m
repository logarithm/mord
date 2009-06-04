clear
clc
% загрузка матрицы А, её собственных чисел и векторов, матрицы АА
% через EIG
tic
%%
%--------------------вычисление матриц
% вычисление матрицы А
N=4; % количество отсчетов в группе
R=2;% количество частотных интервалов всего
%%
sigma=pi/R;
a=zeros(N,N,R);
matri=zeros(N,N);
bufer=0;
    for r=1:R
        % матрица А для данного r
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
% NN % количество частотных интервалов
%% N; % длина окна анализа
nnn=N/R+2; % количество вычислЯемых чисел и векторов
%%
AA=zeros(nnn*R,N);
for r=1:R
    for i=1:N
        for j=1:N
%             A(i,j)=a(r,i,j);
            A(i,j)=a(i,j,r);
        end;
    end;
    [Q,l]=eig(A); % собственные вектора по столбцам Q (хорошие в конце)
    for i=1:nnn
        lam(r,i)=l((N+1)-i,(N+1)-i); % строки собственных чисел
    end;
    Q=Q';
    for i=1:nnn
        q=Q((N+1)-i,:);
        l=sqrt(lam(r,i));
        AA(i+(r-1)*nnn,:)=q*l;
    end;
end;
%%
save('test4AA.txt','-ascii','AA','-double');
clear A Q a i j l q r sigma
toc
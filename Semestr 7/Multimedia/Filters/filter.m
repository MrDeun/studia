clear
M= input ('podaj liczbe punktow odpowiedzi impulsowej M= ')
fc= input ('podaj czestotliwosc odciecia fc= ')
f= input('podaj czestotliwosc sygnalu=');
N= input('podaj liczbe punktow sygnalu=');
for k=1:M;
if (k-(M/2)) < 0
 z(k)=(sin(2*pi*fc*(k-M/2)))./(k-M/2);
 elseif (k-(M/2)) == 0;
 z(k) = 2*pi*fc;
 else (k-(M/2)) > 0
 z(k)=(sin(2*pi*fc*(k-M/2)))./(k-M/2);
 end
end
ind=0;
 for o=1:M;
 ind=ind+z(o);
 endfor
wyn=z./ind;
okno(M)=0;
a=1:M;
okno= wyn.*(0.42-0.5*cos(2*pi*a/M)+0.08*cos(4*pi*a/M));
subplot (6,1,1)
scatter (a,okno,1,[1 0 0])
x=a/M;
tran=fft(okno,M);
pyy=sqrt(tran.*conj(tran));
subplot (6,1,2)
scatter (x(1:M/2),pyy(1:M/2),1);
grid
calka(M)=0;
 for w=1:M-1;
 calka(w+1)=calka(w)+okno(w+1);
 endfor;
z=1:M;
subplot (6,1,3)
scatter(z,calka,1)
t=1:N;
syg=sin(2*pi*f.*t/N)+sin(2*pi*5*f.*t/N);
subplot(6,1,4);
plot(t,syg);
out=conv(okno,syg);
r=length(out)
subplot(6,1,5);
indeks = M+N;
w=1:indeks;
plot(w(M:r-M),out(M:r-M))
e(M)=0;
 e=-wyn
e(M/2)=e(M/2)+1
subplot(6,1,6)
y=1:M;
scatter(y,e,1);

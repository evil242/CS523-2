
%calculates the rate of convergence based on the stdv
%for Island GA

%Normal GA
r1 = std(x1pt_Tourn);
y1 = length(x1pt_Tourn)-1;
for i=1:y1
    xx1(i)= abs(x1pt_Tourn(i+1) -r1)/abs(x1pt_Tourn(i) -r1);
end
%Island GA
r2 = std(island1);
y2 = length(island1)-1;
for i=1:y2
    xx2(i)= abs(island1(i+1) -r2)/abs(island1(i) -r2);
end
r3 = std(island2);
y3 = length(island2)-1;
for i=1:y3
    xx3(i)= abs(island2(i+1) -r2)/abs(island2(i) -r2);
end
%loglog(xx1);xlabel('number of cycles');ylabel('rate of convergence');
%hold on
%loglog(xx2);xlabel('number of cycles');ylabel('rate of convergence');
%hold on
loglog(xx3);xlabel('number of cycles');ylabel('rate of convergence');
legend('GA', 'Island1','Island2')


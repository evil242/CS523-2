
%calculates the rate of convergence based on the mean
%for mutation rates

%0.05
r1 = std(x1pt_Tourn);
y1 = length(x1pt_Tourn)-1;
for i=1:y1
    xx1(i)= abs(x1pt_Tourn(i+1) -r1)/abs(x1pt_Tourn(i) -r1);
end
%0.15
r2 = std(m15);
y2 = length(m15)-1;
for i=1:y2
    xx2(i)= abs(m15(i+1) -r2)/abs(m15(i) -r2);
end

%loglog(xx1);xlabel('number of cycles');ylabel('rate of convergence');
%hold on
loglog(xx2);xlabel('number of cycles');ylabel('rate of convergence');

legend('0.05', '0.15')




%calculates the rate of convergence based on the mean
%for selection methods

%tournament selection
r1 = std(x1pt_Tourn);
y1 = length(x1pt_Tourn)-1;
for i=1:y1
    xx1(i)= abs(x1pt_Tourn(i+1) -r1)/abs(x1pt_Tourn(i) -r1);
end
%roulette selection
r2 = std(x1pt_r);
y2 = length(x1pt_r)-1;
for i=1:y2
    xx2(i)= abs(x1pt_r(i+1) -r2)/abs(x1pt_r(i) -r2);
end
%Random replacement
r3 = std(x1pt_rand);
y3 = length(x1pt_rand)-1;
for i=1:y3
    xx3(i)= abs(x1pt_rand(i+1) -r2)/abs(x1pt_rand(i) -r2);
end
loglog(xx1);xlabel('number of cycles');ylabel('rate of convergence');
hold on
loglog(xx2);xlabel('number of cycles');ylabel('rate of convergence');
hold on
loglog(xx3);xlabel('number of cycles');ylabel('rate of convergence');
legend('tournament', 'roulette','random')

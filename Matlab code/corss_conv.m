
%calculates the rate of convergence based on the mean
%for crossover methods

%1pt-crossover
r1 = std(x1pt_Tourn);
y1 = length(x1pt_Tourn)-1;
for i=1:y1
    xx1(i)= abs(x1pt_Tourn(i+1) -r1)/abs(x1pt_Tourn(i) -r1);
end
%Uniform crossover
r2 = std(unf_tourn);
y2 = length(unf_tourn)-1;
for i=1:y2
    xx2(i)= abs(unf_tourn(i+1) -r2)/abs(unf_tourn(i) -r2);
end

%loglog(xx1);xlabel('number of cycles');ylabel('rate of convergence');
%hold on
%loglog(xx2);xlabel('number of cycles');ylabel('rate of convergence');
%hold on
loglog(xx3);xlabel('number of cycles');ylabel('rate of convergence');
legend('1pt', 'roulette','no crossover')


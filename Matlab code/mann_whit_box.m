%Mann-Whiney Interquartile Box Plot

%Temporary data for fitst data sets
data1 = x1pt_Tourn;

%Temporary data for second data sets
data2 = x1pt_r;

data3 = x1pt_rand;

%Generate boxplot
boxplot(data1,'Notch', 'off', 'Label', {'Tournament'})
hold on
boxplot(data2,'Notch', 'off', 'Label', {'Roulette'})
title('check')


clear 
clc 

%preparing the dataset
meas=xlsread('iris dataset.xlsx');
meas(:,3)=[];
classes=[ones(1,50) 2*ones(1,50) 3*ones(1,50)];
class1=[ones(1,50) zeros(1,100)];
class2=[zeros(1,50) 2*ones(1,50) zeros(1,50)];
class3=[zeros(1,100) 3*ones(1,50)];

xtrain=[meas(1:30,:);meas(51:80,:);meas(101:130,:)];
ytrain=[ones(1,30) 2*ones(1,30) 3*ones(1,30)]';

xtest=[meas(31:40,:);meas(81:90,:);meas(131:140,:)];
ytest=[ones(1,10) 2*ones(1,10) 3*ones(1,10)]';

xvalidat=[meas(41:50,:);meas(91:100,:);meas(141:150,:)];
yvalidat=[ones(1,10) 2*ones(1,10) 3*ones(1,10)]';

%% setosa vs all 
data1=[ meas class1'];
train1=[data1(1:30,:);data1(51:80,:);data1(101:130,:)];
test1=[data1(31:40,:);data1(81:90,:);data1(131:140,:)];
validat1=[data1(41:50,:);data1(91:100,:);data1(141:150,:)];

linmodel1=fitcsvm(train1(:,1:3), train1(:,4), 'KernelFunction', 'linear');
svm_3d_plot(linmodel1,data1(:,1:3),data1(:,4)); title('setosa vs all'); hold on;

%% versicolor vs all 
data2=[meas class2'];
train2=[data2(1:30,:);data2(51:80,:);data2(101:130,:)];
test2=[data2(31:40,:);data2(81:90,:);data2(131:140,:)];
validat2=[data2(41:50,:);data2(91:100,:);data2(141:150,:)];

linmodel2=fitcsvm(train2(:,1:3), train2(:,4), 'KernelFunction', 'linear');
svm_3d_plot(linmodel2,data2(:,1:3),data2(:,4)); title('vercicolor vs all'); hold on;

%% virginical vs all
data3=[meas class3'];
train3=[data3(1:30,:);data3(51:80,:);data3(101:130,:)];
test3=[data3(31:40,:);data3(81:90,:);data3(131:140,:)];
validat3=[data3(41:50,:);data3(91:100,:);data3(141:150,:)];

linmodel3=fitcsvm(train3(:,1:3), train3(:,4), 'KernelFunction', 'linear');
svm_3d_plot(linmodel3,data3(:,1:3),data3(:,4));title('virginica vs all'); hold on;

lintrain_err= multidim_err(linmodel1, linmodel2, linmodel3, xtrain, ytrain)
lintest_err= multidim_err(linmodel1, linmodel2, linmodel3, xtest, ytest)
linvalid_err= multidim_err(linmodel1, linmodel2, linmodel3, xvalidat, yvalidat)

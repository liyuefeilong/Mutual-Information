% 仿射变换
clear;
q = 0.5;
U = [1*cos(q) 1.1*sin(q) 0;-1.1*sin(q) 1*cos(q) 0;0 0 1];
img = imread('Fig8.14(a).jpg');
% 获取图像相关信息
% 若为彩色图像，则需转化为灰度图像
Info = imfinfo('Fig8.14(a).jpg'); 
if (Info.BitDepth > 8)
    img = rgb2gray(img);
end
imwrite(img, 'new1.jpg');
% Maketform函数就是利用给定的参量建立变换结构
% 然后把该变换结构赋给结构体变换
% 根据得到的结构体变量T调用imtransform函数进行变换。
T = maketform('affine',U); 
% 参数A是要变换的图像，T是由makeform函数产生的变换结构
[imt,xdata,ydata] = imtransform(img,T);%,'XYScale',1);
imwrite(imt, 'new2.jpg');
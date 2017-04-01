read = (imread('/home/sheun/Pictures/transistor/Transistor3.jpg'));
I  = rgb2gray(read); %grayscale
I2 = imadjust(I,[0 0.3], [0 1]); %increase contrast

level1 = graythresh(I);  %ostu method without contrast adjustment
level2 = graythresh(I2); %ostu method with contrast adjustment

BW1 = im2bw(I,level1);% without contrast adjustment
BW2 = ~(im2bw(I2,level2)); % with contrast adjustment
BW11 = edge(BW1,'Canny');
BW22 = edge(BW2,'Canny');
%BWO = edge(I2,'Canny');

points1 = detectSURFFeatures(BW1);
points2 = detectSURFFeatures(BW22);
pointsOri = detectSURFFeatures(I);
 
  figure, imshow(I);
  hold on;
  plot(pointsOri.selectStrongest(800));
  figure, imshow(BW1);
  figure, imshow(BW2);

% figure, imshow(BW11);
% figure, imshow(BW22);

% Invert and get rid of the border.
  binaryImage = imclearborder(BW11);
 % Get rid of blobs smaller than n pixels.
 binaryImage = bwareaopen(binaryImage, 49);
%  Count the number of blobs:
 [labeledImage, numberOfBlobs] = bwlabel(binaryImage);
  figure, imshow(binaryImage);
  
  
% Invert and get rid of the border.
  binaryImage2 = imclearborder(BW22);
 % Get rid of blobs smaller than n pixels.
 binaryImage2 = bwareaopen(binaryImage2, 49);
%  Count the number of blobs:
 [labeledImage, numberOfBlobs] = bwlabel(binaryImage2);
 
 %coloredLabelsImage = label2rgb (BW2, 'hsv', 'k', 'shuffle')
 % figure, imshow(binaryImage2);
 % figure, imshow(coloredLabelsImage);
  
%   hold on;
%   plot(pointsOri.selectStrongest(800));
 CC = bwconncomp(BW1)
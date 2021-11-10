
clear all
close all


%% 1.0 Build Sine Wave/Set Params
Fs = 48000;
T = 1/Fs;   
f = 200;    
L = 1;     
N = L*Fs;   
s1 = sin(2*pi*f*[0:T:L-T]); 

% Distortion Variables
levelStart = 1;
levelFinal = 1;
dry = 0;
wet = 1-dry;
k=1.3;
r=1;
DistDry = 0;
DistWet = 1-DistDry;
CasBlend = 0.5;
ParBlend = 1-CasBlend;

%% 2.0 Sigmoid

for n = 1:N
   out_sig(n) = atan(k*s1(n))/atan(k); 
end

plot(s1,out_sig)
axis([-1 1 -1 1])
xlabel('INPUT SAMPLE AMPLITUDE')
ylabel('OUTPUT SAMPLE AMPLITUDE')
title('Sigmoid Distortion Transfer Function')




%% 3.0 Hyperbolic Tangent


for n = 1:N
    out_tan(n) = tanh(s1(n)*r); 
end


plot(s1,out_tan)
axis([-1 1 -1 1])
xlabel('INPUT SAMPLE AMPLITUDE')
ylabel('OUTPUT SAMPLE AMPLITUDE')
title('Hyperbolic Tanget Distortion Transfer Function')

%% 4.0 Cascaded Distortion

% Beginmain time loop
for n = 1:N
  % Create an array applying the first stage of sigmoid distortion,
  % implementing gain modulation on the input signal. 
  out_cas(n) = (dry * levelStart * s1(n))  + (wet * (DistDry * levelStart * s1(n) + DistWet * (1/atan(k)) * atan(k * levelStart * s1(n))));
  % Creeate a tempory variable to contain the values of the output of the
  % prior sigmoid distortion acting as the input value for the hyperbolic
  % tangent distortion
 temp = (dry * (levelStart * out_cas(n))) + wet*(((DistDry * (out_cas(n) * levelStart * r)) + (DistWet * tanh(levelStart * out_cas(n)*r))));
 
 % Final output is stored taking the values solely from the prior temp
 % variable
 out_cas(n) = temp;
end

% implementing final gain stage
out_cas = out_cas*levelFinal;


% A plot of the function using the test signal. 
figure(1)
plot(s1,out_cas)
axis([-1 1 -1 1])
xlabel('INPUT SAMPLE AMPLITUDE')
ylabel('OUTPUT SAMPLE AMPLITUDE')
title('Sigmoid Distortion Function')




%% 5.0 Cascade + Parallel

% Begin main time loop
for n = 1:N
 % Here the same parallel algorithm as explained above is implemented.
 out_par(n) = (dry * levelStart * s1(n))  + (wet * (DistDry * levelStart * s1(n) + DistWet * (1/atan(k)) * atan(k * levelStart * s1(n))));
 
 temp = (dry * (levelStart * out_par(n))) + wet*(((DistDry * (out_par(n) * levelStart * r)) + (DistWet * tanh(levelStart * out_par(n)*r))));

 out_par(n) = temp;
 
 % Using a second temporary variable, a sigmoid function with its own user
 % defined parameters is created.
 temp2 = (dry * levelStart * s1(n))  + (wet * (DistDry * levelStart * s1(n) + DistWet * (1/atan(k)) * atan(k * levelStart * s1(n))));
 
 % The output of the loop here is blended between the parallel input and
 % the cascaded input, allowing for more user control. 
 out_par(n) = CasBlend * out_par(n) + ParBlend * temp2;
end

% Implementing final gain stage
out_par = out_par * levelFinal;

% A plot of the function using the test signal. 
figure(1)
plot(s1,out_par)
axis([-1 1 -1 1])
xlabel('INPUT SAMPLE AMPLITUDE')
ylabel('OUTPUT SAMPLE AMPLITUDE')
title('Sigmoid Distortion Function')



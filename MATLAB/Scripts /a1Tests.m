clear all
close all
clc;

%% Please find below the tests for the distortion plug in


%% 1.0 Cascade 

[x,Fs] = audioread('CascadeSimulation.wav');
[y,Fs] = audioread('PluginCascadeTest-004.wav');
[z,Fs] = audioread('TestAudio.wav');


x1 = x(1:48000/8,1);
y1 = y(1:48000/8,1);
z1 = z(1:48000/8,1);

% Variables if wish to see plot for 1 second length 
x2 = x(1:48000,1);
y2 = y(1:48000,1);
z2 = z(1:48000,1);

y_cas = y;

figure (1)
figure('Position', [100, 100, 1024, 1200]);
sgtitle ('Comparison of Matlab Simulation and Plugin Response (Fs/8 Samples) for Cascaded Section')
subplot(3,1,1)
plot (z1,'r') 
title('Test Signal')
xlabel('Samples')
ylabel('Amplitude')
subplot(3,1,2)
plot (z1,'r')
hold on
plot (x1,'b')
title('Matlab Cascade Simulation -')
xlabel('Samples')
ylabel('Amplitude')
subplot(3,1,3)
plot(z1,'r')
hold on
plot (y1,'k')
title('Plugin Cascade Response')
xlabel('Samples')
ylabel('Amplitude')
hold off

figure(2)
figure('Position', [100, 100, 1024, 1200]);
plot (x2-y2);
ylim([-1 1])
title('Matlab Cascade Simulation - Reaper Cascade Response')
xlabel('Samples')
ylabel('Amplitude')

figure(3)
title('Cascaded Distortion Reaper Plugin Harmonic Distortion')
plot(linspace(0,Fs,length(y(:,1))), 20*log10(abs(fft(y(:,1)))));

%% 2.0 Parallel 



[x,Fs] = audioread('ParallelSimulation.wav');
[y,Fs] = audioread('PluginParallelTest-004.wav');
[z,Fs] = audioread('TestAudio.wav');

T = 1/Fs
x1 = x(1:48000/8,1);
y1 = y(1:48000/8,1);
z1 = z(1:48000/8,1);

% Variables if wish to see plot for 1 second length 
x2 = x(1:48000,1);
y2 = y(1:48000,1);
z2 = z(1:48000,1);

y_par = y; 

figure (1)
figure('Position', [100, 100, 1024, 1200]);
sgtitle ('Comparison of Parallel Matlab Simulation and Plugin Response (Fs/8 Samples) for Cascade + Parallel')
subplot(3,1,1)
plot (z1,'r') 
title('Test Signal')
xlabel('Samples')
ylabel('Amplitude')
subplot(3,1,2)
plot (z1,'r')
hold on
plot (x1,'b')
title('Matlab Parallel Simulation - Reaper Parallel Response')
xlabel('Samples')
ylabel('Amplitude')
subplot(3,1,3)
plot(z1,'r')
hold on
plot (y1,'k')
title('Plugin Parallael Response')
xlabel('Samples')
ylabel('Amplitude')
hold off

figure(2)
figure('Position', [100, 100, 1024, 1200]);
plot (x2-y2);
ylim([-1 1])
title('Matlab Cascade + Parallel Simulation - Reaper Cascade + Parallel Response')
xlabel('Samples')
ylabel('Amplitude')
 
figure(3)
title('Cascaded + Parallel Distortion Reaper Plugin Harmonic Distortion')
plot(linspace(0,Fs,length(y(:,1))), 20*log10(abs(fft(y(:,1)))));

%% 3.0 Comparison of cascade and cascade + parallel

plot(linspace(0,Fs,length(y_cas(:,1))), 20*log10(abs(fft(y_cas(:,1)))), 'b','LineWidth',2, 'DisplayName',' 0.5');
hold on
plot(linspace(0,Fs,length(y_par(:,1))), 20*log10(abs(fft(y_par(:,1)))),'y','LineWidth',1, 'DisplayName',' 0.3'); h2a.Color(4)=0.7;  %  
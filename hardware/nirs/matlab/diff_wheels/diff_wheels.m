clc;
clear variables;
close all force;

t = 0:0.01:5;
L = 0.08;
R = 0.02;
R0 = [0; 0; 0]

diff = @(t) 0 + t*0.1;
gas = @(t) 3;

[l, r, c] = do_diff(t, R0, gas, diff);

figure(1); hold on;
plot(t, l, 'b');
plot(t, r, 'r');
plot(t, c, 'g');

legend('left', 'right', 'centra');

function [l, r, c, c_lin, t] = do_diff(t, R0, gas, diff)
    L = 0.08; R = 0.02;
    l = zeros(length(t), 1);
    r = zeros(length(t), 1);
    c = zeros(length(t), 1);
    c_lin = gas(:);
    l(1) = R0(1);
    r(1) = R0(2);
    c(1) = R0(3);
    dG = 50;
    for i=2:1:length(t)
        if abs(gas) < dG
            dphi = gas(i)/R;
            w1 = dphi + diff(i)/2;
            w2 = dphi - diff(i)/2;
            l(i) = w1; r(i) = w2;
            w = (w1 - w2) * R / L;
            c(i) = w;
            if abs(diff) == 0
                % стоим
            else
                % поворот на месте
            end
        else
            if abs(diff) == 0
                % едем прямолинейно
            else
                % по дуге
            end
        end
        dphi = gas(i)/R;
        w1 = dphi + diff(i)/2;
        w2 = dphi - diff(i)/2;
        l(i) = w1; r(i) = w2;
        w = (w1 - w2) * R / L;
        c(i) = w;
    end
end

function r = filter(src)
    tr = 
    if src >= 0 && src <
end

% function [l, r, c, t] = do_diff(t, dR, dPhi, R0, diff)
%     l = zeros(length(t), 2);
%     r = zeros(length(t), 2);
%     c = zeros(length(t), 2);
%     l(1, :) = R0(1, :);
%     r(1, :) = R0(2, :);
%     c(1, :) = R0(3, :);
%     for i=2:1:length(t)
%         c(i, :) = 
%     end
% end
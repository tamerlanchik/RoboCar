clc;
clear variables;
close all force;

[t, x, v, a] = get();

figure(1);
hold on; grid on; grid minor;
plot(t, x/40, 'g', 'LineWidth', 2);
plot(t, v, 'b', 'LineWidth', 2);
plot(t, a, 'r', 'LineWidth', 2);
legend('x(t)', 'v(t)', 'a(t)');
ylim([-1 1]);


function [t, x, v, a] = get()
    from_cpp = fopen("../fstreams/f1_output.txt", 'r');
    assert(from_cpp ~= -1);
    data = fscanf(from_cpp, '%d %f %f %f\n', [4 Inf]);
    t = data(1, :)';
    x = data(2, :)';
    v = data(3, :)';
    a = data(4, :)';
end

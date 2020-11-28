t = writeT();
function t = writeT()
    to_cpp = fopen("../fstreams/f1_input.txt", 'w');
    
    assert(to_cpp ~= -1);
    
%     x = @(t) sin(2*pi*t - pi/2)+1;
    x = @(t) 20*t.^2;
    t = (0.01:0.01:8);
    
    t = diffSignal(x(t), 0.1);
    t = round(t * 10e6);

    fprintf(to_cpp, '%d\n', t);
    fclose(to_cpp);
end


function s = diffSignal(src, T)
    s = [T];
    maxVal = max(src);
    i = 1;
    j = 2;
    while i < length(src)
        if T*i <= s(end)
            i = i + 1;
        end
        s_ = s(end) + T * max((1 - src(i)/maxVal), 0.1);
        j = j + 1;
        s = [s; s_];
        d = T * src(i)/maxVal
    end
%     for i=2:1:length(src)
%         s_ = s(i-1) + T * (1 - src(i)/maxVal);
%         s = [s; s_];
%         d = T * src(i)/maxVal
%     end
end

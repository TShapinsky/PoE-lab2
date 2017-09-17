pause on
arduino = serial('COM9', 'BAUD', 115200);
fopen(arduino);
fprintf(arduino,'hi');
disp('sending');
pause(1);
timeout = 0;
points = [];
while timeout <5
    while arduino.BytesAvailable > 0
        timeout = 0;
        out = eval(fscanf(arduino));
        points = [points , out];
    end
    pause(0.5);
    timeout = timeout + 1;
end
fclose(arduino);
delete(arduino);
clear arduino
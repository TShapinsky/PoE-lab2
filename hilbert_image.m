function [ pixels ] = hilbert_image( raw )
    pixels = zeros(max(raw(1,:)),max(raw(2,:)));
    for pixel = raw
        pixels(pixel(1) + 1,pixel(2) + 1) = pixel(3);
    end


end


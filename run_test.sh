#!/bin/sh

imgs="a b c d e f"

for i in $imgs
do
./add_hat  --avatar_image $i.jpg --hat_image 1.png --output output_$i.jpg
done

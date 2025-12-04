#!/bin/bash
set -e

# Input filter type
echo "----------------------------------"
echo "Which filter do you want to apply?"
echo "  e - Edge Detection"
echo "  s - Sepia Tone"
echo "  b - Blur"
echo "  g - Grayscale"
echo "  r - Reflection"
echo "----------------------------------"
read -p "Enter the flag letter (e/s/b/g/r): " FLAG

# Validate input
if [[ ! "$FLAG" =~ ^[esbgr]$ ]]; then
    echo "Invalid option. Exiting."
    exit 1
fi

# Adding a dash
FILTER_FLAG="-$FLAG"

# Check for C engine
if [ ! -f "./filter" ]; then
    echo "Compiling C Engine"
    gcc -o filter filter.c helpers.c -lm
fi

rm -rf frames processed
mkdir -p frames processed

# Extract frames
echo "Extracting frames"
ffmpeg -i input.mp4 -pix_fmt bgr24 frames/frame_%04d.bmp -hide_banner -loglevel error

# Process frames using a loop
echo "Applying filter ($FILTER_FLAG) to frames"
for img in frames/*.bmp; do
    filename=$(basename "$img")
    ./filter $FILTER_FLAG "$img" "processed/$filename"
done

# Recombine the frames
echo "Rendering output"
ffmpeg -framerate 30 -i processed/frame_%04d.bmp -c:v libx264 -pix_fmt yuv420p output.mp4 -y -hide_banner -loglevel error

echo "Done! Saved to output.mp4"
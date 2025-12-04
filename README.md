# CLI Video Effects Engine

## Overview
A lightweight, high-performance video processing pipeline built in **C** and **Bash**.

Unlike standard video editors that rely on pre-built libraries like OpenCV, this project implements core computer vision algorithms from scratch. It utilizes a custom automation pipeline to decompose video streams, manipulate raw binary pixel data in memory using low level C logic, and reconstruct the footage in real-time.

## Features
* **Edge Detection:** Implements the Sobel Operator using 3x3 convolution matrices to calculate gradient magnitude.
* **Blur:** Applies spatial averaging for noise reduction and smoothing.
* **Color Transformations:** Non-linear pixel mapping for **Sepia** and linear mapping for **Grayscale**.
* **Stream Automation:** Integrated Bash/FFmpeg pipeline handles frame extraction, batch processing, and video rendering.

## How It Works
The engine follows a 3-stage pipeline:
1.  **Decomposition:** A Bash script utilizes FFmpeg to split MP4 video streams into uncompressed 24-bit BMP bitmaps.
2.  **Processing:** The C executable reads the binary file headers (`BITMAPFILEHEADER`), allocates memory for pixel buffers, and applies convolution kernels directly to the RGB arrays.
3.  **Reconstruction:** The processed frames are re-sequenced and encoded into an H.264 video container.

## Installation

### Prerequisites
* GCC Compiler (standard on Linux/Mac/WSL)
* FFmpeg

### Building from Source
Clone the repository and compile the C engine:
```bash
make
```
### Usage
1. Place an MP4 video file named input.mp4 in the root directory.
2. Make the pipeline script executable:
```bash
chmod +x process_video.sh
```
3. Run the pipeline:
```bash
./process_video.sh
```
4. Select your desired filter from the interactive menu:
- e - Edge Detection (Sobel)
- s - Sepia
- b - Blur
- g - Grayscale
- r - Horizontal Reflection
5. The processed video will be saved as output.mp4.

### Technical Details
- Language: C (ISO C11 Standard)
- Memory Management: Manual stack/heap allocation for image buffers.
- Math: Custom implementation of rounding and square root logic using math.h.
- Performance: Optimized for cache locality by processing contiguous memory blocks of uncompressed bitmap data.

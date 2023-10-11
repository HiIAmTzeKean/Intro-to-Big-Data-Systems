# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:13

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . .
WORKDIR /

# This command compiles your app using GCC, adjust for your source code
RUN g++ -std=c++11 -fopenmp -g -O3 -o pr main.cpp page_rank.cpp common/graph.cpp

# This command runs your application, comment out this line to compile only
CMD ["./pr","./hw2_data/com-orkut_117m.graph","2"]

LABEL Name=hw2 Version=0.0.1

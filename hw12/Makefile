HALIDE_DISTRIB_PATH = $(realpath /halide)
DNNLROOT = $(realpath /opt/intel/oneapi/dnnl/latest/cpu_gomp)

CXX = g++
CXXFLAGS = -Wall -O3 -std=c++17 -I $(HALIDE_DISTRIB_PATH)/include -I $(DNNLROOT)/include -I $(DNNLROOT)/examples 
LDFLAGS = -ldl -lpthread -lz

LIBHALIDE_LDFLAGS = -Wl,-rpath,$(HALIDE_DISTRIB_PATH)/lib -L $(HALIDE_DISTRIB_PATH)/lib -lHalide
LIBDNNL_LDFLAGS = -Wl,-rpath,$(DNNLROOT)/lib -L $(DNNLROOT)/lib -ldnnl

.PHONY: all
all: matmul conv dilated_conv op_fuse

matmul: matmul.cpp halide_benchmark.h common.h
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBHALIDE_LDFLAGS) $(LIBDNNL_LDFLAGS) $(LDFLAGS)

conv: conv.cpp halide_benchmark.h common.h
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBHALIDE_LDFLAGS) $(LIBDNNL_LDFLAGS) $(LDFLAGS)

dilated_conv: dilated_conv.cpp halide_benchmark.h common.h
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBHALIDE_LDFLAGS) $(LIBDNNL_LDFLAGS) $(LDFLAGS)

op_fuse: op_fuse.cpp halide_benchmark.h common.h
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBHALIDE_LDFLAGS) $(LIBDNNL_LDFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf matmul conv dilated_conv op_fuse

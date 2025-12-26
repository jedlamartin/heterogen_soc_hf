#include <string>
#include "stringify.h"

#ifndef _BENCH_KERNELS_H_
#define _BENCH_KERNELS_H_

static const std::string opencl_kernel_code =

#include "median2d_kernel_gl.cl"
#include "median2d_kernel_sh_uchar_int.cl"
#include "median2d_kernel_sh_uchar_float.cl"
;


#endif

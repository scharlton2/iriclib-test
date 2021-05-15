#ifndef IRICLIB_SOL_GRIDCOORD_H
#define IRICLIB_SOL_GRIDCOORD_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d_WithGridId_Mul(int fid, int gid, int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, int step, double* x_arr, double* y_arr, double* z_arr);

int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d_WithGridId_Mul(int fid, int gid, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, double* x_arr, double* y_arr, double* z_arr);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_SOL_GRIDCOORD_H
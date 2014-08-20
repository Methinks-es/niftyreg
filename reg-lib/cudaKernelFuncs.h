#pragma once
#include "nifti1_io.h"

typedef struct nifti_params {

	int ndim;                    /*!< last dimension greater than 1 (1..7) */
	int nx;                      /*!< dimensions of grid array             */
	int ny;                      /*!< dimensions of grid array             */
	int nz;                      /*!< dimensions of grid array             */
	int nt;                      /*!< dimensions of grid array             */
	int nu;                      /*!< dimensions of grid array             */
	int nv;                      /*!< dimensions of grid array             */
	int nw;                      /*!< dimensions of grid array             */
	unsigned long nvox;          /*!< number of voxels = nx*ny*nz*...*nw   */
	int nbyper;                  /*!< bytes per voxel, matches datatype    */
	int datatype;                /*!< type of data in voxels: DT_* code    */

	float dx;                    /*!< grid spacings      */
	float dy;                    /*!< grid spacings      */
	float dz;                    /*!< grid spacings      */
	float dt;                    /*!< grid spacings      */
	float du;                    /*!< grid spacings      */
	float dv;                    /*!< grid spacings      */
	float dw;                    /*!< grid spacings      */
	unsigned int nxyz;           //xyz image size

}nifti_params_t;

void launch(nifti_image *image, float *sigma, int kernelType, int *mask, bool *timePoint, bool *axis);
void launchAffine(mat44 *affineTransformation, nifti_image *deformationField, bool compose = false, int *mask = NULL);
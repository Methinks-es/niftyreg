#include"Kernel.h"
#include"Kernels.h"
#include "CPUPlatform.h"
#include "CudaPlatform.h"
#include "CLPlatform.h"
#include "_reg_ReadWriteImage.h"
#include"cuda_runtime.h"
#include <ctime>

void mockAffine(mat44* affine) {
	affine->m[0][0] = 0.999948680;
	affine->m[1][0] = 0.000179830939;
	affine->m[2][0] = -0.0101536512;
	affine->m[3][0] = 0.0000;

	affine->m[0][1] = -0.000137887895;
	affine->m[1][1] = 0.999991596;
	affine->m[2][1] = 0.00413208781;
	affine->m[3][1] = 0.0000;

	affine->m[0][2] = 0.0101542696;
	affine->m[1][2] = -0.00413054228;
	affine->m[2][2] = 0.999939919;
	affine->m[3][2] = 0.0000;

	affine->m[0][3] = 0.331813574;
	affine->m[1][3] = -0.145962417;
	affine->m[2][3] = 0.238046646;
	affine->m[3][3] = 1.0000;
}

void test(Platform* platform) {
	Kernel affineDeformKernel = platform->createKernel(AffineDeformationFieldKernel::Name(), 16);

	//init ref params
	nifti_image* input = reg_io_ReadImageFile("mock_affine_input.nii");
	nifti_image* output = reg_io_ReadImageFile("mock_affine_output.nii");

	mat44* affine = new mat44;
	mockAffine(affine);

	clock_t begin = clock();
	//run kernel
	affineDeformKernel.getAs<AffineDeformationFieldKernel>().execute(affine, input);

	clock_t end = clock();

	//read elapsed time
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	

	//compare results
	double maxDiff = reg_test_compare_images(input, output);

	//output
	std::cout << "diff:" << maxDiff << std::endl;
	std::cout << "elapsed" << elapsed_secs << std::endl;

	nifti_image_free(input);
	nifti_image_free(output);
}

int main(int argc, char **argv) {

	//init platform params
	Platform *cpuPlatform = new CPUPlatform();
	Platform *cudaPlatform = new CudaPlatform();
	Platform *clPlatform = new CLPlatform();
	test(cpuPlatform);
	test(cudaPlatform);
	cudaDeviceReset();
	test(clPlatform);
	cudaDeviceReset();
	
	return 0;

}
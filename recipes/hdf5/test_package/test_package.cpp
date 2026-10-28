/************************************************************

  This example shows how to set the space allocation time
  for a dataset.  The program first creates two datasets,
  one with the default allocation time (late) and one with
  early allocation time, and displays whether each has been
  allocated and their allocation size.  Next, it writes data
  to the datasets, and again displays whether each has been
  allocated and their allocation size.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include <H5Cpp.h>
#include <hdf5.h>
#include <hdf5_hl.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE "h5ex_d_alloc.h5"
#define DATASET1 "DS1"
#define DATASET2 "DS2"
#define DIM0 4
#define DIM1 7
#define FILLVAL 99
#define CHECK(expression)                                                                          \
    do                                                                                             \
    {                                                                                              \
        if ((expression) < 0)                                                                      \
        {                                                                                          \
            fprintf(stderr, "%s failed\n", #expression);                                           \
            return 1;                                                                              \
        }                                                                                          \
    } while (0)

static int cpp_api_round_trip(void)
{
    const int expected[DIM0] = {1, 2, 3, 4};
    int actual[DIM0] = {0};
    try
    {
        H5::H5File file("h5ex_cpp.h5", H5F_ACC_TRUNC);
        hsize_t dims[1] = {DIM0};
        H5::DataSpace space(1, dims);
        H5::DataSet dataset = file.createDataSet("DS", H5::PredType::NATIVE_INT, space);
        dataset.write(expected, H5::PredType::NATIVE_INT);
        file.openDataSet("DS").read(actual, H5::PredType::NATIVE_INT);
    }
    catch (const H5::Exception &error)
    {
        fprintf(stderr, "HDF5 C++ error: %s\n", error.getCDetailMsg());
        return 1;
    }
    for (int i = 0; i < DIM0; i++)
    {
        if (actual[i] != expected[i])
        {
            fprintf(stderr, "C++ API round trip mismatch at %d\n", i);
            return 1;
        }
    }
    return 0;
}

static int hl_api_round_trip(void)
{
    const int expected[DIM0] = {5, 6, 7, 8};
    int actual[DIM0] = {0};
    hsize_t dims[1] = {DIM0};
    hid_t file = H5Fcreate("h5ex_hl.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(file);
    CHECK(H5LTmake_dataset_int(file, "DS", 1, dims, expected));
    CHECK(H5LTread_dataset_int(file, "DS", actual));
    CHECK(H5Fclose(file));
    for (int i = 0; i < DIM0; i++)
    {
        if (actual[i] != expected[i])
        {
            fprintf(stderr, "HL API round trip mismatch at %d\n", i);
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    hid_t file, space, dset1, dset2, dcpl;
    /* Handles */
    herr_t status;
    H5D_space_status_t space_status;
    hsize_t dims[2] = {DIM0, DIM1}, storage_size;
    int wdata[DIM0][DIM1], /* Write buffer */
        i, j;

    /*
     * Initialize data.
     */
    for (i = 0; i < DIM0; i++)
        for (j = 0; j < DIM1; j++)
            wdata[i][j] = i * j - j;

    /*
     * Create a new file using the default properties.
     */
    file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    CHECK(file);

    /*
     * Create dataspace.  Setting maximum size to NULL sets the maximum
     * size to be the current size.
     */
    space = H5Screate_simple(2, dims, NULL);
    CHECK(space);

    /*
     * Create the dataset creation property list, and set the chunk
     * size.
     */
    dcpl = H5Pcreate(H5P_DATASET_CREATE);
    CHECK(dcpl);

    /*
     * Set the allocation time to "early".  This way we can be sure
     * that reading from the dataset immediately after creation will
     * return the fill value.
     */
    status = H5Pset_alloc_time(dcpl, H5D_ALLOC_TIME_EARLY);
    CHECK(status);

    printf("Creating datasets...\n");
    printf("%s has allocation time H5D_ALLOC_TIME_LATE\n", DATASET1);
    printf("%s has allocation time H5D_ALLOC_TIME_EARLY\n\n", DATASET2);

    /*
     * Create the dataset using the dataset creation property list.
     */
    dset1 = H5Dcreate(file, DATASET1, H5T_STD_I32LE, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    dset2 = H5Dcreate(file, DATASET2, H5T_STD_I32LE, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
    CHECK(dset1);
    CHECK(dset2);

    /*
     * Retrieve and print space status and storage size for dset1.
     */
    status = H5Dget_space_status(dset1, &space_status);
    CHECK(status);
    storage_size = H5Dget_storage_size(dset1);
    printf("Space for %s has%sbeen allocated.\n", DATASET1,
           space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf("Storage size for %s is: %ld bytes.\n", DATASET1, (long)storage_size);

    /*
     * Retrieve and print space status and storage size for dset2.
     */
    status = H5Dget_space_status(dset2, &space_status);
    CHECK(status);
    storage_size = H5Dget_storage_size(dset2);
    printf("Space for %s has%sbeen allocated.\n", DATASET2,
           space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf("Storage size for %s is: %ld bytes.\n", DATASET2, (long)storage_size);

    printf("\nWriting data...\n\n");

    /*
     * Write the data to the datasets.
     */
    status = H5Dwrite(dset1, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata[0]);
    CHECK(status);
    status = H5Dwrite(dset2, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, wdata[0]);
    CHECK(status);

    /*
     * Retrieve and print space status and storage size for dset1.
     */
    status = H5Dget_space_status(dset1, &space_status);
    CHECK(status);
    storage_size = H5Dget_storage_size(dset1);
    printf("Space for %s has%sbeen allocated.\n", DATASET1,
           space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf("Storage size for %s is: %ld bytes.\n", DATASET1, (long)storage_size);

    /*
     * Retrieve and print space status and storage size for dset2.
     */
    status = H5Dget_space_status(dset2, &space_status);
    CHECK(status);
    storage_size = H5Dget_storage_size(dset2);
    printf("Space for %s has%sbeen allocated.\n", DATASET2,
           space_status == H5D_SPACE_STATUS_ALLOCATED ? " " : " not ");
    printf("Storage size for %s is: %ld bytes.\n", DATASET2, (long)storage_size);

    /*
     * Close and release resources.
     */
    status = H5Pclose(dcpl);
    CHECK(status);
    status = H5Dclose(dset1);
    CHECK(status);
    status = H5Dclose(dset2);
    CHECK(status);
    status = H5Sclose(space);
    CHECK(status);
    status = H5Fclose(file);
    CHECK(status);

    if (cpp_api_round_trip() != 0 || hl_api_round_trip() != 0)
    {
        return 1;
    }

    return 0;
}

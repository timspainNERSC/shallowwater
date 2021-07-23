# shallowwater
A simple shallow water solver to test set of grids versus grid of sets.

## Rationale
### Set of grids
In my experience, most computational fluid dynamics and global circulation models use a paradigm that could be described as a **set of grids**. In this, the model parameters are stored in several n-grids defined in the model code. To perform calculations as part of the model integration, an index is chosen, and the data from several of these grids at this index are used in the computation.
The fundamental geometry of the grid or mesh that the model uses is baked into every model variable. If the model varaible is not abstracted into a dataset class, this can lead to code duplication when accesing model variables in different places in the code.
There is also a question of cache-coherence. The scalar values that are used in local calculations are going to be at least an array size apart, restricting the usefulness of cached values, especially if neighbouring grid squares are being processed on seperate CPUs, as might happen in an MPI enabled program.

### Grid of sets
An alternative is to store the model state for an element in a single class. The overall model state is a grid of these classes. A few grid variables might be needed if velocity grid points are separated from mass grid points, as in an Arakawa B-grid. The data for scalar calculations are much more likely to be in the cache, and there are fewer grid variables that need to be passed around.
This might introduce an additional level of indirection, especially when calculating gradients or anything else that requires to know about its neighbours.

## Purpose
The programs in this repository are intended to test the run time differences of these two approaches. The programs will integrate the shallow water equations using the two described approaches and the differences that arise will be quatified.
The difference between the two approaches will likely be minimal in the case of local physics. The scalar values simply need to be accessed either from the several grids at the given index, or from the offsets within the address space of the particular grid state object.
The best test, then, will be simple equations that require little in the way of physics, but depend heavily on inter-element communication.

## Shallow water equations
The shallow water equations are a simple physical model that fulfills this requirement. They simple, well studied and easy to implement. The driving equations depend on the interplay between the height field and velocity field, and to run quickly requires efficient gradient calculation between the two.
As of writing this README, the targets are:
1. A traditional set of grids model, on an Arakawa A-grid (co-located h, u and v fields)
2. A grid of sets model, on the same A grid
3. A set of grids model on an Arakawa C-grid
4. A grid of sets equivalent of 3.

Each will be run at a high resolution, higher resolution than necessary for solving the simple input fields, but high enough to give a tstable run time, especially if run using MPI.
## Boundary conditions
### Initial
The initial boundary conditions will be provided by NetCDF files (perhaps HDF5 if they prove too irritating). These will be simple height and velocity fields, such as vortices or an advected lump.

### External
The boundaries will be periodic. This is close enough in computational difficulty to a spherical, global model, but without the complication of inhomogeneous grid shapes and sizes.

# Infrastructural matters
## Language and standard
The models are written in C++ with the STL. The target standard is C++17, but I doubt there is much that will be that modern.
## Build system
The models are build using CMake. The available targets are:
* `soga` (**s**et **o**f **g**rids on an Arakawa **A** grid)
* `gosa` (**g**rid **o**f **s**ets on an Arakawa **A** grid)
* `sogb` (**s**et **o**f **g**rids on an Arakawa **B** grid)
* `gosb` (**g**rid **o**f **s**ets on an Arakawa **B** grid)
* `all`

The individual models will create executables with the above names.

## Required libraries
NetCDF
Internal timing is based on the C++11 `std::chrono` library.

/*
 * Copyright © 2010 CNRS, INRIA, Université Bordeaux 1
 * See COPYING in top-level directory.
 */

#include <private/config.h>
#include <hwloc.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
  hwloc_topology_t topology;
  hwloc_obj_type_t type;
  unsigned nbobjs;
  unsigned *distances;
  int err;

  hwloc_topology_init(&topology);
  hwloc_topology_load(topology);

  err = hwloc_get_distances(topology, HWLOC_OBJ_NODE, &nbobjs, &distances);
  if (err < 0) {
    printf("No NUMA distances\n");
  } else {
    unsigned i, j;
    for(i=0; i<nbobjs; i++) {
      for(j=0; j<nbobjs; j++)
	printf("%u ", distances[i+nbobjs*j]);
      printf("\n");
    }
    free(distances);
  }

  err = hwloc_get_distances(topology, HWLOC_OBJ_PU, &nbobjs, &distances);
  assert(err == -1);

  hwloc_topology_destroy(topology);

  return 0;
}

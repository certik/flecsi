/*~--------------------------------------------------------------------------~*
 *  @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
 * /@@/////  /@@          @@////@@ @@////// /@@
 * /@@       /@@  @@@@@  @@    // /@@       /@@
 * /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
 * /@@////   /@@/@@@@@@@/@@       ////////@@/@@
 * /@@       /@@/@@//// //@@    @@       /@@/@@
 * /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
 * //       ///  //////   //////  ////////  //
 *
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~--------------------------------------------------------------------------~*/

#ifndef flecsi_minimal_entity_types_h
#define flecsi_minimal_entity_types_h

#include "flecsi/mesh/mesh_types.h"
#include "flecsi/specializations/minimal/minimal_mesh_traits.h"

/*!
 * \file minimal_entity_types.h
 * \authors bergen
 * \date Initial file creation: Dec 26, 2015
 */

namespace flecsi
{
/*!
 */
class minimal_vertex_t
    : public mesh_entity_t<0, minimal_mesh_traits_t::num_domains>
{
 public:
}; // class minimal_vertex_t

class minimal_edge_t
    : public mesh_entity_t<1, minimal_mesh_traits_t::num_domains>
{
 public:
  minimal_edge_t(){} 

  minimal_edge_t(mesh_topology_base_t & mesh) {}
}; // class minimal_edge_t

class minimal_face_t
    : public mesh_entity_t<2, minimal_mesh_traits_t::num_domains>
{
 public:
  minimal_face_t(){} 

  minimal_face_t(mesh_topology_base_t & mesh) {}
}; // class minimal_face_t

class minimal_cell_t
    : public mesh_entity_t<3, minimal_mesh_traits_t::num_domains>
{
 public:
  minimal_cell_t(){} 

  minimal_cell_t(mesh_topology_base_t & mesh) {}
  std::vector<size_t> create_entities(
      size_t dimension, id_t * entities, id_t * vertices, size_t vertex_count)
  {
    return {0};
  } // create_entities

  std::vector<id_t> create_bound_entities(size_t from_domain, size_t to_domain,
      size_t dim, id_t ** ent_ids, id_t * c)
  {
    return {0};
  } // create_bound_entities

}; // class minimal_cell_t

} // namespace flecsi

#endif // flecsi_minimal_entity_types_h

/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/

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

#ifndef flecsi_minimal_types_h
#define flecsi_minimal_types_h

#include "flecsi/specializations/minimal/minimal_mesh_traits.h"
#include "flecsi/specializations/minimal/minimal_entity_types.h"

/*!
 * \file minimal_types.h
 * \authors bergen
 * \date Initial file creation: Dec 26, 2015
 */

namespace flecsi
{
struct minimal_types_t {
  static constexpr size_t dimension = minimal_mesh_traits_t::dimension;
  static constexpr size_t num_domains = minimal_mesh_traits_t::num_domains;

  using vertex_t = minimal_vertex_t;
  using edge_t = minimal_edge_t;
  using face_t = minimal_face_t;
  using cell_t = minimal_cell_t;

  // clang-format off
  using entity_types =
    std::tuple<
      std::pair<domain_<0>, vertex_t>,
      std::pair<domain_<0>, edge_t>,
      std::pair<domain_<0>, face_t>,
      std::pair<domain_<0>, cell_t>
    >;

  using connectivities =
    std::tuple<
      std::tuple<domain_<0>, vertex_t, edge_t>,
      std::tuple<domain_<0>, vertex_t, cell_t>
    >;

  using bindings = std::tuple<>;
  // clang-format on

}; // struct minimal_types

} // namespace flecsi

#endif // flecsi_minimal_types_h

/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/

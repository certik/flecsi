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

#ifndef flecsi_minimal_mesh_traits_h
#define flecsi_minimal_mesh_traits_h

/*!
 * \file minimal_mesh_traits.h
 * \authors bergen
 * \date Initial file creation: Dec 26, 2015
 */

namespace flecsi
{
struct minimal_mesh_traits_t {
  /*!
    Specify the dimension of the mesh topology.
   */
  static constexpr size_t dimension = 3;

  /*!
    Specify the number of mesh topology domains.
   */
  static constexpr size_t num_domains = 1;

  /*!
    Specify the data attachment sites on the mesh.
   */
  enum class attachment_site_t : size_t {
    vertices,
    edges,
    faces,
    cells
  }; // enum class attachment_site_t

}; // struct minimal_mesh_traits

} // namespace flecsi

#endif // flecsi_minimal_mesh_traits_h

/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/

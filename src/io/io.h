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

#ifndef flecsi_io_h
#define flecsi_io_h

#include "io_base.h"

/*!
 * \file io.h
 * \authors wohlbier
 * \date Initial file creation: Oct 07, 2015
 */

namespace flecsi
{
/*!
  \brief Generic mesh reader that calls the correct method based on the suffix.

  \tparam mesh_t Mesh type to read.

  \param[in] name Read mesh \e m from \e name.
  \param[out] m Create mesh \e m from \e name.

  \return Error code. 0 on success.
 */
template <typename mesh_t>
int32_t read_mesh(const std::string & name, mesh_t & m)
{
  // get the suffix.
  auto suffix = name.substr(name.find_last_of(".") + 1);
  // create the io instance with the factory using the file suffix.
  auto io = io_factory_t<mesh_t>::instance().create(suffix);

  // call the io read function
  auto ret = io->read(name, m);

  // clean up and return
  delete io;
  return ret;
}

/*!
  \brief Generic mesh writer that calls the correct method based on the suffix.

  \tparam mesh_t Mesh type to write.

  \param[in] name Write mesh \e m to \e name.
  \param[in] m Write mesh \e m to \e name.

  \return Error code. 0 on success.
 */
// FIXME: should allow for const mesh_t &
// int32_t write_mesh(const std::string &name, const mesh_t &m) {
template <typename mesh_t>
int32_t write_mesh(const std::string & name, mesh_t & m)
{
  // get the suffix.
  auto suffix = name.substr(name.find_last_of(".") + 1);
  // create the io instance with the factory using the suffix.
  auto io = io_factory_t<mesh_t>::instance().create(suffix);

  // call the io write function
  auto ret = io->write(name, m);

  // clean up and return
  delete io;
  return ret;
}

} // namespace flecsi

#endif // flecsi_io_h

/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/

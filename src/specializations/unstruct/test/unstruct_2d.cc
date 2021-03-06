/*~-------------------------------------------------------------------------~~*
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
 *~-------------------------------------------------------------------------~~*/

///////////////////////////////////////////////////////////////////////////////
//! \file unstruct.cc
//!
//! \brief This file includes the main test fixture for the general 
//!        unstructured mesh.
///////////////////////////////////////////////////////////////////////////////

// includes
#include <cinchtest.h>
#include <vector>

#include "flecsi/specializations/unstruct/unstruct.h"

// namespaces
using namespace flecsi;


//=============================================================================
//! \class Unstruct
//!
//! \brief The fixture for testing the general unstructured mesh
//=============================================================================

class Unstruct2D : public ::testing::Test {

protected:

  //---------------------------------------------------------------------------
  // Types
  //---------------------------------------------------------------------------

  
  //! \brief number of cells wide
  static constexpr size_t width = 2;
  //! \brief number of cells high
  static constexpr size_t height = 2;

  //! \brief the mesh type
  using mesh_t   = unstruct_2d_mesh_t;

  //! \brief the mesh float type
  using real_t   = typename mesh_t::real_t;
  //! \brief the mesh dimensions
  static constexpr size_t dimension = mesh_t::dimension;

  //! \brief the point
  using point_t  = typename mesh_t::point_t;
  //! \brief the vertex type
  using vertex_t = typename mesh_t::vertex_t;
  //! \brief the vertex type
  using edge_t   = typename mesh_t::edge_t;
  //! \brief the face type
  using face_t   = typename mesh_t::face_t;
  //! \brief the cell type
  using cell_t   = typename mesh_t::cell_t;

  
  //---------------------------------------------------------------------------
  //! \brief the test setup function
  //---------------------------------------------------------------------------
  virtual void SetUp() override {
    
    std::vector<vertex_t*> vs;

    mesh_.init_parameters( (height+1)*(width+1) );
  
    for(size_t j = 0; j < height + 1; ++j){
      for(size_t i = 0; i < width + 1; ++i){
        point_t p{real_t(i), real_t(j)};
	auto v = mesh_.create_vertex(p);
	vs.push_back(v);
      }
    }

    auto width1 = width + 1;
    for(size_t j = 0; j < height; ++j){
      for(size_t i = 0; i < width; ++i){
	auto c = 
	  mesh_.create_cell({
            vs[ i      +   j      * width1 ],
            vs[ i + 1  +   j      * width1 ],
            vs[ i + 1  +  (j + 1) * width1 ],
            vs[ i      +  (j + 1) * width1 ]  });
      }
    }

    mesh_.init();
  }

  //---------------------------------------------------------------------------
  //! \brief the test teardown function 
  //---------------------------------------------------------------------------
  virtual void TearDown() override { }

  //---------------------------------------------------------------------------
  // Data members
  //---------------------------------------------------------------------------

  //! \brief the actual mesh object
  mesh_t mesh_;


};

//=============================================================================
//! \brief A simple test of the mesh
//=============================================================================
TEST_F(Unstruct2D, mesh) {
  for(auto v : mesh_.vertices()) {
    CINCH_CAPTURE() << "----------- vertex: " << v->id() << std::endl;
  }

  for(auto e : mesh_.edges()) {
    CINCH_CAPTURE() << "----------- edge: " << e->id() << std::endl;
  }

  for(auto f : mesh_.faces()) {
    CINCH_CAPTURE() << "----------- face: " << f->id() << std::endl;
  }

  for(auto c : mesh_.cells()) {
    CINCH_CAPTURE() << "----------- cell: " << c->id() << std::endl;
  }

  ASSERT_TRUE(CINCH_EQUAL_BLESSED("unstruct_2d.blessed"));

};

/*~------------------------------------------------------------------------~--*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~------------------------------------------------------------------------~--*/

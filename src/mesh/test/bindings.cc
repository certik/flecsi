#include <cinchtest.h>
#include <iostream>

#include "../../utils/common.h"
#include "../mesh_topology.h"

using namespace std;
using namespace flecsi;

#define FILTER(E) [&](auto E) -> bool

class Vertex : public mesh_entity_t<0, 2>{
public:
  Vertex(){}

  Vertex(mesh_topology_base_t &){}

  template<size_t M>
  uint64_t precedence() const { return 0; }
};

class Edge : public mesh_entity_t<1, 2>{
public:
  Edge(){}

  Edge(mesh_topology_base_t &){}
};

class Cell : public mesh_entity_t<2, 2>{
public:
  Cell(){}

  Cell(mesh_topology_base_t &){}

  void set_precedence(size_t dim, uint64_t precedence) {}

  std::vector<size_t>
  create_entities(size_t dim, flecsi::id_t *e,
                  flecsi::id_t *v, size_t vertex_count){  

    e[0] = v[0];
    e[1] = v[2];
    
    e[2] = v[1];
    e[3] = v[3];
    
    e[4] = v[0];
    e[5] = v[1];
    
    e[6] = v[2];
    e[7] = v[3];

    return {2, 2, 2, 2};
  }

  flecsi::index_vector_t
  create_bound_entities(size_t from_domain,
                        size_t to_domain,
                        size_t create_dim,
                        flecsi::id_t **ent_ids,
                        flecsi::id_t *c) {
    
    switch(create_dim) {
      case 1:
        c[0] = ent_ids[0][0];
        c[1] = ent_ids[1][0];
        c[2] = ent_ids[1][2];

        c[3] = ent_ids[0][1];
        c[4] = ent_ids[1][1];
        c[5] = ent_ids[1][2];

        c[6] = ent_ids[0][2];
        c[7] = ent_ids[1][0];
        c[8] = ent_ids[1][3];

        c[9] = ent_ids[0][3];
        c[10] = ent_ids[1][3];
        c[11] = ent_ids[1][1];

        return {3, 3, 3, 3};
      case 2:
        c[0] = ent_ids[0][0];
        c[1] = ent_ids[1][2];

        c[2] = ent_ids[0][1];
        c[3] = ent_ids[1][1];

        c[4] = ent_ids[0][3];
        c[5] = ent_ids[1][3];

        c[6] = ent_ids[0][2];
        c[7] = ent_ids[1][0];

        return {2, 2, 2, 2};
    }
  }
};

class Corner : public mesh_entity_t<1, 2>{
public:
  Corner(){}

  Corner(mesh_topology_base_t &){}
};

class Wedge : public mesh_entity_t<2, 2>{
public:
  Wedge(){}

  Wedge(mesh_topology_base_t &){}
};

class TestMesh2dType{
public:
  static constexpr size_t dimension = 2;

  static constexpr size_t num_domains = 2;

  using entity_types = std::tuple<
    std::pair<domain_<0>, Vertex>,
    std::pair<domain_<0>, Edge>,
    std::pair<domain_<0>, Cell>,
    std::pair<domain_<1>, Corner>,
    std::pair<domain_<1>, Wedge>>;

  using connectivities = 
    std::tuple<std::tuple<domain_<0>, Vertex, Edge>,
               std::tuple<domain_<0>, Vertex, Cell>,
               std::tuple<domain_<0>, Edge, Vertex>,
               std::tuple<domain_<0>, Edge, Cell>,
               std::tuple<domain_<0>, Cell, Vertex>,
               std::tuple<domain_<0>, Cell, Edge>>;

  using bindings = 
    std::tuple<
              std::tuple<domain_<0>, domain_<1>, Cell, Corner>,
              std::tuple<domain_<0>, domain_<1>, Vertex, Corner>,
              std::tuple<domain_<1>, domain_<0>, Corner, Cell>,
              std::tuple<domain_<1>, domain_<0>, Corner, Edge>,
              std::tuple<domain_<0>, domain_<1>, Edge, Corner>,
              std::tuple<domain_<1>, domain_<0>, Corner, Vertex>,
              std::tuple<domain_<0>, domain_<1>, Cell, Wedge>,
              std::tuple<domain_<0>, domain_<1>, Edge, Wedge>,
              std::tuple<domain_<0>, domain_<1>, Vertex, Wedge>,
              std::tuple<domain_<1>, domain_<0>, Wedge, Cell>,
              std::tuple<domain_<1>, domain_<0>, Wedge, Edge>,
              std::tuple<domain_<1>, domain_<0>, Wedge, Vertex>>;
};

using TestMesh = mesh_topology_t<TestMesh2dType>;

TEST(mesh_topology, traversal) {

  size_t width = 2;
  size_t height = 2;

  auto mesh = new TestMesh;

  vector<Vertex*> vs;

  size_t id = 0;
  for(size_t j = 0; j < height + 1; ++j){
    for(size_t i = 0; i < width + 1; ++i){
      auto v = mesh->make<Vertex>();
      mesh->add_entity<0,0>(v);
      vs.push_back(v); 
    }
  }

  id = 0;
  size_t width1 = width + 1;
  for(size_t j = 0; j < height; ++j){
    for(size_t i = 0; i < width; ++i){
      auto c = mesh->make<Cell>();
      mesh->add_entity<2, 0>(c);

      mesh->init_cell<0>(c,
                         {vs[i + j * width1],
                         vs[i + (j + 1) * width1],
                         vs[i + 1 + j * width1],
                         vs[i + 1 + (j + 1) * width1]}
                        );


    }
  }

  mesh->init<0>();
  mesh->init_bindings<1>();

  mesh->dump();

  for(auto cell : mesh->entities<2>()) {
    CINCH_CAPTURE() << "------- cell id: " << cell.id() << endl;
    for(auto corner : mesh->entities<1, 0, 1>(cell)) {
      CINCH_CAPTURE() << "--- corner id: " << corner.id() << endl;
    }
  }

  for(auto vertex : mesh->entities<0>()) {
    CINCH_CAPTURE() << "------- vertex id: " << vertex.id() << endl;
    for(auto corner : mesh->entities<1, 0, 1>(vertex)) {
      CINCH_CAPTURE() << "--- corner id: " << corner.id() << endl;
    }
  }

  for(auto corner : mesh->entities<1, 1>()) {
    CINCH_CAPTURE() << "------- corner id: " << corner.id() << endl;
    for(auto cell : mesh->entities<2, 1, 0>(corner)) {
      CINCH_CAPTURE() << "--- cell id: " << cell.id() << endl;
    }
  }

  for(auto corner : mesh->entities<1, 1>()) {
    CINCH_CAPTURE() << "------- corner id: " << corner.id() << endl;
    for(auto edge : mesh->entities<1, 1, 0>(corner)) {
      CINCH_CAPTURE() << "--- edge id: " << edge.id() << endl;
    }
  }

  for(auto edge : mesh->entities<1>()) {
    CINCH_CAPTURE() << "------- edge id: " << edge.id() << endl;
    for(auto corner : mesh->entities<1, 0, 1>(edge)) {
      CINCH_CAPTURE() << "--- corner id: " << corner.id() << endl;
    }
  }

  for(auto corner : mesh->entities<1, 1>()) {
    CINCH_CAPTURE() << "------- corner id: " << corner.id() << endl;
    for(auto vertex : mesh->entities<0, 1, 0>(corner)) {
      CINCH_CAPTURE() << "--- vertex id: " << vertex.id() << endl;
    }
  }

  for(auto cell : mesh->entities<2>()) {
    CINCH_CAPTURE() << "------- cell id: " << cell.id() << endl;
    for(auto wedge : mesh->entities<2, 0, 1>(cell)) {
      CINCH_CAPTURE() << "--- wedge id: " << wedge.id() << endl;
    }
  }

  for(auto edge : mesh->entities<1>()) {
    CINCH_CAPTURE() << "------- edge id: " << edge.id() << endl;
    for(auto wedge : mesh->entities<2, 0, 1>(edge)) {
      CINCH_CAPTURE() << "--- wedge id: " << wedge.id() << endl;
    }
  }

  for(auto vertex : mesh->entities<0>()) {
    CINCH_CAPTURE() << "------- vertex id: " << vertex.id() << endl;
    for(auto wedge : mesh->entities<2, 0, 1>(vertex)) {
      CINCH_CAPTURE() << "--- wedge id: " << wedge.id() << endl;
    }
  }

  for(auto wedge : mesh->entities<2, 1>()) {
    CINCH_CAPTURE() << "------- wedge id: " << wedge.id() << endl;
    for(auto cell : mesh->entities<2, 1, 0>(wedge)) {
      CINCH_CAPTURE() << "--- cell id: " << cell.id() << endl;
    }
  }

  for(auto wedge : mesh->entities<2, 1>()) {
    CINCH_CAPTURE() << "------- wedge id: " << wedge.id() << endl;
    for(auto edge : mesh->entities<1, 1, 0>(wedge)) {
      CINCH_CAPTURE() << "--- edge id: " << edge.id() << endl;
    }
  }

  for(auto wedge : mesh->entities<2, 1>()) {
    CINCH_CAPTURE() << "------- wedge id: " << wedge.id() << endl;
    for(auto vertex : mesh->entities<0, 1, 0>(wedge)) {
      CINCH_CAPTURE() << "--- vertex id: " << vertex.id() << endl;
    }
  }

  auto f1 = FILTER(ent){
    return ent.id() > 5;
  };

  auto f2 = FILTER(ent){
    return ent.id() < 3;
  };

  auto f3 = FILTER(ent){
    return ent.id() % 2 == 0;
  };

  auto r1 = mesh->entities<1>().filter(f1);

  auto r2 = mesh->entities<1>().filter(f2);

  auto r3 = mesh->entities<1>().filter(f3);

  for(auto edge : (r1 | r2) & r3){
    CINCH_CAPTURE() << "---- filter edge id: " << edge.id() << endl;   
  }

  ASSERT_TRUE(CINCH_EQUAL_BLESSED("bindings.blessed"));
}

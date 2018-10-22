#ifndef AGL_SMALL_BIP_SIGNED_GRAPH_DELTA_3
#define AGL_SMALL_BIP_SIGNED_GRAPH_DELTA_3

#include "Types.hpp"

class VertexDataView{
  u8& data;
public:
  struct Deg{
    Deg(VertexDataView& p) : parent(p) {}
    const Deg& operator++(int) const{
      parent.data = parent.data + (1<<5);
      return *this;
    }
    u8 val() const{
      return parent.data>>5;
    }
    VertexDataView& parent;
  };
  struct StrongIdx{
    StrongIdx(VertexDataView& p) : parent(p) {}
    const StrongIdx& operator++(int) const{
      u8 tmp1 = (parent.data & ((1<<9) - (1<<5)));
      u8 tmp2 = ((parent.data + 1) & ((1<<5) -1));
      parent.data = tmp1 + tmp2;
      return *this;
    }
    u8 val() const{
      u8 tmp = parent.data<<3;
      return tmp>>3;
    }
    VertexDataView& parent;
  };
  const Deg deg;
  const StrongIdx str;
  VertexDataView(u8& v) : data(v), deg(*this), str(*this) {}
};

#endif

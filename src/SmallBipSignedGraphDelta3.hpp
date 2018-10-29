#ifndef AGL_SMALL_BIP_SIGNED_GRAPH_DELTA_3
#define AGL_SMALL_BIP_SIGNED_GRAPH_DELTA_3

#include "Types.hpp"

template<typename DataType>
struct VertexDataViewBase{
  DataType data;
};

template<typename DataType, int BitMin, int BitMax>
struct DataMember{
  DataMember(VertexDataViewBase<DataType>& p) : parent(p) {}
  const DataMember& operator++(int) const{
    parent.data = parent.data + (1<<5);
    return *this;
  }
  DataType val() const{
    return parent.data>>5;
  }
  VertexDataViewBase<DataType>& parent;
  static const int bitMin = BitMin;
  static const int bitMax = BitMax;
  using dataType = DataType;
};

#define AGL_GENERATE_DATA_MEMBER(hasName, name) template<typename DataType, typename T> struct hasName##Base{ \
      using DMType = T; \
      T name; \
      hasName##Base(VertexDataViewBase<DataType>& p) : name(p) {} \
    }; \
    template<typename DataType, int BitMin, int BitMax> \
    using hasName = hasName##Base<DataType,DataMember<DataType, BitMin, BitMax>>;

AGL_GENERATE_DATA_MEMBER(hasBlu, blu)
//#undef AGL_GENERATE_DATA_MEMBER
AGL_GENERATE_DATA_MEMBER(hasDeg,deg)
AGL_GENERATE_DATA_MEMBER(hasStrongIdx,strongIdx)

template<typename DataType, typename ...DMArgs>
struct DataMemberList : DMArgs... {
  DataMemberList (VertexDataViewBase<DataType>& p)
        : DMArgs(p)...
    {
        static_assert(valid(), "Invalid DataMemberList: overlaping between the data members.");
    }

  template<class DMember>
  static constexpr bool is_valid_helper(DataType& range) {
    for (int i = DMember::DMType::bitMin; i < DMember::DMType::bitMax; i++){
        if (range & (DataType(1)<<i)){
            return false;
        } else{
            range |= DataType(1)<<i;
        }
    }
    return true;
  }

  template<class DM, class DM2, class ...Args>
  static constexpr bool is_valid_helper(DataType& range) {
    return is_valid_helper<DM>(range) && is_valid_helper<DM2, Args...>(range);
  }

  static constexpr bool valid(){
    DataType range = 0;
    return is_valid_helper<DMArgs...>(range);
  }
};

VertexDataViewBase<u8> base;
DataMemberList<u8, hasDeg<u8,0,3>, hasBlu<u8,3,5>> bli{base};



template<typename DataType, typename DataMemberList>
struct VertexDataView : VertexDataViewBase<DataType> {
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
  DataType data;
  VertexDataView(u8& v) : data(v), deg(*this), str(*this) {}
};

#endif

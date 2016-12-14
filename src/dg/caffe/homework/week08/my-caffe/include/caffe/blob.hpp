#ifndef CAFFE_BLOB_HPP_
#define CAFFE_BLOB_HPP_

#include <algorithm>
#include <string>
#include <vector>

#include "caffe/common.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/syncedmem.hpp"

namespace caffe {

template <typename Dtype>
class Blob {
 public:
  Blob()
       : data_(), diff_(), count_(0), capacity_(0) {}

  explicit Blob(const vector<int>& shape);

 protected:
  float* data_;
  float* diff_;
  vector<int> shape_;
  int count_;
  int capacity_;
};  // class Blob

}  // namespace caffe

#endif  // CAFFE_BLOB_HPP_
